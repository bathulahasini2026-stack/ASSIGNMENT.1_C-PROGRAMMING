#include <stdio.h>
#define FIXED_PAISE 5000
#define RATE_PAISE 225
#define SQUARE(x) ((x)*(x))

int main(void)
{
    int units = 150;
    long bill = FIXED_PAISE + (long)units * RATE_PAISE;
    printf("Bill = Rs %ld.%02ld\n", bill / 100, bill % 100);
    printf("Square of 3 = %d\n", SQUARE(3));
    return 0;
}
/* Commands (save as t8.c):
   gcc -E t8.c -o t8.i          preprocess: macros replaced
   gcc -S t8.c -o t8.s          assembly
   gcc -c t8.c -o t8.o          object file
   gcc t8.o -o t8               link
   gcc -Wall -Wextra t8.c -o t8 warnings
   Compile-time error : remove a semicolon
   Link-time error    : call a function that is declared but never defined
   Run-time error     : int z = 0; printf("%d", 10 / z);
*/
//OUTPUT OF THE CODE
//Bill = Rs 387.50
//Square of 3 = 9
