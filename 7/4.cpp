/*
Да се дефинира класа Vozilo која ќе содржи информација за неговата маса (децимален број), ширина и висина (цели броеви).

Од оваа класа да се изведе класата Автомобил во која како дополнителна информација се чува информацијата за бројот на врати (цел број).

Од класата возило да се изведе и класата Автобус во која се чуваат информации и за бројот на патници кои може да ги пренесува.

Од класата возило да се изведе класата Камион во која се чуваат информации и за максималната маса која може да се товари на него (децимална вредност).

За сите класи да се креираат погодни контруктори, како и set и get функции.

Да се дефинира класа ParkingPlac за која се чува динамичко алоцирано поле од покажувачи кон Vozilo, како и бројот на елементи во полето. Во оваа класа да се дефинираат:

конструктор
деструктор
операторот += за додавање на ново возило (аргументот е покажувач кон Vozilo)
функција float presmetajVkupnaMasa() со која се пресметува вкупната маса на сите возила во паркинг плацот
функција int brojVozilaPoshirokiOd(int l) со која се пресметува бројот на возила кои се пошироки од дадената вредност
функција void pecati() со која се печати: Brojot na avtomobili e X, brojot na avtobusi e Y i brojot na kamioni e Z.
функција int pogolemaNosivostOd(Vozilo& v) во која се враќа бројот на сите камиони кои имаат носивост поголема од масата на возилото предадено како аргумент.
Да се дефинира виртуелна функција int vratiDnevnaCena() во класата Vozilo и истата да се преоптовари во сите изведени класи. За секој автомобил со помалку од 5 врати дневната цена е 100, а инаку е 130 денари. За секој камион цената се пресметува со формулата: (masa+nosivost)*0.02. За секој автобус цената е 5 денари по лице кое може да се пренесува.

Во класата ParkingPlac да се додаде следната функција: - функција int vratiDnevnaZarabotka() со која се враќа дневната заработка од сите возила на паркингот.

For example:

Input	        Result
5
1 1300 3 2 3
2 4500 10 4 45
3 6000 8 5 2000
1 2100 3 3 5
2 4200 9 5 52
                Brojot na avtomobili e 2, brojot na avtobusi e 2 i brojot na kamioni e 1.

                Zarabotkata e 875
                Vkupnata masa e 18100
                Brojot poshiroki od 5 e 3
                Brojot na kamioni so nosivost pogolema od avtomobilot e 1
 */
#include<iostream>
#include<cstring>
using namespace std;

class Vozilo{
protected:
    float masa;
    int sirina;
    int visina;
public:
    Vozilo(float masa=0.0, int sirina=0, int visina=0){
        this->masa=masa;
        this->sirina=sirina;
        this->visina=sirina;
    }
    virtual int vratiDnevnaCena() = 0;
    void setMasa(float masa){
        this->masa=masa;
    }
    void setSirina(int sirina){
        this->sirina=sirina;
    }
    void setVisina(int visina){
        this->visina=visina;
    }
    float getMasa(){
        return masa;
    }
    int getSirina(){
        return sirina;
    }
    int getVisina(){
        return visina;
    }
};

class Avtomobil: public Vozilo{
    int brVrati;
public:
    Avtomobil(float masa=0.0, int sirina=0, int visina=0, int brVrati=0) : Vozilo(masa, sirina, visina){
        this->brVrati=brVrati;
    }
    int vratiDnevnaCena(){
        if(brVrati<5){
            return 100;
        }else{
            return 130;
        }
    }
};

class Avtobus: public Vozilo{
    int brPatnici;
public:
    Avtobus(float masa=0.0, int sirina=0, int visina=0, int brPatnici=0) : Vozilo(masa, sirina, visina){
        this->brPatnici=brPatnici;
    }
    int vratiDnevnaCena(){
        return brPatnici*5;
    }
};

