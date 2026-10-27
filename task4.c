#include <stdio.h>

#define SQUARE_BAD(x) x*x
#define SQUARE(x) ((x)*(x))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define RUPEES_TO_PAISE(r) ((r) * 100)

static int max_func(int a, int b)
{
    return a > b ? a : b;
}

int main(void)
{
    int a = 4, i = 5, j = 3, m;

    printf("SQUARE_BAD(a+1) = %d\n", SQUARE_BAD(a + 1));
    printf("SQUARE(a+1)     = %d\n", SQUARE(a + 1));

    m = MAX(i++, j);
    printf("MAX(i++, j)     = %d, i = %d\n", m, i);

    i = 5;
    m = max_func(i++, j);
    printf("max_func(i++,j) = %d, i = %d\n", m, i);

    printf("RUPEES_TO_PAISE(162) = %d\n", RUPEES_TO_PAISE(162));
    return 0;
} 
//OUTPUT OF THE CODE 
//SQUARE_BAD(a+1) = 9
//SQUARE(a+1)     = 25
//MAX(i++, j)     = 6, i = 7
//max_func(i++,j) = 5, i = 6
//RUPEES_TO_PAISE(162) = 16200
