# snob
The **S**imple **Nob**uild system for C.

## About
Snob is a bulid tool for C that is inspired by [nob](https://github.com/tsoding/nob.h). It is a STB-style single header file library, making it easy to include in your project.

The premise behind the library is that you shouldn't need an external build tool in order to build C programs. Instead, you should be able to build an entire C project with just a C compiler. 

### How does it work? 
**S**nob is deliberately simple. It passes over each target twice.

The first time snob extracts all the preprocessor directives and puts them into a separate file. It then adds a pre-defined main function into this file that can be controlled with preprocessor directives.

This first script then gets compiled and ran, which will build the actual target.

This leads to a nice setup where you simply put your build information at the top of a file, and snob will naturally collect it and build your targets based off the directives that you gave it. 

## Use
### A word of warning
1. This library is very experimental and things are due to change drastically. 
2. I'm largely creating this to see if this is a viable way to build C projects. This was originally intended to build super simple project, and will probably be very slow or headache-inducing to use in larger projects with more complicated dependencies. It also **doesn't support incremental builds** or **building itself**... (yet)
