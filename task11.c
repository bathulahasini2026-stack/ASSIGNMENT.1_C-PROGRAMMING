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
//OUTPUT OF THE CODE 
//tariff.txt not found, using defaults
//sizeof: int=4 long=4 long long=8 float=4
//n=4000  paise total = Rs 1656875.00  float total = 1656875.00  diff = 0.00
  // total too big for int? no
//n=60000  paise total = Rs 24853125.00  float total = 24846614.00  diff = -6511.00
  // total too big for int? YES
//n=800000  paise total = Rs 331375000.00  float total = 331515424.00  diff = 140424.00
  // total too big for int? YES
//Check: 150 units -> Rs 162.50
