# snob
The **S**imple **Nob**uild system for C.

## About
Snob is a bulid tool for C that is inspired by [nob](https://github.com/tsoding/nob.h). It is a STB-style single header file library, making it easy to include in your project.

The premise behind the library is that you shouldn't need an external build tool in order to build C programs. Instead, you should be able to build an entire C project with just the C compiler. 

### How does it work? 
**S**nob is deliberately simple. It compiles each file twice - the first building the second.

It achieves this by (re)defining a `main` function. 

During the first build the (re)defined main gets compiled. This (re)defined main then invokes the command line through `snob_cmd` or `snob_build`. When this executable is run it will contain instructions on how to build itself.

## Use
### A word of warning
1. This library is very experimental and things are due to change drastically. 
2. I'm largely creating this to see if this is a viable way to build C projects. This was originally inteded to build super simple project, and will probably be very slow or headache-inducing to use in larger projects with more complicated dependencies. It also **doesn't support incremental builds** or **building itself**... (yet)

All in all... **don't use this**. Unless you really want to.

### How to use snob
Snob is fairly easy to use. Here's a reference guide:

#### `#include "snob.h"` 
Renames the `main` function to `_snob_prog_main`. 

It also `#define`s some constants like `SNOB_CC` and `SNOB_CFLAGS`.

#### `snob_start()`
Defines the start of the build logic.

#### `snob_end()`
Defines the end of the build logic.

#### `snob_cmd(...)`
This runs a command. It takes a list of strings and concats them into a single argument. It doesn't perform any checks on what "should" be grouped or not.

Currently the default for this is to use `system()` from `stdlib.h`. But, you can redefine this before the include if you wish to provide your own functionality.

#### `snob_build(extras)`
This is a wrapper around `snob_cmd`. It uses `__FILE__`, `SNOB_CFLAGS` and `extras` as the argv to `SNOB_CC`.

Similar to `snob_cmd`, it can be redefined before you include snob to allow for your own logic.

#### `snob_nob()`
"Snob no-build". Is equivalent to calling `snob_start` and `snob_end` with no logic inbetween. In other words, "don't do anything".
