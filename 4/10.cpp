/*
а да се овозможи прецизна контрола и евиденција во еден аеродромски сервис, потребно е да се имплементира модул со следниве класи и функционалности:

Да се имплементира класа Airplane во која ќе се чуваат информации за:

Регистарска ознака (низа од најмногу 12 знаци)
Име на авиокомпанија која го поседува авионот (динамички алоцирана низа од знаци)
Матичен аеродром на авиокомпанијата (низа од најмногу 20 знаци)
Состојба (авионот може да се најде во состојба НЕИСПРАВЕН, СЕ_ПОПРАВА или ИСПРАВЕН)
Вкупен број на часови налет (цел број)
За класата да се имплементираат потребните конструктори, оператор = и методи за да функционира решението. (10 поени). Дополнително за класата да се имплементира метод void print() за печатење на информациите за авионот (според тест примерите). (5 поени)

Да се имплементира класа AirportService во која ќе се чуваат информации за:

Име на аеродромот каде се наоѓа сервисот (низа од најмногу 20 знаци)
Листа на авиони кои моментално се наоѓаат во сервисот (динимички алоцирана низа од објекти од класата Airplane, иницијално без елементи)
Број на авиони во сервисот (број на елементи во низата со авиони - цел број, иницијално е 0)
За класата да се имплементираат потребните конструктори и методи со цел да функционира решението. (5 поени) Дополнително во класата да се имплементираат:

метод void addAirplane (Airplane plane) - за додавање нoв авион во сервисот (5 поени). Еден авион може да се додаде во сервисот само ако се наоѓа во состојба НЕИСПРАВЕН. Дополнително, ако веќе во сервисот има авион од иста авиокомпанија како авионот кој сакаме да го додадеме, потребно е во сервисот да остане авионот со поголем број на часови налет. Кога авион се додава во сервисот неговата состојба преминува во состојба СЕ_ПОПРАВА (10 поени).
метод Airplane serviceOldestAirplane() - за сервисирање на најстариот авион. За најстар авион се смета оној авион од листата кој има најмногу часови налет. Сервисирањето на еден авион претствува:

Потребно е авионот да биде избришан од листата со авиони во сервисот
Авионот треба да премине од состојба СЕ_ПОПРАВА во состојба ИСПРАВЕН
Доколку има повеќе авиони со ист број на часови налет при одредувањето на најстар авион, тогаш потребно е да се избрише авионот чиј што матичен аеродром на авиокомпанијата на авионот е аеродромот каде што се наоѓа сервисот. Во ваква ситуација, секогаш само еден од авионите ќе има ист матичен аеродром со аеродромот на сервисот.  (15 поени)
метод void print() - за печатење на информации за сите авиони кои моментално се наоѓаат на поправка во сервисот (формат во тест примери) (10 поени)
For example:

Input	        Result
3
ZHN-96-RT
FINKI-Airline
MF
50
2
                TESTING PRINT() FOR AIRPLANE
                ID: ZHN-96-RT - WORKING FINKI-Airline, 50, MF
                5
                2
                ZHN-96-RT
                FINKI-Airline
                MF
                50
                0
                ZHN-96-RA
                F-Airline
                TMF
                50
                1
                TESTING ADD() AND PRINT() FOR AIRPORTSERVICE
                FINKI
                ID: ZHN-96-RT - REPAIRING FINKI-Airline, 50, MF
 */
#include <iostream>
#include <cstring>
using namespace std;

enum state{
    NOT_WORKING, REPAIRING, WORKING
};

class Airplane{
private:
    char ID[12];
    char *company_name;
    char company_airport[20];
    int flight_hours;
    state s;
public:
    Airplane(char *ID="", char *company_name="", char *company_airport="", int flight_hours=0, int ss = 0){
        this->company_name = new char[strlen(company_name)+1];
        strcpy(this->company_name, company_name);
        strcpy(this->ID, ID);
        strcpy(this->company_airport, company_airport);
        this->flight_hours=flight_hours;
        s=(state)ss;
    }
    Airplane(const Airplane &a){
        this->company_name = new char[strlen(a.company_name)+1];
        strcpy(this->company_name, a.company_name);
        strcpy(this->ID, a.ID);
        strcpy(this->company_airport, a.company_airport);
        this->flight_hours=a.flight_hours;
        s=a.s;
    }
    Airplane &operator=(const Airplane &a){
        if(this!=&a){
            delete [] company_name;
            this->company_name = new char[strlen(a.company_name)+1];
            strcpy(this->company_name, a.company_name);
            strcpy(this->ID, a.ID);
            strcpy(this->company_airport, a.company_airport);
            this->flight_hours=a.flight_hours;
            s=a.s;
        }
        return *this;
    }
    ~Airplane(){
        delete [] company_name;
    }
    void print(){
        cout<<"ID: "<<ID<<" - ";
        if(s==0)
        {
            cout<<"NOT_WORKING ";
        }
        else if(s==1)
        {
            cout<<"REPAIRING ";
        }
        else cout <<"WORKING ";
        cout<<company_name<<", "<<flight_hours<<", "<<company_airport<<endl;
    }
    state get_state(){
        return s;
    }
    char *get_company_name(){
        return company_name;
    }
    int get_flight_hours(){
        return flight_hours;
    }
    char *get_airport_name(){
        return company_airport;
    }
    void set_state(int k){
        s = (state)k;
    }
};

