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
//OUTPUT OF THE CODE
//tariff12.txt not found, using defaults
//Readings per house per year : 35040
//One house, 10 kW all year   : 87600000 Wh (16-bit max 65535, 32-bit max 4294967295)
//District 800000 houses      : 70080000000000 Wh (needs long long)
//Peak slots: slot 71=0 slot 72=1 slot 87=1 slot 88=0
//350 kWh off-peak                         expected  90000  got  90000  PASS
//150 kWh + 1 kWh peak (225 x 1.2)         expected  11520  got  11520  PASS
//32-bit rollover, 1000 Wh free slab       expected      0  got      0  PASS
//30-day month: 552 kWh, bill = Rs 1986.26
