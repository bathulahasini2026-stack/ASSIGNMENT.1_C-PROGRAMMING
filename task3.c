#include <stdio.h>

#define SLAB1_UNITS 100
#define SLAB2_UNITS 200
#define RATE1_PAISE 0
#define RATE2_PAISE 225
#define RATE3_PAISE 450
#define FIXED_CHARGE_PAISE 5000L

const int MAX_UNITS = 100000;
enum { DOMESTIC, COMMERCIAL };

long compute_bill(int units)
{
    long paise = FIXED_CHARGE_PAISE;

    if (units > SLAB2_UNITS) {
        paise += (long)(units - SLAB2_UNITS) * RATE3_PAISE;
        units = SLAB2_UNITS;
    }
    if (units > SLAB1_UNITS) {
        paise += (long)(units - SLAB1_UNITS) * RATE2_PAISE;
        units = SLAB1_UNITS;
    }
    paise += (long)units * RATE1_PAISE;
    return paise;
}

int main(void)
{
    int tests[] = {0, 100, 150, 200, 350};
    int n = sizeof tests / sizeof tests[0];
    int i;

    for (i = 0; i < n; i++) {
        long p = compute_bill(tests[i]);
        printf("%3d units -> Rs %ld.%02ld\n", tests[i], p / 100, p % 100);
    }
    printf("MAX_UNITS = %d, COMMERCIAL = %d\n", MAX_UNITS, COMMERCIAL);
    return 0;
}

//OUTPUT 
//  0 units -> Rs 50.00
//100 units -> Rs 50.00
//150 units -> Rs 162.50
//200 units -> Rs 275.00
//350 units -> Rs 950.00
//MAX_UNITS = 100000, COMMERCIAL = 1
