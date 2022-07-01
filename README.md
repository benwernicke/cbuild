# cbuild
a build tool which is only dependent on libc and a c compiler

## USAGE

cbuild.h will detect which compiler was used to compile it and use it to compile the given source files.

This feature is supported for `gcc, clang, msvc`

```
compile_object(char* src, char* flags, char* obj);
compile_object("main.c", "-g -Wall -pedantic", "main.o");
```
Compile a source file to an object file. Will only compile if source file was updated since last compilation

---

```
compile(char* out, ...);
compile("main", "-Wall", "-g -pedantic", "main.o", "add.o");
```
Compile given file with given flags. This function just constructs associated compile command with the parameters given.

---

```
auto_update();
```
The function `auto_update()` will automatically recompile `cbuild.c` if its source was altered
