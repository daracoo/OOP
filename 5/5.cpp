/*
Како успешен студент на ФИНКИ вие сте повикани да работите на подобрување на IKnow системот. Како дел од системот треба да се додаде нов дел кој ќе биде одговорен за обработување на дисциплински мерки, па како дел од тимот за развивање на софтверот ќе треба да ја имплементирате класата DisciplinaryAction која ќе ги чува следните информации:

Името на студентот (динамички алоцирана низа од карактери)
Индексот на студентот (int)
Причината за дисциплинската мерка (динамички алоцирана низа од карактери)
бројот на сесии во кои студентот нема право да полага (int)

Класата треба да ги има следните методи и конструктори:

Default конструктор
Copy конструктор
Конструктор со аргументи
Деструктор
Set и Get методи за индексот
Оператор =
оператор << за печатење на информации за студентот
оператор ++ за зголемување на бројот на сесии во кои студентот е казнет (во префикс нотација)
оператор >= за споредба на дисциплински постапки според бројот на сесии во кои студентот е казнет

Операторот << треба да печати според следниот формат:
Student: [Name]
Student's index: [Index]
Reason: [Reason]
Sessions: [Sessions]


При што вредностите во [] треба да се заменат со вредностите во класата!

!!! ДА НЕ СЕ ПРАВАТ ПРОМЕНИ ВО MAIN() ФУНКЦИЈАТА !!!

For example:

Input	                Result
1
Stefan 151020 Prepis 2
                        -- Testing operator = & operator <<  --
                        Student: Stefan
                        Student's index: 151020
                        Reason: Prepis
                        Sessions: 2

                        -- Testing copy constructor & set index --
                        -------------
                        Source:
                        -------------
                        Student: Stefan
                        Student's index: 151020
                        Reason: Prepis
                        Sessions: 2

                        -------------
                        Copied and edited:
                        -------------
                        Student: Stefan
                        Student's index: 112233
                        Reason: Prepis
                        Sessions: 2

                        -- Testing if array was inputted correctly --
                        Student: Stefan
                        Student's index: 151020
                        Reason: Prepis
                        Sessions: 2

                        Testing operator ++ and <<
                        Student: Stefan
                        Student's index: 151020
                        Reason: Prepis
                        Sessions: 3

                        Testing operator >=
 */
#include <iostream>
#include <cstring>
using namespace std;

class DisciplinaryAction{
    char *ime;
    int index;
    char *pricina;
    int brSesii;

    void copy(const DisciplinaryAction &da){
        this->ime=new char[strlen(da.ime)+1];
        strcpy(this->ime, da.ime);
        this->index=da.index;
        this->pricina=new char[strlen(da.pricina)+1];
        strcpy(this->pricina, da.pricina);
        this->brSesii=da.brSesii;
    }
public:
    DisciplinaryAction(char *ime="", int index=1, char *pricina="", int brSesii=0){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        this->index=index;
        this->pricina=new char[strlen(pricina)+1];
        strcpy(this->pricina, pricina);
        this->brSesii=brSesii;
    }
    DisciplinaryAction(const DisciplinaryAction &da){
        copy(da);
    }
    ~DisciplinaryAction(){
        delete[]ime;
        delete[]pricina;
    }
    DisciplinaryAction &operator=(const DisciplinaryAction &da){
        if(this!=&da){
            delete[]ime;
            delete[]pricina;
            copy(da);
        }
        return *this;
    }
    void setIndex(int index){
        this->index=index;
    }
    int getIndex()const{
        return index;
    }
    DisciplinaryAction &operator++(){
        ++brSesii;
        return *this;
    }
    int getSesii()const{
        return brSesii;
    }
    bool operator>=(DisciplinaryAction &da) const{
        return this->getSesii()>=da.brSesii;
    }
    friend ostream &operator<<(ostream &out, DisciplinaryAction &da){
        out<<"Student: "<<da.ime<<endl;
        out<<"Student's index: "<<da.index<<endl;
        out<<"Reason: "<<da.pricina<<endl;
        out<<"Sessions: "<<da.brSesii<<endl;
        return out;
    }
};

/// Do NOT edit the main() function

int main() {
    int n;
    cin >> n;

    /// Testing Default constructor and equal operator
    /// Array input

    DisciplinaryAction arr[n];

    for (int i = 0; i < n; i++) {
        char name[100];
        char reason[100];
        int index;
        int sessions;

        cin >> name >> index >> reason >> sessions;

        arr[i] = DisciplinaryAction(name, index, reason, sessions);
    }

    cout << "-- Testing operator = & operator <<  --\n";
    cout << arr[0];

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    cout << arr[0];

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    cout << merka;

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for (int i = 0; i < n; i++)
        cout << arr[i];


    cout << "\nTesting operator ++ and <<" << endl;
    for (int i = 0; i < n; i++)
        cout << (++arr[i]);


    cout << "\nTesting operator >=" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << i << " " << ((arr[i] >= arr[j]) ? ">= " : "< ") << j << endl;
            }
        }
    }

    return 0;
}