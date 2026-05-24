#ifdef SNOB_BUILD_MAIN
#   define SNOB_CC "gcc"
#   define SNOB_CFLAGS "library.o" // TODO: Add to SNOB_OBJECTS variable?
#endif

#include "../../snob.h"

#include <stdio.h> 
#include "b.h"

int main(void) {
    printf(from_b());
}
