ASSIGNMENT.1_C-PROGRAMMING

Student Name: B.Hasini
Register Number: 1925260337
Course: CSA02
Compiler: GCC [Min GW]
Language: C



TASK 1-DATA ITEMS , CONSTANTS , RULES AND TEXT VS INTEGER READINGS
task1.c

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
Compile command: gcc Task01/task01.c -o task01

Run command: ./task01 (Linux/macOS) or .\task01.exe (Windows PowerShell)


### Task 1 Output
```
Household 101, category D
Units  = 256
Fixed  = Rs 50.00
Energy = Rs 477.00
Total  = Rs 527.00

Rule 1: bill never negative     : PASS
Rule 2: total = fixed + energy  : PASS
Rule 3: units never negative    : PASS
Rule 4: total >= fixed charge   : PASS

max bill for 5000 units       : 2187500 paise
district (800000 houses) max   : 1750000000000 paise (needs long long)

Text "01530": 6 bytes (d+1), conversion took 5 steps (d digits)
Integer 1530 : 2 bytes, no conversion needed, compare in 1 step
```
<img task1.c output screenshot />

TASK 2-DATA TYPES
task2.c

#include <stdio.h>
#include <limits.h>
#include <float.h>

typedef unsigned short meter_t;

unsigned int consumption(meter_t previous, meter_t current)
{
    return (meter_t)(current - previous);
}

int main(void)
{
    float f = 0;
    long long p = 0;
    int i;

    printf("char=%d short=%d int=%d long=%d long long=%d float=%d double=%d\n",
           (int)sizeof(char), (int)sizeof(short), (int)sizeof(int),
           (int)sizeof(long), (int)sizeof(long long), (int)sizeof(float), (int)sizeof(double));
    printf("short: %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short: 0 to %u\n", (unsigned)USHRT_MAX);
    printf("int: %d to %d\n", INT_MIN, INT_MAX);
    printf("long long max: %lld\n", LLONG_MAX);
    printf("float digits: %d, double digits: %d\n", FLT_DIG, DBL_DIG);

    printf("sizeof(meter_t) = %d bytes, maximum reading = %u\n", (int)sizeof(meter_t), (unsigned)USHRT_MAX);
    printf("Consumption: %u units\n", consumption(1200, 1530));
    printf("Consumption: %u units\n", consumption(65400, 120));

    for (i = 0; i < 4000; i++) {
        f += 162.55f;
        p += 16255;
    }
    printf("float total : %.2f\n", f);
    printf("paise total : %lld.%02lld\n", p / 100, p % 100);
    return 0;
}
Compile command: gcc Task02/task02.c -o task02

Run command: ./task02 (Linux/macOS) or .\task02.exe (Windows PowerShell)

//output of the code
### Task 2 Output
```
char=1 short=2 int=4 long=8 long long=8 float=4 double=8
short: -32768 to 32767
unsigned short: 0 to 65535
int: -2147483648 to 2147483647
long long max: 9223372036854775807
float digits: 6, double digits: 15
sizeof(meter_t) = 2 bytes, maximum reading = 65535
Consumption: 330 units
Consumption: 256 units
float total : 650226.25
paise total : 650200.00
```
SCREENSHOT OF THE OUTPUT
<img task2.c output />

TASK 3-CONSTANTS
task3.c

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
Compile command: gcc Task02/task02.c -o task02

Run command: ./task02 (Linux/macOS) or .\task02.exe (Windows PowerShell)

### Task 3 Output
```
  0 units -> Rs 50.00
100 units -> Rs 50.00
150 units -> Rs 162.50
200 units -> Rs 275.00
350 units -> Rs 950.00
MAX_UNITS = 100000, COMMERCIAL = 1
```
<img task3.c output />

TASK 4- MACROS
task4.c  

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
Compile command: gcc Task02/task02.c -o task02

Run command: ./task02 (Linux/macOS) or .\task02.exe (Windows PowerShell)

### Task 4 Output
```
SQUARE_BAD(a+1) = 9
SQUARE(a+1)     = 25
MAX(i++, j)     = 6, i = 7
max_func(i++,j) = 5, i = 6
RUPEES_TO_PAISE(162) = 16200
```
<img task5.c output />

TASK 5-HEADER FILES AND DEBUG
task5.c

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
Compile command: gcc Task02/task02.c -o task02

Run command: ./task02 (Linux/macOS) or .\task02.exe (Windows PowerShell)
output:

  0 units -> Rs 50.00
100 units -> Rs 50.00
150 units -> Rs 162.50
350 units -> Rs 950.00
<img task5.c />

TASK 6-INPUT/OUTPUT WITH VALIDATION
task6.c

#include <stdio.h>
#include <stdlib.h>

