/*
Да се дефинира класа MobilePhone во која ќе се чуваат податоци за еден мобилен телефон:

модел (низа од карактери не подолга од 20 карактери)
број на модел (цел број)
година на издавање (цел број)
За класата да се дефинира default конструктор, конструктор со аргументи, copy конструктор, деструктор и доколку има потреба get методи. Исто така да се дефинира и фунцкија за печатење на информации за класата која ќе печати во следниот формат „(модел) (број на модел) release year: (година на издавање)“.

Потоа да се дефинира класа Owner во која се чуваат следните информации:

име (низа од карактери не подолга од 20 карактери)
презиме (низа од карактери не подолга од 20 карактери)
мобилен телефон (објект од класа MobilePhone)
Да се креира default конструктор, конструктор со аргументи, деструктор и доколку има потреба get методи. Исто така да се дефинира и функција за печатење на информации за класата која ќе печати во следниот формат:

„(име) (презиме) has a mobile phone:

(информации за мобилен телефон)“

ДА НЕ СЕ МЕНУВА MAIN ФУНКЦИЈАТА!!!

For example:

Input	Result
1
Iphone
12
2020
Marko
Petrov
        Marko Petrov has a mobile phone:
        Iphone 12 release year: 2020
 */
#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;

class MobilePhone{
    char model[20];
    int broj;
    int godina;
public:
    MobilePhone(){}
    MobilePhone(char *model, int broj, int godina){
        strcpy(this->model, model);
        this->broj=broj;
        this->godina=godina;
    }
    MobilePhone(const MobilePhone &mp){
        strcpy(this->model, mp.model);
        this->broj=mp.broj;
        this->godina=mp.godina;
    }
    ~MobilePhone(){}

    void print(){
        cout<<model<<" "<<broj<<" release year: "<<godina<<endl;
    }

};

class Owner{
    char ime[20];
    char prezime[20];
    MobilePhone mobile;
public:
    Owner(){}
    Owner(char *ime, char *prezime, MobilePhone mobile){
        strcpy(this->ime, ime);
        strcpy(this->prezime, prezime);
        this->mobile=mobile;
    }
    Owner(const Owner &o){
        strcpy(this->ime, o.ime);
        strcpy(this->prezime, o.prezime);
        this->mobile=o.mobile;
    }

    void print(){
        cout<<ime<<" "<<prezime<<" has a mobile phone: "<<endl;
        mobile.print();
    }

};



//DO NOT CHANGE THE MAIN FUNCTION
int main() {
    char model[20];
    int modelNumber;
    int year;
    char name[20];
    char surname[20];

    int testCase;

    cin>>testCase;

    cin>>model;
    cin>>modelNumber;
    cin>>year;
    cin>>name;
    cin>>surname;

    if(testCase==1){
        MobilePhone mobilePhone(model,modelNumber,year);

        Owner owner(name,surname,mobilePhone);
        owner.print();
    }
    if(testCase==2){
        MobilePhone mobilePhone(MobilePhone(model,modelNumber,year));

        Owner owner(name,surname,mobilePhone);
        owner.print();
    }

}
