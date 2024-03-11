/*
Потребно е да се моделира продажба на карти за прикажување на претстави во некој културен центар. За таа цел, да се направи класа DELO. За класата се чуваат следните атрибути:

Име на делото (низа од 50 знаци)
Година кога е напишано (цел број)
Земја на потекло (низа од 50 знаци)
За класата да се направат потребниот конструктор, get и set методи. За класата DELO да се преоптовари операторот == кој ќе споредува дали две дела се исти (две дела се исти ако имаат исто име) (5 поени).

Да се дефинира класа PRЕTSTAVA. За класата се чуваат информации за:

Делото кое се прикажува (објект од класата DELO)
Број на продадени карти (цел број)
Дата на прикажување (низа од 15 знаци)
За класата да се дефинира потребниот конструктор, set и get методите Дополнително, за класата PRETSTAVA да се напише метода cena која треба да ја врати цената на една карта. (5 поени) Цената зависи од староста на делото и од земјата на потекло и се пресметува по следната формула: Цена = N + М, каде М = 50ден. ако делото е напишано во 20 или 21 век, М = 75ден. ако делото е напишано во 19 век и М = 100ден. ако делото е напишано пред 19 век. N = 100ден ако делото е од Италија, N = 150ден ако делото е од Русија. Делата од останатите земји имаат N = 80ден.

Претставите можат да бидат опера и балет. За балетите се чува дополнителен атрибут за цената на балетот која се додава на оригиналната цена на картата и таа вредност е иста за сите балетски претстави. На почеток изнесува 150 денари, со можност да се променува ако така одлучи менаџментот на културниот центар. (10 поени)

Да се дефинира надворешна функција prihod која како аргумент прима низа од покажувачи кон претстави кои се прикажале во еден месец и големина на низата, а како резултат треба да го пресмета и врати вкупниот приход на културниот центар. (10 поени)

Да се дефинира надворешна функција brojPretstaviNaDelo која како аргумент прима низа од покажувачи кон претстави кои се прикажале во еден месец, големина на низата и едно дело. Оваа функција пресметува на колку од дадените претстави е прикажано даденото дело. (5 поени)

(Напомена: Во низата од претстави која се проследува како аргумент во функциите prihod и brojPretstaviNaDelo може да имаме повеќе претстави за едно исто дело)

Целосна функционалност на задачата (5 поени)
 */
#include<iostream>
#include<string.h>
using namespace std;

class Delo{
    char ime[50];
    int godina;
    char zemja[50];
public:
    Delo(char *ime="", int godina=0, char *zemja=""){
        strcpy(this->ime, ime);
        this->godina=godina;
        strcpy(this->zemja, zemja);
    }
    void setIme(char *name){
        strcpy(ime, name);
    }
    void setGodina(int year){
        godina=year;
    }
    void setZemja(char *country){
        strcpy(zemja, country);
    }
    char *getIme(){
        return ime;
    }
    int getGodina(){
        return godina;
    }
    char *getZemja(){
        return zemja;
    }
    bool operator==(Delo &d){
        if(strcmp(ime, d.ime)==0) return true;
        else return false;
    }
};

class Pretstava{
protected:
    Delo delo;
    int brKarti;
    char data[15];
    int M;
    int N;
public:
    Pretstava(){}
    Pretstava(Delo d, int brKarti, char *data){
        this->delo=d;
        this->brKarti=brKarti;
        strcpy(this->data, data);
    }
    Delo getDelo(){
        return delo;
    }
    virtual int cena(){
        if(delo.getGodina()>=1900 && delo.getGodina()<=2099){
            M=50;
        }else if(delo.getGodina()>=1800 && delo.getGodina()<=1899){
            M=75;
        }else{
            M=100;
        }
        if(strcmp(delo.getZemja(),"Italija")==0){
            N=100;
        }else if(strcmp(delo.getZemja(),"Rusija")==0){
            N=150;
        }else{
            N=80;
        }
        return M+N;
    }
    int getKarti(){
        return brKarti;
    }
};

class Balet: public Pretstava{
    static int vrednost;
public:
    Balet(){}
    Balet(Delo d, int brKarti, char *data) : Pretstava(d, brKarti, data){}
    static void setCenaBalet(int cena){
        vrednost=cena;
    }
    int cena(){
        return Pretstava::cena()+vrednost;
    }
};
int Balet::vrednost=150;
class Opera: public Pretstava{
public:
    Opera(Delo d, int brKarti, char *data) : Pretstava(d, brKarti, data){}
};

int prihod(Pretstava **p, int n){
    int vkupno=0;
    for(int i=0;i<n;i++){
        Balet *b=dynamic_cast<Balet*>(p[i]);
        if(b!=0){
            vkupno+=b->cena()*b->getKarti();
        }else{
            vkupno+=p[i]->cena()*p[i]->getKarti();
        }
    }
    return vkupno;
}

int brojPretstaviNaDelo(Pretstava **p, int n, Delo d){
    int counter=0;
    for(int i=0;i<n;i++){
        if(p[i]->getDelo()==d){
            counter++;
        }
    }
    return counter;
}

//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}
