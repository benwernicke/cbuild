#define CBUILD
#include "cbuild.h"

int main(int argc, char** argv)
{
    auto_update();


    compile_object("main.c", "-Ofast", "main.o");
    compile("main", "main.o", "-Ofast");

    if (argc > 1) {
        if (strcmp(argv[1], "run") == 0) {
            system("./main");
        } else if (strcmp(argv[1], "clean") == 0) {
            system("rm main.o");
            system("rm main");
        }
    }
    return 0;
}
