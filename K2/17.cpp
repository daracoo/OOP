/*
Да се имплементира апстрактна класа FudblaskaEkipa во која се чува: (5 поени)

име на тренерот на екипата (максимум 100 знаци)
бројот на постигнати голови на последните 10 натпревари, последниот натпревар е на позиција 9, предпоследниот на позиција 8, итн (поле од 10 цели броеви)
Од класата FudblaskaEkipa да се изведат класите Klub и Reprezentacija. За секој клуб дополнително се чува податок за името и бројот на титули што ги има освоено, а за репрезентацијата се чуваат податоци за името на државата и вкупен број на меѓународни настапи. За овие класи да се имплементираат следните методи:

соодветен конструктор (5 поени)
оператор << за печатење на стандарден излез во формат [IME_NA_KLUB/DRZHAVA]\n[TRENER]\n[USPEH]\n (5 поени)
преоптоварен оператор+= за додавање на голови од последниот натпревар (внимавајте секогаш се чуваат головите само од последните 10 натпревари) (10 поени)
метод uspeh, за пресметување на успехот на тимот на следниот начин:
За Klub се пресметува како збир од збирот на головите од последните 10 натпревари помножен со 3 и бројот на титули помножен со 1000 (на пр. голови = {2, 0, 1, 3, 2, 0, 1, 4, 2, 3} и број на титули = 3, достигнување = 18 * 3 + 3 * 1000 = 3054)
За Reprezentacija како збир од збирот на головите од последните 10 натпревари помножен со 3 и бројот на меѓународни настапи помножен со 50 (на пр. голови = {2, 0, 1, 3, 2, 0, 1, 4, 2, 3} и број на меѓународни настапи=150, достигнување = 18 * 3 + 150 * 50 = 7554) (10 поени)
преоптоварен оператор > за споредба на две фудбласки екипи од каков било вид (клубови или репрезентации) според успехот (5 поени)
Да се имплементира функција najdobarTrener што на влез прима низа од покажувачи кон FudblaskaEkipa и големина на низата и го печати тимот со најголем успех (10 поени).
 */
#include <iostream>
#include <cstring>
using namespace std;

class FudbalskaEkipa
{
protected:
    char imeTrener[100];
    int pole[10];
public:
    FudbalskaEkipa(){}
    FudbalskaEkipa(char *imeTrener,int *pole)
    {
        strcpy(this->imeTrener,imeTrener);
        for(int i=0;i<10;i++)
        {
            this->pole[i]=pole[i];
        }
    }
    virtual ~FudbalskaEkipa(){}

    char *getImeTrener()
    {
        return imeTrener;
    }
    int *getPole()
    {
        return pole;
    }
    virtual int uspeh()=0;

    bool operator>(FudbalskaEkipa &f)
    {
        if(uspeh()>f.uspeh())
        {
            return true;
        }
        return false;
    }
    FudbalskaEkipa &operator+=(int num)
    {
        for(int i=1;i<10;i++)
        {
            pole[i-1]=pole[i];
        }
        pole[9]=num;
        return *this;
    }

};


class Klub:public FudbalskaEkipa
{
protected:
    char imeKlub[100];
    int brojTituli;
public:
    Klub(char *imeTrener,int *pole,char *imeKlub,int brojTituli):FudbalskaEkipa(imeTrener,pole)
    {
        this->brojTituli=brojTituli;
        strcpy(this->imeKlub,imeKlub);
    }
    ~Klub(){}

    char *getImeKlub()
    {
        return imeKlub;
    }
    int getBrojTituli()
    {
        return brojTituli;
    }
//    Klub &operator+=(int num)
//    {
//        pole[9]+=num;
//        return *this;
//    }
    int uspeh()
    {
        int total=0;
        for(int i=0;i<10;i++)
        {
            total+=pole[i];
        }
        total*=3;
        total+=(brojTituli*1000);
        return total;
    }

};


class Reprezentacija:public FudbalskaEkipa
{
protected:
    char imeDrzava[100];
    int nastapi;
public:
    Reprezentacija(char *imeTrener,int *pole,char *imeDrzava,int nastapi):FudbalskaEkipa(imeTrener,pole)
    {
        strcpy(this->imeDrzava,imeDrzava);
        this->nastapi=nastapi;
    }
    ~Reprezentacija(){}
    char *getImeDrzava()
    {
        return imeDrzava;
    }
    int getNastapi()
    {
        return nastapi;
    }
//    Reprezentacija &operator+=(int num)
//    {
//        pole[9]+=num;
//        return *this;
//    }
    int uspeh()
    {
        int total=0;
        for(int i=0;i<10;i++)
        {
            total+=pole[i];
        }
        total*=3;
        total+=(nastapi*50);
        return total;
    }

};


ostream &operator<<(ostream &out,FudbalskaEkipa &fe)
{
    Reprezentacija *r=dynamic_cast<Reprezentacija *>(&fe);
    if(r!=0)
    {
        out<<r->getImeDrzava()<<endl;
        out<<r->getImeTrener()<<endl;
        out<<r->uspeh()<<endl;
    }
    Klub *k=dynamic_cast<Klub *>(&fe);
    if(k!=0)
    {
        cout<<k->getImeKlub()<<endl;
        cout<<k->getImeTrener()<<endl;
        cout<<k->uspeh()<<endl;
    }
    return out;
}

void najdobarTrener(FudbalskaEkipa **ekipa,int n)
{
    int inx=0;
    for(int i=1;i<n;i++)
    {
        if(*ekipa[i]>*ekipa[inx])
        {
            inx=i;
        }
    }
    cout<<*ekipa[inx];
}


int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}