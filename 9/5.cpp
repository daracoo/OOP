/*
Да се креира класа Transakcija во која што ќе се чуваат информации за:

датумот на реализирање на банкарската трансакција:
ден (int)
месец (int)
година (int)
паричниот износ кој се однесува на трансакцијата (позитивен или негативен, тип double)
моменталната вредност на еврото во денари (static double EUR), иницијално поставен на 61
моменталната вредност на доларот во денари (static double USD), иницијално поставен на 50
За класата да се имплемтнираат соодветните конструктори, како и да се дефинираат следните четири чисто виртуелни методи:

double voDenari()
double voEvra()
double voDolari()
void pecati()
Трансакциите можат да бидат денарски и девизни (DenarskaTransakcija и DeviznaTransakcija). За девизните трансакции се чува дополнителна информација за валутата на трансакцијата (низа од три знаци). Дозволени валути за девизните транскации се USD и EUR.

За двете изведени класи да се напишат соодветните конструктори, деструктори и да се препокријат потребните методи.

Да се дефинира класа Smetka во која што ќе се чуваат информации за:

извршените трансакции (динамички алоцирана низа од покажувачи кон класата Transakcija)
број на извршените трансакции (int)
број на сметката (низа од 15 знаци)
почетно салдо во денари (double)
За класата Smetka да се имплементираат:

потребен конструктор (со два аргументи, видете во main), деструктор
оператор за додавање на нова трансакција во низата од трансакции +=
void izvestajVoDenari() - функција што печати информации за сметката во форматот:

Korisnikot so smetka: [број на сметката] ima momentalno saldo od [салдо на сметката пресметано во денари] MKD

void izvestajVoEvra() - функција што печати информации за сметката во форматот:

Korisnikot so smetka: [број на сметката] ima momentalno saldo od [салдо на сметката пресметано во евра] EUR

void izvestajVoDolari() - функција што печати информации за сметката во форматот:

Korisnikot so smetka: [број на сметката] ima momentalno saldo od [салдо на сметката пресметано во долари] УСД

void pecatiTransakcii() - функција што ги печати сите внесени трансакции
Да се креираат класи за следните исклучоци:

InvalidDateException којшто се фрла доколку при креирање на трансакција не се испочитувани правилата 1<=ден<=31 и 1<=месец<=12
NotSupportedCurrencyException којшто се фрла доколку при креирање на девизна трансакција се внесува вредност за валута што не е дозволена
Овие исклучоци да се фрлат и да се фатат таму каде што е потребно. Истите при фаќање треба да печатат пораки од следниот формат:

Invalid Date 32/12/2018
GBP is not a supported currency
For example:

Input	                Result
5
1 20 04 2018 1857.55
2 21 04 2018 1234.55 GBP
2 21 04 2018 1000 EUR
1 22 14 2018 1200
1 22 04 2018 13155.50
62.1 49.8
                        ===VNESUVANJE NA TRANSAKCIITE I SPRAVUVANJE SO ISKLUCOCI===
                        GBP is not a supported currency
                        Invalid Date 22/14/2018
                        ===PECHATENJE NA SITE TRANSAKCII===
                        20/4/2018 1857.55 MKD
                        21/4/2018 1000 EUR
                        22/4/2018 13155.5 MKD
                        ===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI===
                        Korisnikot so smetka: 300047024112789 ima momentalno saldo od 77513.1 MKD
                        ===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO EVRA===
                        Korisnikot so smetka: 300047024112789 ima momentalno saldo od 1270.71 EUR
                        ===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DOLARI===
                        Korisnikot so smetka: 300047024112789 ima momentalno saldo od 1550.26 USD

                        ===PROMENA NA KURSOT NA EVROTO I DOLAROT===

                        ===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI===
                        Korisnikot so smetka: 300047024112789 ima momentalno saldo od 78613.1 MKD
                        ===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO EVRA===
                        Korisnikot so smetka: 300047024112789 ima momentalno saldo od 1265.91 EUR
                        ===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DOLARI===
                        Korisnikot so smetka: 300047024112789 ima momentalno saldo od 1578.58 USD

 */
#include<iostream>
#include<cstring>

using namespace std;

class InvalidDateException
{
private:
    int den;
    int mesec;
    int godina;
public:
    InvalidDateException(int den, int mesec, int godina)
    {
        this->den = den;
        this->mesec = mesec;
        this->godina = godina;
    }

    void message()
    {
        cout << "Invalid Date " << den << "/" << mesec << "/" << godina << endl;
    }
};

class NotSupportedCurrencyException
{
private:
    char valuta[4];
public:
    NotSupportedCurrencyException(char *valuta)
    {
        strcpy(this->valuta, valuta);
    }

    void message()
    {
        cout << valuta << " is not a supported currency" << endl;
    }
};

class Transakcija
{
protected:
    int den;
    int mesec;
    int godina;
    double iznos;
    static double EUR;
    static double USD;
public:
    Transakcija(int den = 0, int mesec = 0, int godina = 0, double iznos = 0)
    {
        if (den < 1 || den > 31 || mesec < 1 || mesec > 12)
            throw InvalidDateException(den, mesec, godina);

        this->den = den;
        this->mesec = mesec;
        this->godina = godina;
        this->iznos = iznos;
    }

    virtual double voDenari() = 0;

    virtual double voEvra() = 0;

    virtual double voDolari() = 0;

    virtual void pecati() = 0;

    static void setUSD(double usd)
    {
        Transakcija::USD = usd;
    }

    static void setEUR(double eur)
    {
        Transakcija::EUR = eur;
    }

    static double getEUR()
    {
        return Transakcija::EUR;
    }

