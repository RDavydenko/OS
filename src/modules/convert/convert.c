#include "convert.h"

// Realization from: https://opensource.apple.com/source/groff/groff-10/groff/libgroff/itoa.c
char* itoa(int i)
{
    /* Room for INT_DIGITS digits, - and '\0' */
    static char buf[INT_DIGITS + 2];
    char *p = buf + INT_DIGITS + 1;	/* points to terminating '\0' */
    if (i >= 0) {
        do 
        {
            *--p = '0' + (i % 10);
            i /= 10;
        } while (i != 0);

        return p;
    }
    else 
    {			/* i < 0 */
        do 
        {
            *--p = '0' - (i % 10);
            i /= 10;
        } while (i != 0);

        *--p = '-';
    }

    return p;
}