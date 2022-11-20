#include <stdio.h>

void
fgError(const char* fmt, ...)
{
    printf("fgError: %s\n", fmt);
}

void
fgWarning(const char* fmt, ...)
{
    printf("fgWarning: %s\n", fmt);
}

#define FREEGLUT_EXIT_IF_NOT_INITIALISED printf
