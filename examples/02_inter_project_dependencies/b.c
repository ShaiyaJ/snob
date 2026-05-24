#ifdef SNOB_BUILD_MAIN
#   define SNOB_CC "gcc"
#endif

#include "../../snob.h"

#include <stdio.h> 
#include "a.h"

const char* from_b() {
    return "Hello, a!";
}

int main(void) {
    printf(from_a());
}
