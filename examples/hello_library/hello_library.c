// Compile me with `-DSNOB_BUILD`, and then run the output!

#ifdef SNOB_BUILD
#   define SNOB_CC "gcc"
#   include "../../snob.h"
#       define SNOB_CFLAGS "-c"

    snob_start()
        snob_build()
    snob_end()
#endif

#include <stdio.h>

int say_hello(void) {
    printf("hello, world!");
    return 0;
}
