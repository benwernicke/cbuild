#define CBUILD
#include "cbuild.h"

#define FLAGS "-g -Wall -pedantic"

int main(void)
{
    printf("Hello World\n");
    auto_update();
    compile_object("add.c", FLAGS, "build/add.o");
    compile_object("main.c", FLAGS, "build/main.o");
    compile_object_directory("main", FLAGS, "build/");
    return 0;
}
