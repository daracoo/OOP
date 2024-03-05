/*
Да се дефинира класа Flight во која што ќе се чуваат податоци за лет:

име на лет (динамички алоцирана низа од знаци)
полетување од (динамички алоцирана низа од знаци)
пристигнување во (динамички алоцирана низа од знаци)
цена на лет (цел број)
За класата да се дефинира copy конструктор, default конструктор, конструктор со аргументи и да се преоптоварат следните оператори:

оператор << за печатење во формат ([flight_name] [from] [to] [price])
оператор = за доделување на вредности
оператор == за споредување на 2 летови според името
Потоа да се креира класа Airport во која што се чуваат следните податоци:

име на аеродром (низа од максимум 50 карактери)
број на летови на аеродромот(цел број)
низа од летови на аеродромот(динамичка низа од објекти од Flight класата)
Да се креира конструктор со аргументи за класата, конструктор без аргументи и да се преоптоварат следните оператори:

оператор += за додавање на нов лет
оператор -= за бришење на лет (според името се брише)
оператор << за печатење во формат: [airport_name] и летовите.
Да се креира метод void printBelowPrice(int) ги печати летовите кои се под внесената цена.

ДА НЕ СЕ МЕНУВА MAIN ФУНКЦИЈАТА.


For example:

Input	                            Result
1
                                    TESTING FLIGHT CLASS CONSTRUCTORS
                                    OS776 SKOPJE(SKP) VIENNA(VIE) 100
                                    TESTING FLIGHT CLASS OPERATORS
                                    OS776 SKOPJE(SKP) VIENNA(VIE) 100
3
3
OS776 SKOPJE(SKP) VIENNA(VIE) 100
W67719 SKOPJE(SKP) PARIS(BVA) 70
LTNSKP112 LONDON(LTN) SKOPJE(SKP) 150
                                    TESTING AIRPORT OPERATOR +=
                                    SkopjeInternationalAirport
                                    OS776 SKOPJE(SKP) VIENNA(VIE) 100
                                    W67719 SKOPJE(SKP) PARIS(BVA) 70
                                    LTNSKP112 LONDON(LTN) SKOPJE(SKP) 150

 */
#include <iostream>
#include <cstring>

using namespace std;

class Flight {
private:
    char *name;
    char *from;
    char *to;
    int price;
public:
    Flight() {
        name = nullptr;
        from = nullptr;
        to = nullptr;
        price = 0;
    }

    Flight(char *name, char *from, char *to, int price) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->from = new char[strlen(from) + 1];
        strcpy(this->from, from);
        this->to = new char[strlen(to) + 1];
        strcpy(this->to, to);
        this->price = price;
    }

    Flight(const Flight &f) {
        this->name = new char[strlen(f.name) + 1];
        strcpy(this->name, f.name);
        this->from = new char[strlen(f.from) + 1];
        strcpy(this->from, f.from);
        this->to = new char[strlen(f.to) + 1];
        strcpy(this->to, f.to);
        this->price = f.price;
    }

    Flight &operator=(const Flight &f) {
        if (this != &f) {
            delete[] name;
            delete[] from;
            delete[] to;
            this->name = new char[strlen(f.name) + 1];
            strcpy(this->name, f.name);
            this->from = new char[strlen(f.from) + 1];
            strcpy(this->from, f.from);
            this->to = new char[strlen(f.to) + 1];
            strcpy(this->to, f.to);
            this->price = f.price;
        }

        return *this;
    }

    friend ostream &operator<<(ostream &out, const Flight &f) {
        out << f.name << " ";
        out << f.from << " ";
        out << f.to << " ";
        out << f.price << endl;
        return out;
    }

    bool operator<=(const Flight &f1) const {
        return this->price <= f1.price;
    }

    friend bool operator==(const Flight &f1, const Flight &f2){
        return strcmp(f1.name, f2.name)==0;
    }

    ~Flight() {
        delete[] name;
        delete[] from;
        delete[] to;
    }


    int getPrice() {
        return this->price;
    }
};

class Airport {
    char name[100];
    int num_flights;
    Flight *flights;
public:
    Airport() {
        strcpy(name, "");
        num_flights = 0;
        flights= nullptr;
    }

    Airport(char *name) {
        strcpy(this->name, name);
        this->num_flights = 0;
        flights = nullptr;
    }

    Airport(const Airport &a) {
        strcpy(this->name, a.name);
        this->num_flights = a.num_flights;
        for (int i = 0; i < this->num_flights; i++) {
            this->flights[i] = a.flights[i];
        }
    }

    Airport &operator=(const Airport &a) {
        if (this != &a) {
            strcpy(this->name, a.name);
            this->num_flights = a.num_flights;
            for (int i = 0; i < this->num_flights; i++) {
                this->flights[i] = a.flights[i];
            }
        }
        return *this;
    }

