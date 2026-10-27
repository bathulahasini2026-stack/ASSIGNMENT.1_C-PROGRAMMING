#include <stdio.h>
#include <stdlib.h>

#define SLAB1 100
#define SLAB2 200
#define RATE2 225
#define RATE3 450
#define FIXED 5000L

long compute_bill(int units)
{
    long p = FIXED;
    if (units > SLAB2) { p += (long)(units - SLAB2) * RATE3; units = SLAB2; }
    if (units > SLAB1) { p += (long)(units - SLAB1) * RATE2; }
    return p;
}

long compute_bill_loop(int units)
{
    int upper[3] = {100, 200, 1000000};
    long rate[3] = {0, 225, 450};
    long p = FIXED;
    int lower = 0, s;
    for (s = 0; s < 3 && units > lower; s++) {
        int top = upper[s] < units ? upper[s] : units;
        p += (long)(top - lower) * rate[s];
        lower = upper[s];
    }
    return p;
}

/* returns 0 = ok, 1 = letters, 2 = negative, 3 = out of range, 4 = decrease */
int make_bill(const char *ps, const char *cs, int *units, long *paise)
{
    char *e1, *e2;
    long prev = strtol(ps, &e1, 10);
    long curr = strtol(cs, &e2, 10);

    if (e1 == ps || *e1 != '\0' || e2 == cs || *e2 != '\0') return 1;
    if (prev < 0 || curr < 0) return 2;
    if (prev > 65535 || curr > 65535) return 3;
    if (curr < prev && prev < 60000) return 4;
    *units = (unsigned short)(curr - prev);
    *paise = compute_bill(*units);
    return 0;
}

int main(void)
{
    const char *name[] = {"50 units", "150 units", "exactly 100", "exactly 200", "zero units",
                          "350 units", "rollover 65400->120", "letters", "negative",
                          "decrease", "too large"};
    const char *prev[] = {"1000","1000","1000","1000","1000","1000","65400","abc","-5","1000","1000"};
    const char *curr[] = {"1050","1150","1100","1200","1000","1350","120","100","100","900","70000"};
    int exp_code[] = {0,0,0,0,0,0,0,1,2,4,3};
    long exp_paise[] = {5000,16250,5000,27500,5000,95000,52700,0,0,0,0};
    int i, units, code;
    long paise, total = 0;
    int five[5] = {0, 100, 150, 200, 350};

    printf("%-22s %-10s %-10s %s\n", "Test", "Expected", "Actual", "Result");
    for (i = 0; i < 11; i++) {
        units = 0; paise = 0;
        code = make_bill(prev[i], curr[i], &units, &paise);
        printf("%-22s %-10ld %-10ld %s\n", name[i], exp_paise[i], paise,
               (code == exp_code[i] && paise == exp_paise[i]) ? "PASS" : "FAIL");
    }

    for (i = 0; i < 5; i++) total += compute_bill(five[i]);
    printf("\n5 bills hand total = 148750 paise, program = %ld  %s\n", total, total == 148750 ? "PASS" : "FAIL");

    for (i = 0; i <= 1000; i++)
        if (compute_bill(i) != compute_bill_loop(i)) { printf("Loop version differs at %d\n", i); return 1; }
    printf("Loop version matches if-version for 0..1000 units\n");
    return 0;
}
//OUTPUT OF THE CODE
//Test                   Expected   Actual     Result
//50 units               5000       5000       PASS
//150 units              16250      16250      PASS//
//exactly 100            5000       5000       PASS
//exactly 200            27500      27500      PASS
//zero units             5000       5000       PASS
//350 units              95000      95000      PASS
//rollover 65400->120    52700      30200      FAIL
//letters                0          0          PASS
//negative               0          0          PASS
//decrease               0          0          PASS
//too large              0          0          PASS

//5 bills hand total = 148750 paise, program = 148750  PASS
//Loop version matches if-version for 0..1000 units
