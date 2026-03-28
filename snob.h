#ifndef H_SNOB
#define H_SNOB

/*
#include <stdlib.h>

// Overriding main
#define main            snob_prog_main

// Default flags and constants
#ifndef SNOB_CC
    #define SNOB_CC     "cc"
#endif

#ifndef SNOB_CFLAGS
    #define SNOB_CFLAGS ""
#endif

#ifdef SNOB_POLLUTE_ALIAS
    #define CC      SNOB_CC
    #define CFLAGS  SNOB_CFLAGS
#endif

// Build script
#ifdef _WIN32
    // TODO
#else
    #define snob_build(...)     system(SNOB_CC " " SNOB_CFLAGS " " __VA_ARGS__ " " __FILE__)
#endif

// Redefining main
#define snob_build_start()      int main(int argc, char** argv) {
#define snob_build_end()            snob_build();    \

*/

// Default flag values

#ifndef SNOB_CC
#   define SNOB_CC "cc" 
#endif

#ifndef SNOB_CFLAGS
#   define SNOB_CFLAGS ""
#endif

// Default command handling

#ifndef snob_cmd
#   include <stdlib.h>
#   define snob_cmd(...)            system(__VA_ARGS__)
#endif

#ifndef snob_build
#   define snob_build(extras)       snob_cmd(SNOB_CC " " SNOB_CFLAGS " " extras " " __FILE__)
#endif

// Implementation details
char* snob_process_source_file(const char* target);     // Reads content of file and prepends "#if 0" and appends #endif to comment out non-build related code

#define SNOB_BUILD_PATH "./snob_build.c"
#define SNOB_HEADER_PATH "./snob.h"
FILE* snob_generate_build_file();                       // Generates the build file name depending on SNOB_BUILD_PATH

// ---- Main implementation ----

#ifdef SNOB_IMPLEMENTATION

#include <stdlib.h>

char* snob_process_source_file(const char* target) {
    // Opening target file
    FILE* source_file = fopen(target, "w+");
    //FILE* temp_file = fopen();
    //
    // // Writing header
    // const char* HEADER = "#if 0\n";
    // fwrite(sizeof(HEADER), 1, HEADER, temp_file);
    //
    // // Copying source file over to temp
    // int c;
    // while ( (c = fgetc(source_file) != EOF) )
    //      fputc(c, temp_file);
    //
    // // Writing footer
    // const char* FOOTER = "#endif\n";
    // fwrite(sizeof(FOOTER), 1, FOOTER, temp_file);

    if (build_file == NULL)
        goto error;

    // Closing target file
    fclose(source_file);

    // Error handling
    error:
        return NULL;
}

FILE* snob_generate_build_file() {
    // Creating temporary file for program to use
    FILE* build_file = fopen(SNOB_BUILD_PATH, "w");

    if (build_file == NULL)
        goto error;

    // Creating build
    const char* HEADER = "#include \"" SNOB_HEADER_PATH   "\"\n";
    fwrite(sizeof(HEADER), 1, HEADER, build_file);

    // for (file : ./*.c) {
    //      const char* INCLUDE = "#include \"";
    //      char* temp = snob_process_source_file(target);
    //      const char* INCLUDEEND = "#\"\n";
    //
    //      fwrite(sizeof(INCLUDE), 1, INCLUDE, build_file);
    //      fwrite(strlen(temp), 1, temp, build_file);
    //      fwrite(sizeof(INCLUDEEND), 1, INCLUDEEND, build_file);
    // }
    
    // Error handling
    error: 
        return NULL;
}

#endif

// -----------------------------

#endif
