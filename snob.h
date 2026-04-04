#ifndef H_SNOB
#define H_SNOB

// Overriding main
#define main(...)   main(void) {            \
                        _snob_build_fn();   \
                    }                       \
                    int _snob_prog_main(__VA_ARGS__)


// Parameters
#ifndef SNOB_CC
#   define SNOB_CC "cc" 
#endif

#ifndef SNOB_CFLAGS
#   define SNOB_CFLAGS ""
#endif

// Running commands
#ifndef snob_cmd        
#   include <stdlib.h>
#   define snob_cmd(...)            system(__VA_ARGS__);
#endif

// Predefined commands
#ifndef snob_build
#   define snob_build(extras)       snob_cmd(SNOB_CC " " SNOB_CFLAGS " " extras " " __FILE__)
#endif

// Course of a snob program's life
#define snob_start()    void _snob_build_fn(void) {
//#define snob_main()     int main(void) {return 0;} snob_start()
#define snob_end()      }

#define snob_nob()      void _snob_build_fn(void) {}

#endif