class AirportService{
private:
    char airport_name[20];
    Airplane *arr;
    int n;
public:
    AirportService(char *airport_name=""){
        strcpy(this->airport_name, airport_name);
        arr = new Airplane[0];
        n=0;
    }
    AirportService(const AirportService &a){
        strcpy(this->airport_name, a.airport_name);
        n=a.n;
        arr = new Airplane[n];
        for(int i=0; i<n; i++){
            arr[i] = a.arr[i];
        }
    }
    AirportService &operator=(const AirportService &a){
        if(this!=&a){
            delete [] arr;
            strcpy(this->airport_name, a.airport_name);
            n=a.n;
            arr = new Airplane[n];
            for(int i=0; i<n; i++){
                arr[i] = a.arr[i];
            }
        }
        return *this;
    }
    ~AirportService(){
        delete [] arr;
    }
    void print(){
        cout<<airport_name<<endl;
        if(n>0){
            for(int i=0; i<n; i++){
                arr[i].print();
            }
        }else{
            cout<<"-- EMPTY --"<<endl;
        }
    }
    void addAirplane(Airplane  p){
        if(p.get_state()==0){
            p.set_state(1);
            for(int i=0; i<n; i++){
                if(strcmp(arr[i].get_company_name(),p.get_company_name())==0){
                    if(p.get_flight_hours()>arr[i].get_flight_hours()){
                        arr[i]=p;
                    }
                    return;
                }
            }
            Airplane *tmp = new Airplane[n+1];
            for(int i=0; i<n; i++){
                tmp[i] = arr[i];
            }
            tmp[n++] = p;
            delete [] arr;
            arr = tmp;
        }
    }
    Airplane serviceOldestAirplane(){
        Airplane oldest = arr[0];
        int index = 0;
        for(int i=1; i<n; i++){
            if(arr[i].get_flight_hours()>oldest.get_flight_hours()){
                oldest=arr[i];
                index=i;
            }else if(arr[i].get_flight_hours()==oldest.get_flight_hours()){
                if(strcmp(arr[i].get_airport_name(), airport_name)==0){
                    oldest=arr[i];
                    index=i;
                }
            }
        }
        Airplane *tmp = new Airplane[n-1];
        for(int i=0, j=0; i<n; i++){
            if(i!=index){
                tmp[j++] = arr[i];
            }
        }
        n--;
        delete [] arr;
        arr = tmp;
        oldest.set_state(2);
        return oldest;
    }
};

int main() {
    int testCase;
    cin >> testCase;
    char ID[12];
    char company_name[20];
    char company_airport[20];
    int flight_hours;
    int state;
    if (testCase == 1) {
        cout << "TESTING CONSTRUCTOR FOR AIRPLANE" << endl;
        Airplane a;
        cout << "TEST FOR DEFAULT CONSTRUCTOR PASSED" << endl;
        Airplane a1("ZHN-96-TY", "FINKI-Airline", "TMF", 13);
        cout << "TEST FOR CONSTRUCTOR WITH 3 ARGUMENTS PASSED" << endl;
        Airplane a2("ZHN-96-TA", "FINKI1-Airline", "TMF", 13, 0);
        cout << "TEST FOR CONSTRUCTOR WITH 4 ARGUMENTS PASSED" << endl;
    } else if (testCase == 2) {
        cout << "TESTING COPY-CONSTRUCTOR AND OPERATOR = (ASSIGNMENT) FOR AIRPLANE" << endl;
        Airplane p("ZHN-96-TA", "FINKI-Airline", "TMF", 13, 0);
        Airplane p1(p);
        cout << "TEST FOR COPY CONSTRUCTOR PASSED" << endl;
        Airplane p2;
        p2 = p;
        cout << "TEST FOR OPERATOR = (ASSIGNMENT) PASSED" << endl;
    } else if (testCase == 3) {
        cout << "TESTING PRINT() FOR AIRPLANE" << endl;
        cin>>ID>>company_name>>company_airport>>flight_hours>>state;
        Airplane p(ID, company_name, company_airport, flight_hours, state);
        p.print();
    } else if (testCase == 4) {
        cout << "TESTING CONSTRUCTOR FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        cout << "TEST PASSED" << endl;
    } else if (testCase == 5) {
        cout << "TESTING ADD() AND PRINT() FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        int n;
        cin>>n;
        for(int i=0; i<n; i++){
            cin>>ID>>company_name>>company_airport>>flight_hours>>state;
            Airplane p(ID, company_name, company_airport, flight_hours, state);
            as.addAirplane(p);
        }
        as.print();
    } else if (testCase == 6) {
        cout << "TESTING serviceOldestAirplane() AND PRINT() FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        int n;
        cin>>n;
        for(int i=0; i<n; i++){
            cin>>ID>>company_name>>company_airport>>flight_hours>>state;
            Airplane p(ID, company_name, company_airport, flight_hours, state);
            as.addAirplane(p);
        }
        Airplane p = as.serviceOldestAirplane();
        cout<<"Removed plane:"<<endl;
        p.print();
        cout<<"-----------------"<<endl;
        as.print();
    }  else if (testCase == 7) {
        cout << "TESTING COPY CONSTRUCTOR AND OPERATOR = FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        Airplane a1("ZHN-96-TY", "FINKI-Airline", "TMF", 13);
        as.addAirplane(a1);

        AirportService s1 = as; //copy constructor
        AirportService s2;
        s2 = s1; //operator =
        s1.print();
        s2.print();
    }
    return 0;
}