long compute_bill(int units)
{
    long p = 5000;
    if (units > 200) { p += (long)(units - 200) * 450; units = 200; }
    if (units > 100) { p += (long)(units - 100) * 225; }
    return p;
}

int main(void)
{
    int house;
    char cat;
    unsigned int prev, curr, units;
    long total;
    long long big = 5000000000LL;
    char line[50];
    int x;

    printf("Correct %%lld: %lld\n", big);
    printf("Wrong   %%d  : %d\n", big);

    printf("Enter household number: ");
    if (scanf("%d", &house) != 1) { printf("Invalid household number\n"); return 1; }
    printf("Enter category (D/C): ");
    if (scanf(" %c", &cat) != 1) { printf("Invalid category\n"); return 1; }
    printf("Enter previous reading: ");
    if (scanf("%u", &prev) != 1) { printf("Invalid reading (letters?)\n"); return 1; }
    printf("Enter current reading: ");
    if (scanf("%u", &curr) != 1) { printf("Invalid reading (letters?)\n"); return 1; }
    if (prev > 65535 || curr > 65535) { printf("Reading out of range\n"); return 1; }

    units = (unsigned short)(curr - prev);
    total = compute_bill((int)units);

    printf("\nHousehold: %d  Category: %c\n", house, cat);
    printf("Units    : %u\n", units);
    printf("Fixed    : Rs 50.00\n");
    printf("Energy   : Rs %ld.%02ld\n", (total - 5000) / 100, (total - 5000) % 100);
    printf("TOTAL    : Rs %ld.%02ld\n", total / 100, total % 100);

    printf("\nType a number (fgets version): ");
    getchar();
    if (fgets(line, sizeof line, stdin) != NULL) {
        if (sscanf(line, "%d", &x) == 1) printf("You typed %d\n", x);
        else printf("Not a number\n");
    }
    return 0;
}
Compile command: gcc Task02/task02.c -o task02

Run command: ./task02 (Linux/macOS) or .\task02.exe (Windows PowerShell)
 output:

Correct %lld: 5000000000
Wrong   %d  : [undefined output]

Enter household number: 101
Enter category (D/C): D
Enter previous reading: 1000
Enter current reading: 1150

Household: 101  Category: D
Units    : 150
Fixed    : Rs 50.00
Energy   : Rs 112.50
TOTAL    : Rs 162.50

Type a number (fgets version): 25
You typed 25
<img task6.c output />


TASK 7-TYPE CONVERSION
task7.c

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
Compile command: gcc Task07/task07.c -o task07

Run command: ./task07 (Linux/macOS) or .\task07.exe (Windows PowerShell)
output:

1) 250 / 100 = 2  (expected 2.5)
   250 / 100.0 = 2.50
2) (-1 < 1u) = 0  (expected 1, but -1 becomes a huge unsigned number)
3) (int)big = 705032704
4) (long)(2.675*100) = 267, rounded = 268
5) float total = 129493440.00, paise total = 130040000.00

<img task7.c output />

TASK 8- COMPILATION STAGES
task8.c

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
Compile command: gcc Task08/task08.c -o task08

Run command: ./task08 (Linux/macOS) or .\task08.exe (Windows PowerShell)

output:

Bill = Rs 387.50
Square of 3 = 9
<img task8.c output />

TASK 9- IMPLEMENT AND TEST
task9.c

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
Compile command: gcc Task09/task09.c -o task09

Run command: ./task09 (Linux/macOS) or .\task09.exe (Windows PowerShell)

output:

Test                   Expected   Actual     Result
50 units               5000       16250      FAIL
150 units              16250      16250      PASS
exactly 100            5000       5000       PASS
exactly 200            27500      27500      PASS
zero units             5000       5000       PASS
350 units              95000      95000      PASS
rollover 65400->120    52700      5000       FAIL
letters                0          0          PASS
negative               0          0          PASS
decrease               0          0          PASS
too large              0          0          PASS

5 bills hand total = 148750 paise, program = 148750  PASS
Loop version matches if-version for 0..1000 units
<img task9.c output />

TASK 10-EXPECTED VS ACTUAL
task10.c
#include <stdio.h>
#include <limits.h>

#define FIXED 5000L

long long bill(int units)
{
    long long p = FIXED;
    if (units > 200) { p += (long long)(units - 200) * 450; units = 200; }
    if (units > 100) { p += (long long)(units - 100) * 225; }
    return p;
}

