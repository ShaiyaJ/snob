#ifndef H_SNOB
#define H_SNOB

// Parameters
#ifndef SNOB_CC
#   define SNOB_CC "cc" 
#endif

#ifndef SNOB_CFLAGS
#   define SNOB_CFLAGS ""
#endif

#ifndef SNOB_NET_DEPENDENCIES // TODO
#   define SNOB_NET_DEPENDENCIES
#endif

#ifndef SNOB_LOCAL_DEPENDENCIES // TODO
#   define SNOB_LOCAL_DEPENDENCIES
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
#   define snob_build(target) snob_cmd(SNOB_CC " " SNOB_CFLAGS " " target)
#endif

#ifndef snob_post_build
#   define snob_post_build
#endif


// Functions


// Implementation

#ifdef SNOB_IMPLEMENTATION
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>

    void burnline(FILE* input_stream) {
        while (fgetc(input_stream) != '\n' && !feof(input_stream));
    }

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
            char result_name[] = "snob_tempfile_XXXXXX";
            mkstemp(result_name);

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
            fputs("int main(void) {\n",         result_file);
            fputs("   " "snob_pre_build\n",     result_file);
            fputs("   " "snob_build(",          result_file); 
                            fputs(argv[i],      result_file); 
                            fputs(")\n",        result_file); 
            fputs("   " "snob_post_build\n",    result_file);
            fputs("}\n", result_file);

            // Compile the tempfile 
            

            // Execute the tempfile
        }

        return EXIT_SUCCESS;
    }
#endif

#endif
