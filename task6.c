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
//OUTPUT OF THE CODE
//Correct %lld: 5000000000
//Wrong   %d  : [undefined output]

//Enter household number: 101
//Enter category (D/C): D
//Enter previous reading: 1000
//Enter current reading: 1150

//Household: 101  Category: D
//Units    : 150
//Fixed    : Rs 50.00
//Energy   : Rs 112.50
//TOTAL    : Rs 162.50

//Type a number (fgets version): 25
//You typed 25