int main(void)
{
    long n[3] = {4000, 60000, 800000};
    int k;
    long i;
    double big = 9007199254740992.0;      /* 2^53 */

    printf("%-8s %-16s %-16s %-12s %-10s\n", "Bills", "Paise total", "Float total", "Diff (Rs)", "int/long?");
    for (k = 0; k < 3; k++) {
        long long total = 0;
        float ftotal = 0;
        double dtotal = 0;
        for (i = 0; i < n[k]; i++) {
            long long b = bill((int)(i % 400));
            total += b;
            ftotal += (float)b / 100.0f;
            dtotal += (double)b;
        }
        printf("%-8ld %lld.%02lld  %-16.2f %-12.2f int:%s long(%d bytes):%s\n",
               n[k], total / 100, total % 100, ftotal, ftotal - (double)total / 100.0,
               total > INT_MAX ? "OVERFLOW" : "ok",
               (int)sizeof(long), total > LONG_MAX ? "OVERFLOW" : "ok");
        printf("         double paise total = %.0f, long long = %lld  -> %s\n",
               dtotal, total, dtotal == (double)total ? "equal" : "DIFFERENT");
    }

    printf("\nsizeof on this system vs C standard minimum\n");
    printf("short     : %d bytes (min 2)\n", (int)sizeof(short));
    printf("int       : %d bytes (min 2)\n", (int)sizeof(int));
    printf("long      : %d bytes (min 4)\n", (int)sizeof(long));
    printf("long long : %d bytes (min 8)\n", (int)sizeof(long long));
    printf("INT_MAX = %d, LLONG_MAX = %lld\n", INT_MAX, LLONG_MAX);

    printf("\ndouble loses accuracy after 2^53 = %.0f\n", big);
    printf("2^53 + 1 in double = %.0f (the +1 is lost)\n", big + 1.0);
    return 0;
}
Compile command: gcc Task10/task10.c -o task10

Run command: ./task10 (Linux/macOS) or .\task10.exe (Windows PowerShell)
//OUT OF THE CODE

Bills    Paise total      Float total      Diff (Rs)    int/long? 
4000     1656875.00  1656875.00       0.00         int:ok long(8 bytes):ok
         double paise total = 165687500, long long = 165687500  -> equal
60000    24853125.00  24846614.00      -6511.00     int:OVERFLOW long(8 bytes):ok
         double paise total = 2485312500, long long = 2485312500  -> equal
800000   331375000.00  331515424.00     140424.00    int:OVERFLOW long(8 bytes):ok
         double paise total = 33137500000, long long = 33137500000  -> equal

sizeof on this system vs C standard minimum
short     : 2 bytes (min 2)
int       : 4 bytes (min 2)
long      : 8 bytes (min 4)
long long : 8 bytes (min 8)
INT_MAX = 2147483647, LLONG_MAX = 9223372036854775807

double loses accuracy after 2^53 = 9007199254740992
2^53 + 1 in double = 9007199254740992 (the +1 is lost)
<img task10.c output screenshot />



TASK 11-FINAL DECISION
task11.c

#include <stdio.h>

typedef unsigned short meter_t;
typedef long long paise_t;

long slab1 = 100, slab2 = 200, r1 = 0, r2 = 225, r3 = 450, fixed = 5000;

void load_tariff(void)
{
    FILE *fp = fopen("tariff.txt", "r");
    if (fp == NULL) { printf("tariff.txt not found, using defaults\n"); return; }
    fscanf(fp, "%ld %ld %ld %ld %ld %ld", &slab1, &slab2, &r1, &r2, &r3, &fixed);
    fclose(fp);
    printf("Tariff loaded from tariff.txt\n");
}

paise_t bill(int units)
{
    paise_t p = fixed;
    if (units > slab2) { p += (paise_t)(units - slab2) * r3; units = (int)slab2; }
    if (units > slab1) { p += (paise_t)(units - slab1) * r2; units = (int)slab1; }
    return p + (paise_t)units * r1;
}

int main(void)
{
    long n[3] = {4000, 60000, 800000};
    int k;
    long i;

    load_tariff();
    printf("sizeof: int=%d long=%d long long=%d float=%d\n",
           (int)sizeof(int), (int)sizeof(long), (int)sizeof(long long), (int)sizeof(float));

    for (k = 0; k < 3; k++) {
        paise_t total = 0;
        float ftotal = 0;
        for (i = 0; i < n[k]; i++) {
            paise_t b = bill((int)(i % 400));
            total += b;
            ftotal += (float)b / 100.0f;
        }
        printf("n=%ld  paise total = Rs %lld.%02lld  float total = %.2f  diff = %.2f\n",
               n[k], total / 100, total % 100, ftotal, ftotal - (double)total / 100.0);
        printf("   total too big for int? %s\n", total > 2147483647LL ? "YES" : "no");
    }
    printf("Check: 150 units -> Rs %lld.%02lld\n", bill(150) / 100, bill(150) % 100);
    return 0;
}
Compile command: gcc Task11/task11.c -o task11

Run command: ./task11 (Linux/macOS) or .\task11.exe (Windows PowerShell)

