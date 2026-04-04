// A little helper build script - later on we can take this idea further! 

#include "../../snob.h"
#define BUILD "-DSNOB_BUILD -o build_current_file"

snob_start()
    // Build objects
    snob_build_target("hello_library.c", BUILD) // Build hello_library.c's build script
    snob_cmd("./build_current_file")            // Run it

    snob_build_target("main.c", BUILD)          // Build main.c's build script
    snob_cmd("./build_current_file")            // Run it

    // Link them
    snob_build_target("hello_library.o main.o", "-o exec")

    // Clean the targets up
    snob_cmd("rm hello_library.o")
    snob_cmd("rm main.o")
snob_end()
