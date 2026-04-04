#ifdef SNOB_BUILD
#   define SNOB_CC "gcc"
#   define SNOB_CFLAGS "-c"
#   include "../../snob.h"

    snob_start()
        snob_build()
    snob_end()

#   undef SNOB_BUILD    // With multiple files, you might want to introduce a
#endif                  // guard such as this. In most cases it isn't necessary
                        // as long as you keep your build logic in the .c files
                        // and only include the .h files. However, if you need
                        // to build with single-header libraries or are 
                        // including .c files directly then you might 
                        // accidentally end up defining multiple "builds" 
                        // (which will result in an error). Stay safe!

#include "hello_library.h"

int main(void) {
    say_hello();
    return 0;
}