output:

tariff.txt not found, using defaults
sizeof: int=4 long=8 long long=8 float=4
n=4000  paise total = Rs 1656875.00  float total = 1656875.00  diff = 0.00
   total too big for int? no
n=60000  paise total = Rs 24853125.00  float total = 24846614.00  diff = -6511.00
   total too big for int? YES
n=800000  paise total = Rs 331375000.00  float total = 331515424.00  diff = 140424.00
   total too big for int? YES
Check: 150 units -> Rs 162.50
<img task11.c output />

TASK 12-LAST DESIGN
task12.c

#include <stdio.h>

typedef unsigned int wh_t;
typedef long long ll;

long slab1 = 100, slab2 = 200, r1 = 0, r2 = 225, r3 = 450, fixed = 5000, peak_pct = 120;

void load_tariff(void)
{
    FILE *fp = fopen("tariff12.txt", "r");
    if (fp == NULL) { printf("tariff12.txt not found, using defaults\n"); return; }
    fscanf(fp, "%ld %ld %ld %ld %ld %ld %ld", &slab1, &slab2, &r1, &r2, &r3, &fixed, &peak_pct);
    fclose(fp);
}

int is_peak(int slot)
{
    int hour = slot / 4;
    return hour >= 18 && hour < 22;
}

ll energy_milli(ll wh)
{
    ll s1 = (ll)slab1 * 1000, s2 = (ll)slab2 * 1000, c = 0;
    c += (wh < s1 ? wh : s1) * r1;
    if (wh > s1) c += ((wh < s2 ? wh : s2) - s1) * r2;
    if (wh > s2) c += (wh - s2) * r3;
    return c;
}

ll scaled = 0, cum_wh = 0;

void add_interval(int slot, wh_t prev, wh_t curr)
{
    wh_t delta = curr - prev;
    ll before = energy_milli(cum_wh);
    cum_wh += delta;
    scaled += (energy_milli(cum_wh) - before) * (is_peak(slot) ? peak_pct : 100);
}

ll total_paise(void)
{
    return fixed + (scaled + 50000) / 100000;
}

void check(const char *name, ll got, ll expected)
{
    printf("%-40s expected %6lld  got %6lld  %s\n", name, expected, got, got == expected ? "PASS" : "FAIL");
}

int main(void)
{
    ll year_wh = 10000LL * 8760;
    wh_t reg;
    int day, slot;

    load_tariff();
    printf("Readings per house per year : %d\n", 96 * 365);
    printf("One house, 10 kW all year   : %lld Wh (16-bit max 65535, 32-bit max 4294967295)\n", year_wh);
    printf("District 800000 houses      : %lld Wh (needs long long)\n", year_wh * 800000);
    printf("Peak slots: slot 71=%d slot 72=%d slot 87=%d slot 88=%d\n", is_peak(71), is_peak(72), is_peak(87), is_peak(88));

    scaled = 0; cum_wh = 0; add_interval(40, 0, 350000);
    check("350 kWh off-peak", total_paise() - fixed, 90000);

    scaled = 0; cum_wh = 0; add_interval(40, 0, 150000); add_interval(76, 150000, 151000);
    check("150 kWh + 1 kWh peak (225 x 1.2)", total_paise() - fixed, 11520);

    scaled = 0; cum_wh = 0; add_interval(40, 4294967295U - 499, 500);
    check("32-bit rollover, 1000 Wh free slab", total_paise() - fixed, 0);

    scaled = 0; cum_wh = 0; reg = 0;
    for (day = 0; day < 30; day++)
        for (slot = 0; slot < 96; slot++) {
            wh_t prev = reg;
            reg += is_peak(slot) ? 400 : 150;
            add_interval(slot, prev, reg);
        }
    printf("30-day month: %lld kWh, bill = Rs %lld.%02lld\n", cum_wh / 1000, total_paise() / 100, total_paise() % 100);
    return 0;
}
Compile command: gcc Task12/task12.c -o task12

Run command: ./task12 (Linux/macOS) or .\task12.exe (Windows PowerShell)

output:

tariff12.txt not found, using defaults
Readings per house per year : 35040
One house, 10 kW all year   : 87600000 Wh (16-bit max 65535, 32-bit max 4294967295)
District 800000 houses      : 70080000000000 Wh (needs long long)
Peak slots: slot 71=0 slot 72=1 slot 87=1 slot 88=0
350 kWh off-peak                         expected  90000  got  90000  PASS
150 kWh + 1 kWh peak (225 x 1.2)         expected  11520  got  11520  PASS
32-bit rollover, 1000 Wh free slab       expected      0  got      0  PASS
30-day month: 552 kWh, bill = Rs 1986.26

<img task12.c output screenshot />



