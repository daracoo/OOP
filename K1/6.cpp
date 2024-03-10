/*
Да се креира структура Воз во која се чуваат податоци за релацијата по која се движи возот (низа од најмногу 50 знаци), предвиден бројот на километри што треба да се поминат (реален број), како и бројот на патници во возот (цел број).

Потоа да се креирa структура ZeleznickaStanica во која се чуваат податоци за градот во кој се наоѓа (низа од 20 знаци), низа од возови што поаѓаат од станицата (најмногу 30) и бројот на возови (цел број).

Треба да се направи функција со потпис

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad)
во која се печати релацијата и бројот на километри на возот што поминува најкратка релација (најмалку километри), а поаѓа од железничката станица од градот што се проследува како влезен аргумент. Ако има повеќе возови со ист најмал број на километри, да се испечати релацијата на последниот таков.

Забелешка: Задачата да се реши во програмскиот јазик C++

For example:

Input	                    Result
1
Dresden
2
Dresden-Berlin 192 200
Dresden-Lajpcig 115 90
Dresden
                            Najkratka relacija: Dresden-Lajpcig (115 km)
 */
#include <iostream>
#include <string.h>
using namespace std;

struct Voz
{
    char relacija[50];
    double kilometri;
    int patnici;
};

struct ZeleznickaStanica
{
    char grad[20];
    Voz vozovi[30];
    int broj;
};

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad)
{

    int inx=0;
    int jnx=0;
    double rel=999999;
    int city=strlen(grad);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<zs[i].broj;j++)
        {
            if(zs[i].vozovi[j].kilometri<=rel && strncmp(zs[i].vozovi[j].relacija,grad,city)==0)
            {
                inx=i;
                jnx=j;
                rel=zs[i].vozovi[j].kilometri;
            }

        }
    }
    cout<<"Najkratka relacija: "<<zs[inx].vozovi[jnx].relacija<<" ("<<zs[inx].vozovi[jnx].kilometri<<" km)"<<endl;

}

int main(){

    int n;
    cin>>n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
        for(i=0;i<n;i++)
        {
            cin>>zStanica[i].grad;
            cin>>zStanica[i].broj;

            for(int j=0;j<zStanica[i].broj;j++)
            {
                cin>>zStanica[i].vozovi[j].relacija;
                cin>>zStanica[i].vozovi[j].kilometri;
                cin>>zStanica[i].vozovi[j].patnici;
            }
        }
    }

    char grad[25];
    cin>>grad;

    najkratkaRelacija(zStanica,n,grad);
    return 0;
}
