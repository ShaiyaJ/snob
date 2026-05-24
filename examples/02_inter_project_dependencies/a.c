#ifdef SNOB_BUILD_MAIN
#   define SNOB_CC "gcc"
#endif

#include "../../snob.h"

#include <stdio.h> 
#include "b.h"

const char* from_a() {
    return "Hello, b!";
}

int main(void) {
    printf(from_b());
}
