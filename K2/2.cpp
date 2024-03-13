/*
Да се дефинира класа Vozac во која се чуваат информации за:

име (низа од максимум 100 знаци)
возраст (цел број)
број на трки (цел број)
дали е ветеран (да/не).
Да се преоптоварат:

операторот << за печатење кој ќе ги печати името, возраст, бројот на трки и дали е ветеран (се печати VETERAN)
операторот == за споредување на два возачи според заработувачката по трка.
Од оваа класа да се изведат две нови класи Avtomobilist и Motociklist.

За автомобилистот дополнително се чува:

цена на автомобилот (децимален број).
За мотоциклистот дополнително се чува:

моќност на мотор (цел број).
Заработувачката по трка на возачите се пресметува како:

за автомобилостот заработувачката по трка е $\frac{CENA_{AVTOMOBIL}}{5}$
за мотоциклистот заработувачката по трка е $MOKJNOST_NA_MOTOR * 20$
Секој автомобилист плаќа данок на заработка. Да се напишат соодветни методи за пресметување данок:

за автомобилисти: ако бројот на трки е поголем од 10 стапката на данок е 15% од заработката, инаку 10% од заработката.
за мотоциклисти: ако е ветеран стапката на данок е 25% од заработката, инаку 20% од заработката.
Да се напше надворешна функција soIstaZarabotuvachka која како аргументи прима низа од покажувачи од класата Vocac, нивниот број, како и покажувач кон ојбект од возач и враќа како резултат бројот на возачи кои имаат иста заработувачка по трка со проследениот возач.
 */
#include<iostream>
#include<cstring>

using namespace std;

class Vozac{
protected:
    char ime[100];
    int vozrast;
    int brTrki;
    bool veteran;
public:
    Vozac(char ime[100],int vozrast, int brTrki, bool veteran){
        strcpy(this->ime, ime);
        this->vozrast=vozrast;
        this->brTrki=brTrki;
        this->veteran=veteran;
    }
    friend ostream &operator<<(ostream &out, Vozac &v){
        out<<v.ime<<endl;
        out<<v.vozrast<<endl;
        out<<v.brTrki<<endl;
        if(v.veteran==true){
            out<<"VETERAN"<<endl;
        }
        return out;
    }
    bool operator==(Vozac &v){
        return zarabotuvacka()==v.zarabotuvacka();
    }
    virtual double zarabotuvacka()=0;
    virtual double danok()=0;
};

class Avtomobilist: public Vozac{
    float cena;
public:
    Avtomobilist(char ime[100],int vozrast, int brTrki, bool veteran, float cena) : Vozac(ime, vozrast, brTrki, veteran){
        this->cena=cena;
    }
    double zarabotuvacka(){
        return cena/5;
    }
    double danok(){
        if(brTrki>10){
            return zarabotuvacka()*0.15;
        }
        return zarabotuvacka()*0.10;
    }
};

class Motociklist: public Vozac{
    int mokjnost;
public:
    Motociklist(char ime[100],int vozrast, int brTrki, bool veteran, int mokjnost) : Vozac(ime, vozrast, brTrki, veteran){
        this->mokjnost=mokjnost;
    }
    double zarabotuvacka(){
        return mokjnost*20;
    }
    double danok(){
        if(veteran==true){
            return zarabotuvacka()*0.25;
        }
        return zarabotuvacka()*0.2;
    }
};
int soIstaZarabotuvachka(Vozac **vozaci, int n, Vozac *v){
    int brVozaci=0;
    for(int i=0;i<n;i++){
        if(vozaci[i]->zarabotuvacka()==v->zarabotuvacka()){
            brVozaci++;
        }
    }
    return brVozaci;
}
int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}