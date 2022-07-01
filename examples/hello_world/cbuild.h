#ifndef CBUILD_H
#define CBUILD_H
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define GREEN "\033[32m"
#define RESET "\033[39m"
#define RED "\033[31m"

#ifndef CBUILD_BUILD_DIR
#define CBUILD_BUILD_DIR "cbuild_build"
#endif

#ifndef COMPILER

#if defined(__clang__)
#define COMPILER "clang"

#elif defined (__GNUG__)
#define COMPILER "g++"

#elif defined(__GNUC__)
#define COMPILER "gcc"

#elif defined(__MSVC_VER__)
#define COMPILER "msvc"

#elif defined(__TINYC__)
#define COMPILER "tcc"
#endif

// TODO: mingw

#endif // COMPILER

#ifndef CBUILD_EXE
#define CBUILD_EXE "cbuild"
#endif

#ifndef CBUILD_SRC
#define CBUILD_SRC "cbuild.c"
#endif

#define run_command(comp, ...) run_command_(comp, __VA_ARGS__, NULL)
void auto_update();
void compile_object(char* path, char* flags, char* obj);
#define compile(out, ...) print_comp_command_(COMPILER, "-o", out, __VA_ARGS__, NULL), run_command_(COMPILER, "-o", out, __VA_ARGS__, NULL)

#endif
#ifdef CBUILD

static void print_comp_command_(char* comp, ...)
{
    va_list ap;
    va_start(ap, comp);
    char* cmd = malloc(256);
    uint64_t len = 256;
    uint64_t new_len = strlen(comp);
    strcpy(cmd, comp);
    char* next_arg = NULL;

    while ((next_arg = va_arg(ap, char*)) != NULL) {
        new_len += strlen(next_arg) + 3;
        if (new_len >= len) {
            cmd = realloc(cmd, new_len << 1);
            len = new_len << 1;
        }
        strcat(cmd, " ");
        strcat(cmd, next_arg);
    }
    printf(GREEN "compiling: " RESET "%s\n", cmd);

    free(cmd);
}

static int run_command_(char* comp, ...);
static long file_last_mod(char* path);

static bool file_exists(char* path)
{
    FILE* f = fopen(path, "r");
    if (f == NULL) {
        return 0;
    } else {
        fclose(f);
        return 1;
    }
}

void compile_object(char* path, char* flags, char* obj)
{
    time_t last_mod_src = file_last_mod(path);
    time_t last_mod_obj = file_last_mod(obj);
    bool exists = file_exists(obj);

    if (!exists || last_mod_src > last_mod_obj) {
        printf(GREEN "compiling: " RESET "%s -o %s -c %s\n", COMPILER, obj, path);
        if (run_command(COMPILER, "-o", obj, "-c", path) != 0) {
            exit(1);
        }
    }
}

static time_t file_last_mod(char* path)
{
    struct stat s;
    stat(path, &s);
    return s.st_mtim.tv_sec;
}

void auto_update()
{
    time_t last_mod_src = file_last_mod(CBUILD_SRC);
    time_t last_mod_exe = file_last_mod(CBUILD_EXE);
    if (last_mod_src > last_mod_exe) {
        printf("\033[32mcompiling:\033[39m %s\n", CBUILD_SRC);
        if (run_command(COMPILER, "-o ", CBUILD_EXE, CBUILD_SRC) == 0) {
            char new_run[3 + strlen(CBUILD_EXE)];
            strcpy(new_run, "./");
            strcat(new_run, CBUILD_EXE);
            system(new_run);
            exit(0);
        } else {
            printf(RED "error: " RESET "while compiling %s\n", CBUILD_SRC);
        }
    }
}

static int run_command_(char* comp, ...)
{
    va_list ap;
    va_start(ap, comp);
    char* cmd = malloc(256);
    uint64_t len = 256;
    uint64_t new_len = strlen(comp);
    strcpy(cmd, comp);
    char* next_arg = NULL;

    while ((next_arg = va_arg(ap, char*)) != NULL) {
        new_len += strlen(next_arg) + 3;
        if (new_len >= len) {
            cmd = realloc(cmd, new_len << 1);
            len = new_len << 1;
        }
        strcat(cmd, " ");
        strcat(cmd, next_arg);
    }

    int r = system(cmd);
    free(cmd);
    return r;
}

#endif
