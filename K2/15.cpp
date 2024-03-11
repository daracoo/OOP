/*
Дадена е дел од дефиниција на класата StudentKurs. За секој студент кој слуша некој курс се чуваат информации за неговото име (низа од знаци), оценка од писмен дел (цел број) и дали студентот сака да биде испрашуван и усно (булова променлива).

Оцената за писмениот дел е вредност од 1 до МАX. MAX има почетна вредност 10 која е иста е за сите и може да се промени со соодветна функција setMAX(). (5 поени)

Кај оние студенти кои сакаат да бидат испрашувани усно и добиваат и описна оценка. Имплементирај соодветна класа StudentKursUsno во која се чуваат дополнителни информации за описна оценка на усното испрашување (динамичко алоцирана низа од знаци). Описни оценки може да бидат: odlicen, dobro, losho.... Ако описната оценка е odlicen тогаш оцената ќе биде најмногу за оценки 2 повисока од оценката од писмениот дел, ако е dobro оценката ќе биде најмногу за 1 повисока, а ако е losho за 1 пониска. Ако студентот добие некоја друга описна оценка, неговата оценка ќе остане иста со оценката од писмениот дел.

Во класите StudentKurs и StudentKursUsno треба да се имплементираат потребните конструктори, функции за поставување и преземање и деструктор. (5 поени)

За сите објекти од класите треба да се обезбедат следните функции:

преоптоварен оператор << во кој се печатат информации за студентот на курсот во формат: Ime --- ocenka (5 поени)
оcenka() – ја враќа оценката на студентот на курсот (5 поени)
Во класата StudentKursUsno дефинирај ја функцијата:

преоптоварен оператор += за поставување на описна оценка на студентот(5 поени)
Ако се направи обид да се внесе описна оценка во која покрај букви има и други знаци треба да се фрли исклучок (објект од класата BadInputException). Фатете го исклучокот во главната функција каде што е потребно. Откако ќе го фатите отпечатете соодветна порака за грешка (Greshna opisna ocenka) и справете се со исклучокот така што тие знаци ќе отстранат од стрингот со описната оценка (ако описната оценка била dо1ba0r ќе се промени во dоbar). (10 поени)

Дадена е дел од дефиницијата на класата KursFakultet во која се чуваат информаци за името на курсот (низа од 30 знаци) и за студентите запишани на курсот (низа од 20 покажувачи кон класата StudentKurs) како и бројот на студенти запишани на курсот.

Еден студент кој запишал некој курс ќе го положи курсот ако има барем MINOCENKA. Вредноста MINOCENKA е членка на класата StudentKurs и има фиксна вредност 6 која не може да се промени. (5 поени)

Во класата KursFakultet имплементирај ги функциите:

функција pecatiStudenti() во која се печатат сите студенти кои го положиле курсот, секој во посебен ред. Претходно во првиот ред се печати: Kursot XXXXX go polozile: (5 поени).

функција postaviOpisnaOcenka(char * ime, char* opisnaOcenka) во која на студентот на курсот со даденото име му се поствува описна оценка. Ако тоа не е можно функцијата не прави ништо (15 поени).

Комплетна функционалност (5 поени)
 */
#include<iostream>
#include<string.h>
using namespace std;

class BadInputException {
public:
    static void message() {
        cout << "Greshna opisna ocenka\n";
    }
};

class StudentKurs{
protected:
    char ime[30];
    int ocenka;
    bool daliUsno;
    static int MAX;

private:
    void copy_kurs(const StudentKurs &other) {
        strcpy(this->ime, other.ime);
        this->ocenka = other.ocenka;
        this->daliUsno = other.daliUsno;
    }

public:
    StudentKurs(char* ime, int finalenIspit){
        strcpy(this->ime, ime);
        this->ocenka = finalenIspit;
        this->daliUsno = false;
    }

    StudentKurs(const StudentKurs& other) {
        copy_kurs(other);
    }

