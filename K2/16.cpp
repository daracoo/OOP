/*
Туристичка агенција нуди различни понуди за транспорт на патници. За секоја понуда се чуваат податоци за дестинацијата (низа од знаци), основна цена (цел број) и податок за растојанието до дестинацијата изразено во km (цел број).

Од класата Transport да се изведат класите AvtomobilTransport и KombeTransport за моделирање на понудите за транспорт кои нудат транспорт со автомобил или комбе, соодветно. За секоја понуда за транспорт со автомобил се чува податок за тоа дали во понудата има платен шофер (булова променлива), а за транспорт со комбе бројот на луѓе кои може да се превезат во комбето (цел број). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

конструктор со аргументи што одговараат на податочните членови и set и get методи за податочните членови (5 поени)
метод cenaTransport, за пресметување на цената на понудата на следниот начин:
За транспорт со автомобил - основната цена се зголемува за 20% ако има платен шофер
За транспорт со комбе - основната цена ќе се намали зависно од бројот на патници во комбето. За секој патник во комбето цената се намалува за 200 (10 поени)
преоптоварен оператор < за споредба на две понуди за транспорт на патник според растојанието до дестинацијата. (5 поени)
Да се имплементира функција pecatiPoloshiPonudi што на влез прима низа од понуди за транспорт на патник, бројот на елементите од низата и една понуда T. Функцијата ја печати дестинацијата, растојанието до дестинацијата и цената за понудите од низата кои се поскапи од понудата T сортирани во растечки редослед по растојанието до дестинацијата (погледни го повикот на функцијата) (10 поени)

Комплетна функционалност на кодот (5 поени)
 */
#include <iostream>
#include <cstring>
using namespace std;

class Transport {
protected:
    char* destination;
    int price;
    int km;

    void copy_transport(const Transport& other) {
        this->destination = new char[strlen(other.destination) + 1];
        strcpy(this->destination, other.destination);
        this->price = other.price;
        this->km = other.km;
    }

public:
    Transport() {
        this->destination = new char[5];
        strcpy(this->destination, "dest");
        this->price = this->km = 0;
    }

    Transport(char* destination, int price, int km) {
        this->destination = new char[strlen(destination) + 1];
        strcpy(this->destination, destination);
        this->price = price;
        this->km = km;
    }

    Transport(const Transport& other) {
        copy_transport(other);
    }

    Transport& operator=(const Transport& other) {
        if(this == &other) {
            return *this;
        }
        delete [] destination;
        copy_transport(other);
        return *this;
    }

    friend ostream& operator<<(ostream& out, Transport& t) {
        out << t.destination << " " << t.km << " " << t.price << "\n";
        return out;
    }

    bool operator<(const Transport& other) {
        return km < other.km;
    }

    virtual float cenaTransport() {
        return price;
    }

    char* getDestination() {
        return destination;
    }

    int getKM() {
        return km;
    }

    ~Transport() {
        delete [] destination;
    }
};

class AvtomobilTransport : public Transport {
    bool driver;

public:
    AvtomobilTransport() : Transport() {
        this->driver = false;
    }

    AvtomobilTransport(char* destination, int price, int km, bool driver) : Transport(destination, price, km) {
        this->driver = driver;
    }

    AvtomobilTransport(const AvtomobilTransport& other) : Transport(other) {
        this->driver = other.driver;
    }

    AvtomobilTransport& operator=(const AvtomobilTransport& other) {
        if(this == &other) {
            return *this;
        }
        Transport::operator=(other);
        this->driver = other.driver;
        return *this;
    }

    float cenaTransport() {
        return driver ? price * 1.2 : price;
    }

    ~AvtomobilTransport() { }
};

class KombeTransport : public Transport {
    int passengers;

public:
    KombeTransport() : Transport() {
        this->passengers = 0;
    }

    KombeTransport(char* destination, int price, int km, int passengers) : Transport(destination, price, km) {
        this->passengers = passengers;
    }

    KombeTransport(const KombeTransport& other) : Transport(other) {
        this->passengers = other.passengers;
    }

    KombeTransport& operator=(const KombeTransport& other) {
        if(this == &other) {
            return *this;
        }
        Transport::operator=(other);
        this->passengers = other.passengers;
        return *this;
    }

    float cenaTransport() {
        return price - (passengers * 200);
    }

    ~KombeTransport() { }
};

void pecatiPoloshiPonudi(Transport** ponudi, int n, AvtomobilTransport t) {
    Transport** tmp = new Transport*[n];
    int k = 0;

    for(int i = 0; i < n; i++) {
        if(ponudi[i]->cenaTransport() > t.cenaTransport()) {
            tmp[k++] = ponudi[i];
        }
    }

    for(int i = 0; i < k - 1; i++) {
        for(int j = 0; j < k - i - 1; j++) {
            if(tmp[j]->getKM() > tmp[j + 1]->getKM()) {
                Transport* temp = tmp[j];
                tmp[j] = tmp[j + 1];
                tmp[j + 1] = temp;
            }
        }
    }

    for(int i = 0; i < k; i++) {
        cout << tmp[i]->getDestination() << " " << tmp[i]->getKM() << " " << tmp[i]->cenaTransport() << "\n";
    }
}

int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
