/*
За програмски јазик C.

Да се напише програма во која од стандарден влез се вчитува N (бројот на производи), а потоа се вчитуваат податоците за N производи (име, цена, количина). Програмата треба на стандарден излез да ја отпечати листата на купени производи и вкупната сума која треба да се плати во следниот облик (пример):

1. Flips    10.00 x 3 = 30.00
2. CocaCola 75.00 x 2 = 150.00
3. ChokoBanana  5.00 x 10 = 50.00
Total: 230.00
For example:

Input	            Result
3
Flips 10 3
CocaCola 75 2
ChokoBanana 5 10
                    1. Flips	10.00 x 3.0 = 30.00
                    2. CocaCola	75.00 x 2.0 = 150.00
                    3. ChokoBanana	5.00 x 10.0 = 50.00
                    Total: 230.00
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Proizvodi
{
    char ime[20];
    float cena;
    float kolicina;
};
typedef struct Proizvodi Proizvodi;

int main()
{
    Proizvodi p[20];
    int i, n;
    scanf("%d", &n);
    for(i=0;i<n;i++)
    {
        scanf("%s", &p[i].ime);
        scanf("%f", &p[i].cena);
        scanf("%f", &p[i].kolicina);
    }
    float total=0;
    for(i=0;i<n;i++)
    {
        total+=p[i].cena*p[i].kolicina;
        printf("%d. %s\t%.2f x %.1f = %.2f\n", i+1, p[i].ime, p[i].cena, p[i].kolicina, p[i].cena * p[i].kolicina);
    }
    printf("Total: %.2f", total);
    return 0;
}