## Disclaimer
This is a hobby project in the early stages of development, with great
[alternatives](https://en.wikipedia.org/wiki/List_of_numerical_libraries#C++).
In its current state it is 
at most expected to be useful for someone looking for simple examples of implementations of algorithms related to
linear algebra.

# DaBoPa_lib
A hobby project mathematics library.

### Compilation
On linux, simply run
```shell
make
```
and
```shell
make run
```

If you are using windows you should use [WSL](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux), or
cross compile.

### Linking against the library
Just include the DaBoPa_lib.h header file in src/include. Additionnal header files in subdirectories will be included.

### Header files for developers
Every internal header file should be included in `src/inernal_include/lib.h`.
Every header file that a program linked against the lib would need should be placed in a subdirectory of
`src/include` and included in `src/include/DaBoPas_lib.h`.

Every internal source file should be placed in a subdirectory of
`src/internal` include and included in `src/inernal_include/lib.h`.

Each CU is compiled with the `-I src/internal_include` option, so part of the path can be omitted:
```
#include "lib.h"
```

### Built time configuration
You can choose different implementations of functions by uncommenting/commenting out appropriate
line in `src/internal_include/tweakme`.
