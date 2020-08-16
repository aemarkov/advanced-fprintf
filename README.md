# advanced_fprintf

fprintf hack with ability print custom structures

## How to use

1. Define custom structure you want to print
```c
struct foo
{
    int a;
    int b;
}
```

2. Define function to print this structure to the `FILE*`
```c
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
```

3. Use formatted output
```c
struct foo foo = { .a=1, .b=2 };
afprintf("Foo: %Y\n", FORMAT_FOO(&foo))
```

Use special substitution symbol `%Y` and place formatting macro at the corresponding position

## How it works
When `afprintf` finds `%Y` it expects that next two arguemnts will be pointer to the formatting
function and the pointer to the data to print. It calls formatter and it writes output to the
`FILE*`. Other symbols expect `%Y` are processed by regular `fprintf`

## May I trust it?
This function is POSIX-compilant.

POSIX, 7.19.6: "Formatted output":
> If the format is exhausted while arguments remain, the excess arguments are evaluated (as always),
but are otherwise ignored

[man (3) vfprintf](http://man7.org/linux/man-pages/man3/vfprintf.3p.html):
> These functions shall not invoke the `va_end` macro.
