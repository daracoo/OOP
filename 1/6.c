/*
За програмски јазик да се употреби C.

Да се креира структура Employee во која се чуваат податоци за еден вработен. За вработениот се чуваат информации за името на вработениот (низа од карактери), матичен број (ЕМБГ) на вработениот(низа од карактери), име на одделот во кој што работи (низа од карактери), плата (цел број).

Потоа, да се креира структура Company во која се чуваат податоци за името на компанијата (низа од карактери), низа од вработени во компанијата и број на вработени.

Да се направи функција:

void printEmployeesBelowAverageSalary(Company *comp, int numCompanies)

која што за секоја компанија, ќе ги испечати сите вработени чија што плата е пониска од просекот на платите на сите вработени во таа компанија.

Да се направи функција:

void printHighestSalaryEmployee(Company *comp, int numCompanies, char *department)

кoja што за секоја компанија ќе го испечати вработениот со највисока плата во дадениот оддел.

Напомена: Прво од тастатура се чита бројот на компании, потоа компаниите (името и бројот на вработени), а потоа податоците за нивните вработени соодветно, a на крај се чита одделот кој што ќе биде искористен во printHighestSalaryEmployee функцијата.

For example:

Input	                        Result
2
Apple
3
Vlatko 111111 IT 150000
Nikola 222222 IT 125000
Marko 333333 Accounting 50000
Google
2
Stefan 444444 IT 150000
John 555555 HR 60000
IT
                                Employees with salaries below the average:
                                Marko 333333 Accounting 50000
                                John 555555 HR 60000
                                Employees with highest salaries for given department:
                                Vlatko 111111 IT 150000
                                Stefan 444444 IT 150000
 */
#include <stdio.h>
#include <string.h>

struct Employee{
    char ime[50];
    char embg[13];
    char oddel[50];
    int plata;
};
typedef struct Employee Employee;

struct Company{
    char ime[50];
    Employee employees[50];
    int brVraboteni;
};
typedef struct Company Company;

void printEmployeesBelowAverageSalary(Company *comp, int numCompanies){
    int sumaPlati=0, average=0, maxj=0;

    for(int i=0;i<numCompanies;i++){
        sumaPlati = 0;
        for(int j=0;j<comp[i].brVraboteni;j++){
            sumaPlati += comp[i].employees[j].plata;
        }

        average = sumaPlati / comp[i].brVraboteni;

        for(int j=0;j<comp[i].brVraboteni;j++){
            if(average > comp[i].employees[j].plata){
                maxj=j;
                printf("%s %s %s %d\n", comp[i].employees[maxj].ime, comp[i].employees[maxj].embg, comp[i].employees[maxj].oddel, comp[i].employees[maxj].plata);
            }
        }
    }
}

void printHighestSalaryEmployee(Company *comp, int numCompanies, char *department){
    int  maxj;
    for(int i=0;i<numCompanies;i++){
        int maxPlata=0;
        for(int j=0;j<comp[i].brVraboteni;j++){
            if(!strcmp(department,comp[i].employees[j].oddel)) {
                if (comp[i].employees[j].plata > maxPlata) {
                    maxPlata = comp[i].employees[j].plata;
                    maxj = j;
                }
            }
        }
        printf("%s %s %s %d\n", comp[i].employees[maxj].ime, comp[i].employees[maxj].embg, comp[i].employees[maxj].oddel, comp[i].employees[maxj].plata);

    }
}

int main()
{
    int brKompanii;
    Company c[100];
    scanf("%d", &brKompanii);
    for(int i=0;i<brKompanii;i++){
        scanf("%s %d", c[i].ime, &c[i].brVraboteni);
        for(int j=0;j<c[i].brVraboteni;j++){
            scanf("%s %s %s %d", c[i].employees[j].ime, c[i].employees[j].embg, c[i].employees[j].oddel, &c[i].employees[j].plata);
        }
    }
    char oddel[20];
    scanf("%s", oddel);

    printf("Employees with salaries below the average:\n");
    printEmployeesBelowAverageSalary(c, brKompanii);

    printf("Employees with highest salaries for given department:\n");
    printHighestSalaryEmployee(c, brKompanii, oddel);
}