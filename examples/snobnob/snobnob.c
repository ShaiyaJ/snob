#ifdef SNOB_BUILD
#   define SNOB_CC "gcc"
#   include "../../snob.h"

#   ifdef SNOB_NO_NOB // Only if you really want to see main run
        snob_start()
            snob_build()
        snob_end()
#   else
        snob_nob()
#   endif
#endif

#include <stdio.h>

int main(void) {
    printf("You'll never see me run!");
}
