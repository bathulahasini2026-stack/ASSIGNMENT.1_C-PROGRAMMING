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
//OUTPUT OF THE CODE
//### Task 10 Output
//```
//Bills    Paise total      Float total      Diff (Rs)    int/long? 
//4000     1656875.00  1656875.00       0.00         int:ok long(8 bytes):ok
         double paise total = 165687500, long long = 165687500  -> equal
//60000    24853125.00  24846614.00      -6511.00     int:OVERFLOW long(8 bytes):ok
         double paise total = 2485312500, long long = 2485312500  -> equal
//800000   331375000.00  331515424.00     140424.00    int:OVERFLOW long(8 bytes):ok
         double paise total = 33137500000, long long = 33137500000  -> equal

//sizeof on this system vs C standard minimum
//short     : 2 bytes (min 2)
//int       : 4 bytes (min 2)
//long      : 8 bytes (min 4)
//long long : 8 bytes (min 8)
//INT_MAX = 2147483647, LLONG_MAX = 9223372036854775807

//double loses accuracy after 2^53 = 9007199254740992
//2^53 + 1 in double = 9007199254740992 (the +1 is lost)
//```
