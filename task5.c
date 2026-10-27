#include <stdio.h>

/* ---- header section (in a real project this goes in billing.h) ---- */
#ifndef BILLING_H
#define BILLING_H

/* Remove the comment marks to turn DEBUG mode on (or compile with gcc -DDEBUG) */
/* #define DEBUG */

#define SLAB1_UNITS 100
#define SLAB2_UNITS 200
#define RATE1_PAISE 0
#define RATE2_PAISE 225
#define RATE3_PAISE 450
#define FIXED_CHARGE_PAISE 5000L

#ifdef DEBUG
#define DBG(msg, val) printf("[DEBUG] %s = %ld\n", msg, (long)(val))
#else
#define DBG(msg, val)
#endif

long compute_bill(int units);

#endif

int debug = 0;   /* run-time alternative: set to 1 to see messages */

int main(void)
{
    int tests[] = {0, 100, 150, 350};
    int n = sizeof tests / sizeof tests[0];
    int i;

    for (i = 0; i < n; i++) {
        long p = compute_bill(tests[i]);
        if (debug) printf("run-time debug: units=%d paise=%ld\n", tests[i], p);
        printf("%3d units -> Rs %ld.%02ld\n", tests[i], p / 100, p % 100);
    }
    return 0;
}

long compute_bill(int units)
{
    long paise = FIXED_CHARGE_PAISE;
    DBG("units", units);

    if (units > SLAB2_UNITS) {
        paise += (long)(units - SLAB2_UNITS) * RATE3_PAISE;
        units = SLAB2_UNITS;
        DBG("after slab 3", paise);
    }
    if (units > SLAB1_UNITS) {
        paise += (long)(units - SLAB1_UNITS) * RATE2_PAISE;
        units = SLAB1_UNITS;
        DBG("after slab 2", paise);
    }
    paise += (long)units * RATE1_PAISE;
    DBG("final paise", paise);
    return paise;
}
//OUTPUT OF THE CODE
//  0 units -> Rs 50.00
//100 units -> Rs 50.00
//150 units -> Rs 162.50
//350 units -> Rs 950.00