    StudentKurs& operator=(const StudentKurs& other) {
        if(this == &other) {
            return *this;
        }
        copy_kurs(other);
        return *this;
    }

    friend ostream& operator<<(ostream& out, StudentKurs& kurs) {
        out << kurs.ime << " --- " << kurs.getOcenka() << "\n";
        return out;
    }

    static void setMAX(int val) {
        MAX = val;
    }

    char* getIme() {
        return ime;
    }

    virtual int getOcenka() {
        return ocenka;
    }

    bool getDaliUsno() {
        return daliUsno;
    }

    ~StudentKurs() { }
};

class StudentKursUsno : public StudentKurs {
    char* opisna_ocenka;

public:
    StudentKursUsno(char* ime, int ocenka) : StudentKurs(ime, ocenka) {
        this->opisna_ocenka = new char[10];
        strcpy(this->opisna_ocenka, "opisna");
        this->daliUsno = true;
    }

    StudentKursUsno(const StudentKursUsno& other) : StudentKurs(other) {
        this->opisna_ocenka = new char[10];
        strcpy(this->opisna_ocenka, other.opisna_ocenka);
        this->daliUsno = true;
    }

    StudentKurs& operator+=(char* oc) {
        for(int i = 0; i < strlen(oc); i++) {
            if(!isalpha(oc[i])) {
                throw BadInputException();
            }
        }
        delete [] opisna_ocenka;
        this->opisna_ocenka = new char[10];
        strcpy(this->opisna_ocenka, oc);
        return *this;
    }

    int getOcenka() {
        int kursOcena = StudentKurs::getOcenka(), add = 0;

        if(!strcmp(opisna_ocenka, "odlicen")) {
            add = 2;
        } else if(!strcmp(opisna_ocenka, "dobro")) {
            add = 1;
        } else if(!strcmp(opisna_ocenka, "losho")) {
            add = -1;
        } else {
            return kursOcena;
        }

        return kursOcena + add < MAX ? kursOcena + add : MAX;
    }

    ~StudentKursUsno() {
        delete [] opisna_ocenka;
    }
};

class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;
    const static int MINOCENKA = 6;

public:
    KursFakultet(char* naziv, StudentKurs** studenti, int broj) {
        strcpy(this->naziv, naziv);
        for(int i = 0; i < broj; i++){
            if(studenti[i]->getDaliUsno()) {
                this->studenti[i] = new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            } else {
                this->studenti[i] = new StudentKurs(*studenti[i]);
            }
        }
        this->broj = broj;
    }

    void pecatiStudenti() {
        cout << "Kursot " << naziv << " go polozile:\n";
        for(int i = 0; i < broj; i++) {
            if(studenti[i]->getOcenka() >= MINOCENKA) {
                cout << *studenti[i];
            }
        }
    }

    void postaviOpisnaOcenka(char *ime, char *opisnaOcenka) {
        for(int i = 0; i < broj; i++) {
            if(studenti[i]->getDaliUsno() && !strcmp(ime, studenti[i]->getIme())) {
                *dynamic_cast<StudentKursUsno*>(studenti[i]) += opisnaOcenka;
            }
        }
    }

    ~KursFakultet(){
        for(int i = 0; i < broj; i++) {
            delete studenti[i];
        }
    }
};

int StudentKurs::MAX = 10;

int main(){

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0;i<n;i++){
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0;i<m;i++){
        cin>>ime>>opisna;

        try { programiranje.postaviOpisnaOcenka(ime,opisna); }
        catch(BadInputException) {
            BadInputException::message();
            char nova_opisna[10];
            int ct = 0;

            for(int j = 0; j < strlen(opisna); j++) {
                if(opisna[j] >= '0' && opisna[j] <= '9') continue;
                nova_opisna[ct++] = opisna[j];
            }

            nova_opisna[ct] = '\0';

            programiranje.postaviOpisnaOcenka(ime, nova_opisna);
        }

    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}