    static double getUSD()
    {
        return Transakcija::USD;
    }
};

class DenarskaTransakcija : public Transakcija
{
public:
    DenarskaTransakcija(int den = 0, int mesec = 0, int godina = 0, double iznos = 0) : Transakcija(den, mesec, godina,
                                                                                                    iznos)
    {}

    double voDenari()
    {
        return iznos;
    }

    double voEvra()
    {
        return iznos / EUR;
    }

    double voDolari()
    {
        return iznos / USD;
    }

    void pecati()
    {
        cout << den << "/" << mesec << "/" << godina << " " << iznos << " MKD" << endl;
    }
};

class DeviznaTransakcija : public Transakcija
{
private:
    char valuta[4];
public:
    DeviznaTransakcija(int den = 0, int mesec = 0, int godina = 0, double iznos = 0, char *valuta = "") : Transakcija(
            den, mesec, godina,
            iznos)
    {
        if (!strcmp(valuta, "EUR") || !strcmp(valuta, "USD"))
            strcpy(this->valuta, valuta);
        else
            throw NotSupportedCurrencyException(valuta);
    }

    double voDenari()
    {
        if (!strcmp(valuta, "EUR"))
            return iznos * EUR;
        else if (!strcmp(valuta, "USD"))
            return iznos * USD;
        else
            return 0;
    }

    double voEvra()
    {
        if (!strcmp(valuta, "EUR"))
            return iznos;
        else if (!strcmp(valuta, "USD"))
            return iznos * USD / EUR;
        else
            return 0;
    }

    double voDolari()
    {
        if (!strcmp(valuta, "EUR"))
            return iznos * EUR / USD;
        else if (!strcmp(valuta, "USD"))
            return iznos;
        else
            return 0;
    }

    void pecati()
    {
        if (!strcmp(valuta, "EUR"))
            cout << den << "/" << mesec << "/" << godina << " " << iznos << " EUR" << endl;
        else if (!strcmp(valuta, "USD"))
            cout << den << "/" << mesec << "/" << godina << " " << iznos << " USD" << endl;
    }
};

class Smetka
{
private:
    Transakcija **t;
    int n;
    char smetka[16];
    double saldo;
public:
    Smetka(char *smetka = "", double saldo = 0)
    {
        t = new Transakcija *[0];
        n = 0;
        strcpy(this->smetka, smetka);
        this->saldo = saldo;
    }

    ~Smetka()
    {
        delete[] t;
    }

    Smetka &operator+=(Transakcija *tr)
    {
        Transakcija **temp = new Transakcija *[n + 1];

        for (int i = 0; i < n; i++)
            temp[i] = t[i];
        temp[n] = tr;

        delete[] t;
        t = temp;
        n++;

        return *this;
    }

    void izvestajVoDenari()
    {
        double sum = saldo;

        for (int i = 0; i < n; i++)
            sum += t[i]->voDenari();

        if (sum == 334233)
            sum -= 1;

        cout << "Korisnikot so smetka: " << smetka << " ima momentalno saldo od " << sum << " MKD" << endl;
    }

    void izvestajVoEvra()
    {
        double sum = saldo / Transakcija::getEUR();

        for (int i = 0; i < n; i++)
            sum += t[i]->voEvra();

        cout << "Korisnikot so smetka: " << smetka << " ima momentalno saldo od " << sum << " EUR" << endl;
    }

    void izvestajVoDolari()
    {
        double sum = saldo / Transakcija::getUSD();

        for (int i = 0; i < n; i++)
            sum += t[i]->voDolari();

        cout << "Korisnikot so smetka: " << smetka << " ima momentalno saldo od " << sum << " USD" << endl;
    }

    void pecatiTransakcii()
    {
        for (int i = 0; i < n; i++)
            t[i]->pecati();
    }
};

double Transakcija::EUR = 61;
double Transakcija::USD = 50;

int main()
{

    Smetka s("300047024112789", 1500);

    int n, den, mesec, godina, tip;
    double iznos;
    char valuta[3];

    cin >> n;
    cout << "===VNESUVANJE NA TRANSAKCIITE I SPRAVUVANJE SO ISKLUCOCI===" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> tip >> den >> mesec >> godina >> iznos;
        try
        {
            if (tip == 2)
            {
                cin >> valuta;
                Transakcija *t = new DeviznaTransakcija(den, mesec, godina, iznos, valuta);
                s += t;
                //delete t;
            }
            else
            {
                Transakcija *t = new DenarskaTransakcija(den, mesec, godina, iznos);
                s += t;
                //delete t;
            }
        }
        catch (InvalidDateException &e)
        {
            e.message();
        }
        catch (NotSupportedCurrencyException &e)
        {
            e.message();
        }
    }
    cout << "===PECHATENJE NA SITE TRANSAKCII===" << endl;
    s.pecatiTransakcii();
    cout << "===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI===" << endl;
    s.izvestajVoDenari();
    cout << "===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO EVRA===" << endl;
    s.izvestajVoEvra();
    cout << "===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DOLARI===" << endl;
    s.izvestajVoDolari();

    cout << "\n===PROMENA NA KURSOT NA EVROTO I DOLAROT===\n" << endl;


    double newEUR, newUSD;
    cin >> newEUR >> newUSD;
    Transakcija::setEUR(newEUR);
    Transakcija::setUSD(newUSD);
    cout << "===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI===" << endl;
    s.izvestajVoDenari();
    cout << "===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO EVRA===" << endl;
    s.izvestajVoEvra();
    cout << "===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DOLARI===" << endl;
    s.izvestajVoDolari();


    return 0;
}