class Kamion: public Vozilo{
    float nosivost;
public:
    Kamion(float masa=0.0, int sirina=0, int visina=0, float nosivost=0.0) : Vozilo(masa, sirina, visina){
        this->nosivost=nosivost;
    }
    int vratiDnevnaCena(){
        return (getMasa()+nosivost)*0.02;
    }
};

class ParkingPlac{
    Vozilo **vozila;
    int brVozila;
public:
    ParkingPlac(Vozilo *vozila=0, int brVozila=0){
        this->brVozila=0;
        this->vozila= new Vozilo*[0];
    }
    ~ParkingPlac(){
        delete[]vozila;
    }
    ParkingPlac &operator+=(Vozilo *v){
        Vozilo **tmp = new Vozilo * [brVozila+1];
        for(int i=0;i<brVozila;i++){
            tmp[i]=vozila[i];
        }
        tmp[brVozila++]=v;
        delete[]vozila;
        vozila=tmp;
        return *this;
    }
    float presmetajVkupnaMasa(){
        float suma=0.0;
        for(int i=0;i<brVozila;i++){
            suma+=vozila[i]->getMasa();
        }
        return suma;
    }
    int brojVozilaPoshirokiOd(int l){
        float counter=0.0;
        for(int i=0;i<brVozila;i++){
            if(vozila[i]->getSirina()>l){
                counter++;
            }
        }
        return counter;
    }
    void pecati(){
        int counterA=0, counterB=0, counterK=0;
        for(int i=0;i<brVozila;i++){
            Avtomobil *a = dynamic_cast<Avtomobil*>(vozila[i]);
            if(a!=0){
                counterA++;
                continue;
            }
            Avtobus *b = dynamic_cast<Avtobus*>(vozila[i]);
            if(b!=0){
                counterB++;
                continue;
            }
            Kamion *k = dynamic_cast<Kamion*>(vozila[i]);
            if(k!=0){
                counterK++;
                continue;
            }
        }
        cout<<"Brojot na avtomobili e "<<counterA<<", brojot na avtobusi e "<<counterB<<" i brojot na kamioni e "<<counterK<<"."<<endl;
    }
    int vratiDnevnaZarabotka(){
        int suma=0;
        for(int i=0;i<brVozila;i++){
            suma+=vozila[i]->vratiDnevnaCena();
        }
        return suma;
    }
    int pogolemaNosivostOd(Vozilo &v){
        int counter=0;
        for(int i=0;i<brVozila;i++){
            Kamion *k = dynamic_cast<Kamion*>(vozila[i]);
            if(k!=0){
                if(k->getMasa()>v.getMasa()){
                    counter++;
                }
            }
        }
        return counter;
    }
};

int main(){
    ParkingPlac p;

    int n;
    cin>>n;
    int shirina,visina, broj;
    float masa,nosivost;
    for (int i=0;i<n;i++){
        int type;
        cin>>type;
        if(type==1){
            cin>>masa>>shirina>>visina>>broj;
            Avtomobil *a=new Avtomobil(masa,shirina,visina,broj);
            p+=a;
        }
        if(type==2){
            cin>>masa>>shirina>>visina>>broj;
            p+=new Avtobus(masa,shirina,visina,broj);
        }
        if(type==3){
            cin>>masa>>shirina>>visina>>nosivost;
            p+=new Kamion(masa,shirina,visina,nosivost);
        }
    }

    p.pecati();

    cout<<"\nZarabotkata e "<<p.vratiDnevnaZarabotka()<<endl;
    cout<<"Vkupnata masa e "<<p.presmetajVkupnaMasa()<<endl;
    cout<<"Brojot poshiroki od 5 e "<<p.brojVozilaPoshirokiOd(5)<<endl;
    Avtomobil a(1200,4,3,5);
    cout<<"Brojot na kamioni so nosivost pogolema od avtomobilot e "<<p.pogolemaNosivostOd(a)<<endl;


}
