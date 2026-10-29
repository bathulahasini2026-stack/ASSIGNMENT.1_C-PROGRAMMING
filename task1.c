#include <stdio.h>
#include <string.h>

/* Constants: values that never change during a run */
#define SLAB1_UNITS 100
#define SLAB2_UNITS 200
#define RATE2_PAISE 225
#define RATE3_PAISE 450
#define FIXED_CHARGE_PAISE 5000L

typedef unsigned short meter_t;      /* 16-bit meter register */

long compute_bill(int units)
{
    long paise = FIXED_CHARGE_PAISE;
    if (units > SLAB2_UNITS) {
        paise += (long)(units - SLAB2_UNITS) * RATE3_PAISE;
        units = SLAB2_UNITS;
    }
    if (units > SLAB1_UNITS)
        paise += (long)(units - SLAB1_UNITS) * RATE2_PAISE;
    return paise;
}

/* Alternative: reading stored as text, converted digit by digit: O(d) */
int text_to_number(const char *s, int *steps)
{
    int value = 0;
    *steps = 0;
    while (*s) {
        value = value * 10 + (*s - '0');
        (*steps)++;
        s++;
    }
    return value;
}

int main(void)
{
    /* Data items: inputs */
    int household = 101;             /* number, never negative */
    char category = 'D';             /* D = domestic, C = commercial */
    meter_t previous = 65400;        /* 16-bit counter */
    meter_t current = 120;           /* rolled over */

    /* Data items: outputs */
    unsigned int units;              /* never negative */
    long energy, fixed, total;       /* money in paise (whole numbers) */

    units = (meter_t)(current - previous);
    fixed = FIXED_CHARGE_PAISE;
    total = compute_bill((int)units);
    energy = total - fixed;

    printf("Household %d, category %c\n", household, category);
    printf("Units  = %u\n", units);
    printf("Fixed  = Rs %ld.%02ld\n", fixed / 100, fixed % 100);
    printf("Energy = Rs %ld.%02ld\n", energy / 100, energy % 100);
    printf("Total  = Rs %ld.%02ld\n", total / 100, total % 100);

    /* Rules every correct bill must satisfy */
    printf("\nRule 1: bill never negative     : %s\n", total >= 0 ? "PASS" : "FAIL");
    printf("Rule 2: total = fixed + energy  : %s\n", total == fixed + energy ? "PASS" : "FAIL");
    printf("Rule 3: units never negative    : %s\n", (int)units >= 0 ? "PASS" : "FAIL");
    printf("Rule 4: total >= fixed charge   : %s\n", total >= fixed ? "PASS" : "FAIL");

    /* Which values can be large: district total */
    printf("\nmax bill for 5000 units       : %ld paise\n", compute_bill(5000));
    printf("district (800000 houses) max   : %lld paise (needs long long)\n",
           800000LL * compute_bill(5000));

    /* Alternative: readings as text vs integer */
    {
        const char *text = "01530";
        int steps;
        int number = text_to_number(text, &steps);
        printf("\nText \"%s\": %d bytes (d+1), conversion took %d steps (d digits)\n",
               text, (int)strlen(text) + 1, steps);
        printf("Integer %d : %d bytes, no conversion needed, compare in 1 step\n",
               number, (int)sizeof(meter_t));
    }
    return 0;
}
//OUTPUT OF THE CODE
//### Task 1 Output
//```
//Household 101, category D
//Units  = 256
//Fixed  = Rs 50.00
//Energy = Rs 477.00
//Total  = Rs 527.00

//Rule 1: bill never negative     : PASS
//Rule 2: total = fixed + energy  : PASS
//Rule 3: units never negative    : PASS
//Rule 4: total >= fixed charge   : PASS

//max bill for 5000 units       : 2187500 paise
//district (800000 houses) max   : 1750000000000 paise (needs long long)

//Text "01530": 6 bytes (d+1), conversion took 5 steps (d digits)
//Integer 1530 : 2 bytes, no conversion needed, compare in 1 step
//```
