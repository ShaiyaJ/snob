#ifdef SNOB_BUILD_MAIN
#   define SNOB_CC "gcc"
#   define SNOB_CFLAGS "-c"
#endif

#include "../../snob.h"

#include <stdio.h> 
#include "library.h"

const char* from_b() {
    return "Hello, a!";
}
