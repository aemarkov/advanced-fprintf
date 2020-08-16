/* C fprintf wrapper with ability to print custom types */

#include <stdio.h>
#include "afprintf.h"

// EXAMPLE STRUCTURES //////////////////////////////////////////////////////////////////////////////

struct foo
{
    int a;
    int b;
};

// Function to print "struct foo" to the FILE*
void format_foo(FILE* f, void* data)
{
    if (data == NULL) {
        fprintf(f, "foo(nill)");
        return;
    }

    struct foo* foo = (struct foo*)data;
    fprintf(f, "foo{a=%d, b=%d}", foo->a, foo->b);
}

#define FORMAT_FOO(ptr)format_foo, (ptr)

struct bar
{
    double a;
    int b;
    char c[255];
};

// Function to print "struct bar" to the FILE*
void format_bar(FILE* f, void* data)
{
    if (data == NULL) {
        fprintf(f, "foo(nill)");
        return;
    }

    struct bar* bar = (struct bar*)data;
    fprintf(f, "bar{a=%lf, b=%d, c='%s'}", bar->a, bar->b, bar->c);
}

#define FORMAT_BAR(ptr)format_bar, (ptr)

////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    struct foo foo = { .a=1, .b=2 };
    struct bar bar = { .a=3.14, .b=10, .c="hello world" };

    aprintf("Print: int: %d, foo: %Y, str: '%s', bar: %Y, bad one: %Y. The end!\n",
            123, FORMAT_FOO(&foo), "some string", FORMAT_BAR(&bar), FORMAT_FOO(NULL));

    return 0;
}

