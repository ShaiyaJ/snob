#ifndef H_SNOB
#define H_SNOB

// Overriding main
#define main(...)   _snob_prog_main(__VA_ARGS__); int _snob_prog_main_dummy(void) 

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
#   define snob_cmd(...)                        system(__VA_ARGS__);
#endif

// Predefined build commands
#ifndef snob_build
#   define snob_build(extras)                   snob_cmd(SNOB_CC " " SNOB_CFLAGS " " extras " " __FILE__) // TODO: platform agnostic way to achieve this?
#endif

#ifndef snob_build_target
#   define snob_build_target(target, extras)    snob_cmd(SNOB_CC " " SNOB_CFLAGS " " extras " " target)
#endif

// Course of a snob program's life
#define snob_start()                            void (main)(void) {
#define snob_end()                              }

#define snob_nob()                              void (main)(void) {}
#define snob_quick()                            snob_start() snob_build() snob_end()

#endif
