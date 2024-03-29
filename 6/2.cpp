/*
Да се дефинира класата Kvadrat во која што се чува информација за:

должината на страната а на квадратот (double)
За класата да се дефинираат:

default конструктор
конструктор со аргументи
copy конструктор
double perimetar () што пресметува периметар на квадратот
double plostina () што пресметува плоштина на квадратот
void pecati () што печати информации за квадратот како во тест примерите
Да се имплементира класа Pravoagolnik што наследува од класата Kvadrat. Во неа се чуваат дополнителни информации за:

проширувањето x на двете паралелни страни на квадратот (double)
проширувањето у на другите две паралелни страни (double)
Правоаголникот всушност сега ќе има 2 страни со должина a+x и две страни со должина a+y.

За класата да се дефинираат:

default конструктор
конструктор Pravoagolnik (const Kvadrat &k, double x, double y)
copy конструктор
Да се препокријат трите методи дефинирани погоре за класата Kvadrat.

Напомени:

Ако x и y се исти, тогаш формата не е правоаголник туку е повторно квадрат. Во тој случај pecati() се повикува исто како за квадрат.
При препокривање на методите во класата Pravoagolnik мора да има повик кон истоимените методи од класата Kvadrat
For example:

Input	Result
5
4.5
4
10
17.5
8.9
1 2
1.5 2.5
3 4.5
7 7
8 9
2
        ===Testiranje na klasata Pravoagolnik===
        Pravoagolnik so strani: 5.5 i 6.5 ima plostina P=35.75 i perimetar L=24
        Pravoagolnik so strani: 5.5 i 6.5 ima plostina P=35.75 i perimetar L=24
        Pravoagolnik so strani: 13 i 14.5 ima plostina P=188.5 i perimetar L=55
        Kvadrat so dolzina a=24.5 ima plostina P=600.25 i perimetar L=98
        Pravoagolnik so strani: 16.9 i 17.9 ima plostina
 */
#include <iostream>
#include <cstring>
using namespace std;

class Kvadrat{
protected:
    double a;
public:
    Kvadrat(double a=0.0){
        this->a=a;
    }
    Kvadrat(const Kvadrat &k){
        this->a=k.a;
    }
    double perimetar(){
        return 4*a;
    }
    double plostina(){
        return a*a;
    }
    void pecati(){
        cout<<"Kvadrat so dolzina a="<<a<<" ima plostina P="<<plostina()<<" i perimetar L="<<perimetar()<<endl;
    }
};

class Pravoagolnik : public Kvadrat{
    double x, y;
public:
    Pravoagolnik(double a=0.0, double x=0.0, double y=0.0) : Kvadrat(a){
        this->x=x;
        this->y=y;
    }
    Pravoagolnik(const Kvadrat &k, double x, double y) : Kvadrat(k){
        this->x=x;
        this->y=y;
    }
    Pravoagolnik(const Pravoagolnik &p) : Kvadrat(p){
        this->x=p.x;
        this->y=p.y;
    }
    double perimetar(){
        if(x==y){
            a=x+a;
            return Kvadrat::perimetar();
        }else{
            return (2*(a+x) + 2*(a+y));
        }
    }
    double plostina(){
        if(x==y){
            a=a+x;
            return Kvadrat::plostina();
        }else{
            return ((a+x) * (a+y));
        }
    }
    void pecati(){
        if(x==y){
            a=a+x;
            Kvadrat::pecati();
        }else{
            cout<<"Pravoagolnik so strani: "<<a+x<<" i "<<a+y<<" ima plostina P="<<plostina()<<" i perimetar L="<<perimetar()<<endl;
        }
    }
};

int main() {
    int n;
    double a,x,y;
    Kvadrat * kvadrati;
    Pravoagolnik * pravoagolnici;

    cin>>n;

    kvadrati = new Kvadrat [n];
    pravoagolnici = new Pravoagolnik [n];

    for (int i=0;i<n;i++){
        cin>>a;

        kvadrati[i] = Kvadrat(a);
    }

    for (int i=0;i<n;i++){
        cin>>x>>y;

        pravoagolnici[i]=Pravoagolnik(kvadrati[i],x,y);
    }

    int testCase;
    cin>>testCase;

    if (testCase==1){
        cout<<"===Testiranje na klasata Kvadrat==="<<endl;
        for (int i=0;i<n;i++)
            kvadrati[i].pecati();
    }
    else {
        cout<<"===Testiranje na klasata Pravoagolnik==="<<endl;
        for (int i=0;i<n;i++)
            pravoagolnici[i].pecati();
    }
}