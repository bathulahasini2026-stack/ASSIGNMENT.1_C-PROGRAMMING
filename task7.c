#include <stdio.h>

int main(void)
{
    int units = 250;
    int neg = -1;
    unsigned int one = 1;
    long big = 5000000000L;
    double v = 2.675;
    float f = 0;
    long long p = 0;
    int i;

    printf("1) 250 / 100 = %d  (expected 2.5)\n", units / 100);
    printf("   250 / 100.0 = %.2f\n", units / 100.0);

    printf("2) (-1 < 1u) = %d  (expected 1, but -1 becomes a huge unsigned number)\n", neg < one);

    printf("3) (int)big = %d\n", (int)big);

    printf("4) (long)(2.675*100) = %ld, rounded = %ld\n", (long)(v * 100), (long)(v * 100 + 0.5));

    for (i = 0; i < 800000; i++) { f += 162.55f; p += 16255; }
    printf("5) float total = %.2f, paise total = %lld.%02lld\n", f, p / 100, p % 100);
    return 0;
}
//OUTPUT OF THE CODE
//1) 250 / 100 = 2  (expected 2.5)
  // 250 / 100.0 = 2.50
//2) (-1 < 1u) = 0  (expected 1, but -1 becomes a huge unsigned number)
//3) (int)big = 705032704
//4) (long)(2.675*100) = 267, rounded = 268
//5) float total = 129493440.00, paise total = 130040000.00
