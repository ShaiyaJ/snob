// This shows a basic usage of snob

#ifdef SNOB_BUILD_MAIN
    // Firstly, we define all the "mode-independent build information for this file
#   define SNOB_CC "gcc"

    // Then, we define mode-specific build information
#   ifdef BUILD_AS_OBJ
#       define SNOB_CFLAGS "-c" 
#   elifdef BUILD_AS_PROD_EXE
#       define SNOB_CFLAGS "-O2 -o example"
#   endif

#endif

// Finally, we include snob - TODO: perhaps put this inside the build main block?
#include "../../snob.h"

// The program goes below
#include <stdio.h>

int main(void) {
    printf("hello, world!");

    return 0;
}
