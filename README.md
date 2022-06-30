# cbuild
a build tool which is only dependent on libc and a c compiler

## USAGE
```
#define CBUILD
#include "cbuild.h"

#include <string.h> // for strcmp()
#include <stdlib.h> // for system()

#define FLAGS "-g -Wall -pedantic"

int main(char** argv)
{
    auto_update(); //will recompile cbuild.c if changes were made

    //compile every src file to an object file
    compile_object("main.c", FLAGS, "main.o"); //will only compile if main.c changed
    compile_object("lib1.c", FLAGS, lib1.o); //will only compile if lib1.c changed

    //compile object files to main executable
    compile_src("main", FLAGS, "main.o", lib1.o); //will always run

    //because this is a c program you can do something like this
    if(strcmp(argv[1], "run") == 0) { 
        system("./main");
    }

    return 0;
}
```
