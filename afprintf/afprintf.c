#include "afprintf.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define BUFFER_SIZE    4096
#define SUBSTANCE      "%Y"
#define SUBSTANCE_LEN  (sizeof(SUBSTANCE)-1)

void afprintf(FILE* f, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    static char fmt_copy[BUFFER_SIZE];
    char* subformat_current;
    char* subformat_next;

    strncpy(fmt_copy, fmt, BUFFER_SIZE);
    subformat_current = fmt_copy;
    subformat_next = fmt_copy;

    while((subformat_next = strstr(subformat_next, SUBSTANCE)) != NULL) {
        subformat_next[0] = '\0';
        subformat_next+= SUBSTANCE_LEN;

        // Print all "regular" format before substance
        vfprintf(f, subformat_current, args);
        subformat_current = subformat_next;

        // Print substance
        print_handler handler = va_arg(args, print_handler);
        void* data = va_arg(args, void*);
        if (handler != NULL) handler(f, data);
        else fprintf(f, "<invalid handler>");
    }

    // Handle remain regular format
    vfprintf(f, subformat_current, args);

    va_end(args);
}

