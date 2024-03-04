/*
Како успешен студент на ФИНКИ вие сте повикани да работите на подобрување на IKnow системот. Како дел од системот треба да се додаде нов дел кој ќе биде одговорен за обработување на дисциплински мерки, па како дел од тимот за развивање на софтверот ќе треба да ја имплементирате класата DisciplinaryAction која ќе ги чува следните информации:

Името на студентот (динамички алоцирана низа од карактери)
Индексот на студентот (int)
Причината за дисциплинската мерка (динамички алоцирана низа од карактери)

Класата треба да ги има следните методи и конструктори:

Default конструктор
Copy конструктор
Конструктор со аргументи
Деструктор
Set и Get методи за индексот
void print() метод
Оператор =

Print() методот треба да печати според следниот формат:
Student: [Name]
Student's index: [Index]
Reason: [Reason]

При што вредностите во [] треба да се заменат со вредностите во класата!

!!! ДА НЕ СЕ ПРАВАТ ПРОМЕНИ ВО MAIN() ФУНКЦИЈАТА !!!

For example:

Input	                Result
1
Stefan 151020 Prepis
                        -- Testing operator = & print() --
                        Student: Stefan
                        Student's index: 151020
                        Reason: Prepis

                        -- Testing copy constructor & set index --
                        -------------
                        Source:
                        -------------
                        Student: Stefan
                        Student's index: 151020
                        Reason: Prepis

                        -------------
                        Copied and edited:
                        -------------
                        Student: Stefan
                        Student's index: 112233
                        Reason: Prepis

                        -- Testing if array was inputted correctly --
                        Student: Stefan
                        Student's index: 151020
                        Reason: Prepis
 */
#include <iostream>
#include <cstring>

using namespace std;

class DisciplinaryAction{
    char *ime;
    int index;
    char *pricina;
public:
    DisciplinaryAction(char *ime="", int index=0, char *pricina=""){
        this->index=index;
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        this->pricina=new char[strlen(pricina)+1];
        strcpy(this->pricina, pricina);
    }
    DisciplinaryAction(const DisciplinaryAction &da){
        this->index=da.index;
        this->ime=new char[strlen(da.ime)+1];
        strcpy(this->ime, da.ime);
        this->pricina=new char[strlen(da.pricina)+1];
        strcpy(this->pricina, da.pricina);
    }
    ~DisciplinaryAction(){
        delete[]ime;
        delete[]pricina;
    }
    void setIndex(int index){
        this->index=index;
    }
    int getIndex(){
        return index;
    }
    DisciplinaryAction &operator=(const DisciplinaryAction &da){
        if(this!=&da){
            this->index=da.index;
            delete[]ime;
            delete[]pricina;
            this->ime=new char[strlen(da.ime)+1];
            this->pricina=new char[strlen(da.pricina)+1];
            strcpy(this->ime, da.ime);
            strcpy(this->pricina, da.pricina);
        }
        return *this;
    }
    void print(){
        cout<<"Student: "<<ime<<endl;
        cout<<"Student's index: "<<index<<endl;
        cout<<"Reason: "<<pricina<<endl;
    }
};


/// Do NOT edit the main() function

int main() {
    int n;
    cin >> n;

    /// Testing Default constructor and equal operator
    /// Array input

    DisciplinaryAction arr[n];

    for(int i = 0; i < n; i++) {
        char name[100];
        char reason[100];
        int index;

        cin >> name >> index >> reason;

        arr[i] = DisciplinaryAction(name, index, reason);
    }

    cout << "-- Testing operator = & print() --\n";
    arr[0].print();

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    arr[0].print();

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    merka.print();

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for(int i = 0; i < n; i++)
        arr[i].print();

    return 0;
}