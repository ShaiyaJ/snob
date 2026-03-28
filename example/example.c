#define SNOB_CC "gcc"

#include "../snob.h"

#if     defined execute
    #define SNOB_CFLAGS "-o main"

    snob_build_start()
    snob_build_end()
#elif   defined object
    #define SNOB_CFLAGS "-c"

    snob_build_start()
    snob_build_end()
#else   
        
#endif

#include <stdio.h>

int main(void) {
    puts("Hello, world!");
}