    Airport &operator+=(const Flight &flight) {
        Flight *tmp = new Flight[this->num_flights + 1];
        for (int i = 0; i < num_flights; i++) {
            tmp[i] = flights[i];
        }
        tmp[num_flights] = flight;
        num_flights++;
        delete[] flights;
        flights = tmp;
        return *this;
    }
    Airport &operator-=(const Flight &flight) {
        Flight *tmp = new Flight[this->num_flights - 1];
        int j = 0;
        for (int i = 0; i < num_flights; i++) {
            if (!(flights[i] == flight)) {
                tmp[j++] = flights[i];
            }
        }
        delete[] flights;
        flights = tmp;
        num_flights = j;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Airport &a){
        out<<a.name<<endl;
        for(int i=0;i<a.num_flights;i++){
            out<<a.flights[i];
        }
        return out;
    }

    void printBelowPrice(int price){
        for(int i=0;i<num_flights;i++){
            if(flights[i].getPrice()<=price){
                cout<<flights[i];
            }
        }
    }

    ~Airport() {
        delete[] flights;
    }

};

int main() {
    int testCase;

    cin>>testCase;

    if(testCase==1){
        cout<<"TESTING FLIGHT CLASS CONSTRUCTORS"<<endl;

        Flight flight = Flight("OS776", "SKOPJE(SKP)" , "VIENNA(VIE)", 100);

        cout<<flight;

        cout<<"TESTING FLIGHT CLASS OPERATORS"<<endl;

        Flight flight1 = Flight("OS776", "SKOPJE(SKP)" , "VIENNA(VIE)", 100);
        if(flight==flight1){
            cout<<flight;
        }
        else{
            cout<<"Ne se isti letovi";
        }
    }
    else if(testCase==2){
        cout<<"TESTING FLIGHT CLASS CONSTRUCTORS"<<endl;

        Flight flight = Flight("LTNSKP112", "LONDON(LTN)" ,"SKOPJE(SKP)", 200);

        cout<<flight;

        cout<<"TESTING FLIGHT CLASS OPERATORS"<<endl;

        Flight flight1 = Flight("IATA110", "SKOPJE(SKP)", "ISTANBUL(IST)" , 80);
        if(flight==flight1){
            cout<<flight;
        }
        else{
            cout<<"Ne se isti letovi";
        }
    }
    else if(testCase==3){
        Airport airport("SkopjeInternationalAirport");
        int n;
        cin>>n;

        for (int i=0;i<n;i++)
        {
            char name[100];
            char from[100];
            char to[100];
            int price;

            cin >> name;
            cin >> from;
            cin >> to;
            cin >> price;

            Flight f=Flight(name, from, to, price);

            //dodavanje na let
            airport+=f;

        }

        cout<<"TESTING AIRPORT OPERATOR +="<<endl;

        cout<<airport;
    }
    else if(testCase==4){
        Airport airport("JohnF.Kennedy");
        int n;
        cin>>n;

        for (int i=0;i<n;i++)
        {
            char name[100];
            char from[100];
            char to[100];
            int price;

            cin >> name;
            cin >> from;
            cin >> to;
            cin >> price;

            Flight f=Flight(name, from, to, price);

            //dodavanje na let
            airport+=f;

        }

        cout<<"TESTING AIRPORT OPERATOR -="<<endl;

        //se cita greshen let, za koj shto letot so isto ime treba da se izbrishe
        char name[100];
        char from[100];
        char to[100];
        int price;

        cin >> name;
        cin >> from;
        cin >> to;
        cin >> price;

        Flight greshka=Flight(name, from, to, price);

        //brishenje na let
        airport-=greshka;

        cout<<airport;
    }
    else if(testCase==5){
        Airport airport("Beauvais–Tillé-Airport");
        int n;
        cin>>n;

        for (int i=0;i<n;i++)
        {
            char name[100];
            char from[100];
            char to[100];
            int price;

            cin >> name;
            cin >> from;
            cin >> to;
            cin >> price;

            Flight f=Flight(name, from, to, price);

            //dodavanje na let
            airport+=f;

        }

        cout<<"TESTING AIRPORT OPERATOR -= AND PRINTBELOWPRICE METHOD"<<endl;

        //se cita grehsen let, za koj shto let so isto ime treba da se izbrishe
        char name[100];
        char from[100];
        char to[100];
        int price;

        cin >> name;
        cin >> from;
        cin >> to;
        cin >> price;

        Flight greshka=Flight(name, from, to, price);

        //brishenje na let
        airport-=greshka;

        airport.printBelowPrice(80);
    }


    return 0;
}