#ifndef H_SNOB
#define H_SNOB

// ----- Configuring snob executable file ----- //
// -- These are the configuration options    -- //
// -- when you bootstrap snob - any          -- //
// -- dependencies are used by the standard  -- //
// -- implementation (they're optional if    -- //
// -- you want to write a custom             -- //
// -- implementation                         -- //
// -------------------------------------------- //

// Invoking a command from the bootstrapped snob executable - this is different from snob_cmd
// as snob_cmd is what your source code will use to invoke a command instead.
#define SNOB_BOOTSTRAP_CMD(...)         system(__VA_ARGS__)

// Building a tempfile - your source code will generate a build script called a "tempfile" and
// these are the commands which dictate how the *tempfile* (not the source code itself but its
// *tempfile*) is built.
#define SNOB_TEMPFILE_CC                "cc"
#define SNOB_TEMPFILE_CFLAGS            ""
#define SNOB_TEMPFILE_LDFLAGS           ""
#define SNOB_TEMPFILE_BUILD(target,out) int command_size = strlen(target)    +1 +   \
                                                           strlen(out)       +1 +   \
                                                sizeof(SNOB_TEMPFILE_CC)     +1 +   \
                                                sizeof(SNOB_TEMPFILE_CFLAGS) +1 +   \
                                                sizeof(SNOB_TEMPFILE_LDFLAGS)+1 ;   \
                                        char command_buffer[command_size];          \
                                                                                    \
                                        snprintf(command_buffer, command_size,      \
                                            "%s %s %s %s -o %s",                    \
                                            SNOB_TEMPFILE_CC, SNOB_TEMPFILE_CFLAGS, \
                                            SNOB_TEMPFILE_LDFLAGS, target, out);    \
                                                                                    \
                                        printf("%s\n", command_buffer);             \
                                        SNOB_BOOTSTRAP_CMD(command_buffer);

// Running a tempfile - as mentioned before, the tempfile is like a script which builds your 
// source file. You can think of the compilation process being:
//      source.c -> tempfile that builds source.c -> executable
//      \______/  \___________________________________________/
//         |         Your bootstrapped snob deals with this 
//      You configure what the tempfile outputs by redefining SNOB_CC, SNOB_... here
// These flags dictate how the bootstrapped snob executable runs the tempfile.
#define SNOB_TEMPFILE_RUN(tempfile)     int name_size = strlen(tempfile);       \
                                        char executable_buf[name_size + 2];     \
                                                                                \
                                        executable_buf[0] = '.';                \
                                        executable_buf[1] = '/';                \
                                        strcpy(executable_buf + 2, tempfile);   \
                                                                                \
                                        SNOB_BOOTSTRAP_CMD(executable_buf);


// ----- Snob program code ----- //
// -- These values are        -- //
// -- intended to be set in   -- //
// -- your source files       -- //
// ----------------------------- //

// Parameters
#ifndef SNOB_CC
#   define SNOB_CC "cc" 
#endif

#ifndef SNOB_CFLAGS
#   define SNOB_CFLAGS ""
#endif

#ifndef SNOB_LDFLAGS
#   define SNOB_LDFLAGS ""
#endif


// Utils
#ifndef snob_cmd
#   include <stdlib.h>
#   define snob_cmd(...)    system(__VA_ARGS__);
#endif

#define SNOB_STR(x)         SNOB_EXPAND(x)
#define SNOB_EXPAND(x)      #x


// Hooks
#ifndef snob_pre_build
#   define snob_pre_build // TODO: fill out local deps? 
#endif

#ifndef snob_build
#   define snob_build(target)       snob_cmd(SNOB_CC " " SNOB_CFLAGS " " SNOB_LDFLAGS " " target)
#endif

#ifndef snob_post_build
#   define snob_post_build
#endif


// Implementation

#ifdef SNOB_IMPLEMENTATION
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>

    // Moves to the next line in an input stream
    void burnline(FILE* input_stream) {
        while (fgetc(input_stream) != '\n' && !feof(input_stream));
    }

    // Copies an entire line to the result file
    void copyline(FILE* input_stream, FILE* result_stream) {
        fputc('#', result_stream);
        
        // Copy rest of line after adding already consumed '#'
        int c;
        while ((c = fgetc(input_stream)) != '\n' && !feof(input_stream)) {
            fputc(c, result_stream);

            // Handling multi line macros
            if (c == '\\') {
                burnline(input_stream);
                fputc('\n', result_stream);
            }
        }

        // Adding newline
        fputc('\n', result_stream);
    }

    // Checks whether a line is a compiler directive or program code
    void checkline(FILE* input_stream, FILE* result_stream) {
        int c;
        while (isspace( c = fgetc(input_stream) ) && !feof(input_stream));
        
        if (c == '#')
            copyline(input_stream, result_stream);
        else
            burnline(input_stream);
    }

    int main(int argc, char** argv) {
        // Check for correct argument length (should be <script>, <mode>, <files...>
        if (argc < 3) {
            fprintf(stderr, "Incorrect arguments provided\n\tUSAGE:\n\t\tsnob <mode> <...targets>\n");
            return EXIT_FAILURE;
        }

        // Read the mode
        char* mode = argv[1];

        // Iterate through all files
        for (int i = 2; i < argc; i++) {
            // Opening files
            char result_file_name[] = "snob_tempfile_XXXXXX";
            char result_name[sizeof(result_file_name) + 2] = {0};

            mkstemp(result_file_name);
            strcat(result_name, result_file_name);
            strcat(result_name, ".c");              // Some compilers get confused without the .c ext

            FILE* input_file = fopen(argv[i], "r");
            FILE* result_file = fopen(result_name, "w");

            // Putting mode header information
            fputs("#define ", result_file);
            fputs(mode, result_file);
            fputc('\n', result_file);

            // Processing file
            while(!feof(input_file))
                checkline(input_file, result_file);

            // Adding build commands
            fputs("\nint main(void) {\n",       result_file);
            fputs("   " "snob_pre_build\n",     result_file);
            fputs("   " "snob_build(\"",        result_file); 
                            fputs(argv[i],      result_file); 
                            fputs("\")\n",      result_file); 
            fputs("   " "snob_post_build\n",    result_file);
            fputs("   " "return 0;\n",          result_file);
            fputs("}\n", result_file);

            // Compile the tempfile 
            char executable_name[] = "snob_tempfile_XXXXXX";
            mkstemp(executable_name);

            SNOB_TEMPFILE_BUILD(result_name, executable_name) 

            // Execute the tempfile
            SNOB_TEMPFILE_RUN(executable_name)

            // Cleanup
            fclose(result_file);
            //remove(result_name);
            //remove(executable_name);
        }

        return EXIT_SUCCESS;
    }
#endif

#endif
