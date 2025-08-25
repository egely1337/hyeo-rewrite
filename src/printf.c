#include <printf.h>
#include <stdarg.h>
#include <string.h>

/*
    There is a pointer array starting at str, 
    if you increment 4 bytes on cdecl x86, 
    you get the second variadic parameter
    THAT compiler does not know.

    Because when you calling a function (cdecl calling convention x86), 
    cdecl compiler setting up a new stack that contains pointers of arguments, 
    so when you pass a parameter as variadic parameter, you can find the next argument by increating first parameter address by four.
    
    Like:
    ```c
        unsigned int* integer_arg = (int*)(&str + 1); // you get the first parameter
        unsigned int* string = (int*)(&str + 2); // you get the second parameter
        terminal_print_string((char*)string);
        terminal_print_string(itoa(*integer_arg));
    ```
*/ 
void printf(const char* str, ...) {
    va_list ap;
    va_start(ap, str);
    char* j = str;

    while(*j != 0) {
        switch (*j)
        {
        case 0x13:
            break;
        case '%':
            j++;
            switch (*j)
            {
            case 's':
                char *ch = va_arg(ap, char*);
                terminal_print_string(ch);
                break;
            case 'x':
                unsigned int sint = va_arg(ap, int);
                terminal_print_string(ithex(sint)); 
                break;
            case 'u':
                unsigned int uint = va_arg(ap, unsigned int);
                terminal_print_string(itoa(uint));
                break;
            default:
                break;
            }
            break;
        default:
            terminal_print_char(*j);
            break;
        }

        j++;
    }

    /* Flush to terminal driver */
    terminal_flush();
}