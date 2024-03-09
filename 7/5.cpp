/*
Да се креира хиерархиjа на класи за репрезентациjа на жичани инструменти. За потребите на оваа хиерархиjа да се дефинира класа ZicanInstrument од коjа ќе бидат изведени двете класи Mandolina и Violina.

Во класата ZicanInstrument се чуваат податоци за:

името на инструментот (низа од 20 знаци)
броjот на жици
основната цена на инструментот.
За класата Mandolina дополнително се чува неjзината форма (низа од 20 знаци).

За класата Violina дополнително се чува неjзината големина (децимален броj).

За секоjа изведените класи треба да се дефинираат соодветните конструктори и следните методи:

cena() за пресметување на цената на инструментот
основната цена на мандолината се зголемува за 15% доколку таа има форма во Неаполитански стил (вредноста на променливата форма е “Neapolitan”)
основната цена на виолината се зголемува за 10% ако неjзината големина има вредност 1/4 (0.25), односно за 20% ако неjзината големина има вредност 1 (1.00)
проптоварување на операторот ==, коj ги споредува жичаните инструменти според броjот на жици што го имаат
преоптоварување на операторот << за печатење на сите податоци за жичаните инструменти.
Да се напише функциjа pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **i, int n) коjа на влез прима жичан инструмент, низа од покажувачи кон жичани инструменти и броj на елементи во низата. Функциjата jа печати цената на сите жичани инструменти од низата кои имаат ист броj на жици како и инструментот проследен како прв аргумент на функциjата.

For example:

Input	                        Result
Mandolina_1 10 5000 Nepoznata
2
Mandolina_2 5 3000 Prava
Mandolina_3 10 8000 Neapolitan
Violina_1 10 4000 0.25
Violina_2 10 6000 0.8
                                9200
                                4400
                                6000
 */
#include<iostream>
#include<cstring>
using namespace std;

class ZicanInstrument{
protected:
    char ime[20];
    int brZici;
    int osnovnaCena;
public:
    ZicanInstrument(char *ime="", int brZici=0, int osnovnaCena=0){
        strcpy(this->ime, ime);
        this->brZici=brZici;
        this->osnovnaCena=osnovnaCena;
    }
    virtual double cena()=0;

    friend bool operator ==(ZicanInstrument *z1,ZicanInstrument &z2)
    {
        if(z1->getBroj() == z2.getBroj())
            return true;
        return false;
    }

    friend ostream &operator<<(ostream &out, ZicanInstrument *z){
        out<<z->ime<<" "<<z->brZici<<" "<<z->osnovnaCena<<endl;
        return out;
    }
    int getBroj(){
        return brZici;
    }
};

class Mandolina: public ZicanInstrument{
    char forma[20];
public:
    Mandolina(char *ime="", int brZici=0, float cena=0.0, char *forma="") : ZicanInstrument(ime, brZici, cena){
        strcpy(this->forma, forma);
    }
    double cena(){
        if(strcmp(forma, "Neapolitan")==0){
            return osnovnaCena * 1.15;
        }
        return osnovnaCena;
    }
    friend ostream & operator <<(ostream &out,Mandolina &m)
    {
        out<<m.ime<<" " <<m.brZici<<" " <<m.cena()<<" " <<m.forma<<endl;
        return out;
    }
};

class Violina: public ZicanInstrument{
    double golemina;
public:
    Violina(char *ime="", int brZici=0, float cena=0.0, double golemina=0.0) : ZicanInstrument(ime, brZici, cena){
        this->golemina=golemina;
    }
    double cena(){
        if(golemina==0.25){
            return osnovnaCena*1.1;
        }
        if(golemina==1.0){
            return osnovnaCena*1.2;
        }
        return osnovnaCena;
    }
    friend ostream & operator <<(ostream &out,Violina &v)
    {
        out<<v.ime<<" " <<v.brZici<<" " <<v.cena()<<" " <<v.golemina<<endl;
        return out;
    }
};
void pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **z, int n){
    for(int i=0;i<n;i++){
        if(z[i]==zi){
            Mandolina *m=dynamic_cast<Mandolina*>(z[i]);
            if(m!=0){
                cout<<m->cena()<<endl;
            }
            Violina *v=dynamic_cast<Violina*>(z[i]);
            if(v != 0)
            {
                cout<<v->cena()<<endl;
            }
        }
    }
}
void pecati(ZicanInstrument **niza, int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<niza[i]<<endl;
    }
}
int main() {
    char ime[20];
    int brojZici;
    float cena;
    char forma[20];
    cin >> ime >> brojZici >> cena >> forma;
    Mandolina m(ime, brojZici, cena, forma);
    int n;
    cin >> n;
    ZicanInstrument **zi = new ZicanInstrument*[2 * n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> brojZici >> cena >> forma;
        zi[i] = new Mandolina(ime, brojZici, cena, forma);
    }
    for(int i = 0; i < n; ++i) {
        float golemina;
        cin >> ime >> brojZici >> cena >> golemina;
        zi[n + i] = new Violina(ime, brojZici, cena, golemina);
    }
    pecatiInstrumenti(m, zi, 2 * n);
    for(int i = 0; i < 2 * n; ++i) {
        delete zi[i];
    }
    delete [] zi;
    return 0;
}
