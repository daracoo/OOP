/*
Да се креира класа за опишување на еден сервис за мобилни уреди. За секој мобилен телефон се чуваат податоци за модел (низа од 100 знаци), тип на уред (смартфон или компјутер), потребни часови за основна проверка (децимален број), година на производство (цел број). (5 поени)

Сите уреди имаат исто времетраење за основна проверка и истата изнесува 1 час. Оваа вредност може да се смени со одлука на сервисот. Дополнително, уредите кои се понови од 2015 година имаат потреба од дополнителени 1.5 часа за проверка. При проверка, лаптопите имаат потреба од дополнителни 2 часа за софтверска дијагностика (5 поени).

За оваа класа да се имплементира оператор << за печатење на уред во формат:

[modelnauredotl]
[tipnaured] [casovizaproverka]

Каде часовите за проверка се оние од основната проверка+ дополнителни 2 часа доколку уредот е понов од 2015 + 2 часа доколу уредот е лаптоп (5 поени)

Да се креира класа MobileServis во која се чува адреса (низа од 100 знаци), низа од уреди (динамички алоцирана низа) и број на уреди.(5 поени)

За класата да се обезбедат:

operatoror+= за додавање на нов уред во сервисот.(5 поени) Не смее да се дозволи годината на производство на уредот да биде поголема од 2019 или помала од 2000. Ако се направи обид за додавање на уред со невалидна година, треба да се генерира исклучок InvalidProductionDate. (10 поени)

Функција pecatiUredi со која се печатат сите уреди со времето потребно за нивната проверка во сервисот (5 поени).

Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (5 поени)
 */
#include <iostream>
#include <cstring>
using namespace std;

enum tip{Mobilen,laptop};


class InvalidProductionDate
{
public:
    void message()
    {
        cout<<"Невалидна година на производство"<<endl;//treba vo kirilica
    }
};

class Device
{
private:
    char ime[100];
    tip tipDevice;
    double proverka;
    int godina;
    static double servis;
    double extraServis;

public:
    Device(){}
    Device(char *ime,tip tipDevice,int godina)
    {
        strcpy(this->ime,ime);
        this->tipDevice=tipDevice;
        this->godina=godina;
        setExtraServis();
    }
    ~Device(){}
    static void setPocetniCasovi(double num)
    {
        servis=num;
    }


    void setExtraServis()
    {
        extraServis=servis;
        if(godina>2015)
            extraServis+=2;//1.5
        if(tipDevice==laptop)
        {
            extraServis+=2;
        }
    }
    int getGodina()
    {
        return godina;
    }

    friend ostream &operator<<(ostream &out,Device &d)
    {
        d.setExtraServis();

        out<<d.ime<<endl;
        if(d.tipDevice==laptop)
        {
            out<<"Laptop ";
        }
        else
        {
            out<<"Mobilen ";
        }
        out<<d.extraServis<<endl;
        return out;
    }

};
double Device::servis=1;


class MobileServis
{
protected:
    char ime[100];//adresa
    Device *uredi;
    int brojUredi;

    void copy_func(const MobileServis &m)
    {
        strcpy(ime,m.ime);
        brojUredi=m.brojUredi;
        uredi=new Device[brojUredi];
        for(int i=0;i<brojUredi;i++)
        {
            uredi[i]=m.uredi[i];
        }
    }
public:
    MobileServis(char *ime)
    {
        strcpy(this->ime,ime);
        uredi=NULL;
        brojUredi=0;
    }
    ~MobileServis()
    {
        delete [] uredi;
    }
    MobileServis(const MobileServis &m)
    {
        copy_func(m);
    }
    MobileServis &operator=(const MobileServis &m)
    {
        if(this!=&m)
        {
            delete [] uredi;
            copy_func(m);
        }
        return *this;
    }

    MobileServis &operator+=(Device &d)
    {
        if(d.getGodina()<2000 || d.getGodina()>2019)
        {
            throw InvalidProductionDate();
        }
        Device *tmp=new Device[brojUredi+1];
        for(int i=0;i<brojUredi;i++)
        {
            tmp[i]=uredi[i];
        }
        tmp[brojUredi]=d;
        brojUredi++;
        delete [] uredi;
        uredi=tmp;
        return *this;
    }
    void pecatiCasovi()//pecatiUredi
    {
        cout<<"Ime: "<<ime<<endl;
        for(int i=0;i<brojUredi;i++)
        {
            cout<<uredi[i];
        }
    }

};

int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &i)
            {
                i.message();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &i)
            {
                i.message();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &i)
            {
                i.message();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch(InvalidProductionDate &i)
            {
                i.message();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
//            cout<<tmp;
            }
            catch(InvalidProductionDate &i)
            {
                i.message();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t.pecatiCasovi();
    }

    return 0;

}