/*
Да се имплементира класа List во којашто ќе се чуваат информации за:

броеви што се дел од листата (динамички алоцирана низа од цели броеви)
бројот на броеви што се дел од листата
За класата да се дефинираат следните методи:

конструктор (со аргументи), copy-конструктор, деструктор, оператор =
void pecati()метод што ќе ги печати информациите за листата во форматот: [број на елементи во листата]: x1 x2 .. xn sum: [сума] average: [просек]
int sum() метод што ја враќа сумата на елементите во листата
double average() метод што ќе го враќа просекот на броевите во листата
Дополнително, креирајте класата ListContainer, во која што ќе се чуваат информации за:

низа од листи (динамички алоцирана низа од објекти од класата List)
број на елементи во низата од листи (цел број)
број на обиди за додавање на листа во контејнерот (цел број првично поставен на нула)
За класата потребно е да ги дефинирате следните методи:

конструктор (default), copy-конструктор, деструктор, оператор =
void pecati() метод што ќе ги печати информациите за контејнерот во форматот: List number: [реден број на листата] List info: [испечатени информации за листата со методот List::pecati()] \n sum: [сума] average: [просек]
доколку контејнерот е празен се печати само порака The list is empty.
void addNewList(List l) метод со којшто се додава листа во контејнерот
Напомена: една листа се додава во контејнерот ако и само ако има различна сума од сите листи што се веќе додадени во контејнерот
int sum() метод што ја враќа сумата на сите елементи во сите листи
double average() метод што го враќа просекот на сите елементи во сите листи во контејнерот
For example:

Input	Result
2
1
1
2
0 1
0
        List number: 1 List info: 1: 1 sum: 1 average: 1
        Sum: 1 Average: 1
        Successful attempts: 1 Failed attempts: 1
 */
#include <iostream>
#include <string.h>
using namespace std;

class List{
    int *broevi;
    int brBroevi;
public:
    List(int *broevi, int brBroevi){
        this->brBroevi=brBroevi;
        this->broevi=new int[brBroevi];
        for(int i=0;i<brBroevi;i++){
            this->broevi[i]=broevi[i];
        }
    }
    List(){
        this->brBroevi=0;
        this->broevi=new int[0];
    }
    List(const List &l){
        this->brBroevi=l.brBroevi;
        this->broevi=new int[brBroevi];
        for(int i=0;i<brBroevi;i++){
            this->broevi[i]=l.broevi[i];
        }
    }
    List &operator=(const List &l){
        if(this!=&l){
            this->brBroevi=l.brBroevi;
            delete[]broevi;
            this->broevi=new int[l.brBroevi];
            for(int i=0;i<brBroevi;i++){
                this->broevi[i]=l.broevi[i];
            }
        }
        return *this;
    }
    ~List(){
        delete[]broevi;
    }

    void pecati(){
        cout<<brBroevi<<": ";
        for(int i=0;i<brBroevi;i++){
            cout<<broevi[i]<<" ";
        }
        cout<<"sum: "<<suma()<<" average: "<<average()<<endl;
    }

    int suma(){
        int suma=0;
        for(int i=0;i<brBroevi;i++){
            suma+=broevi[i];
        }
        return suma;
    }

    double average(){
        double average=0.0;
        for(int i=0;i<brBroevi;i++){
            average+=broevi[i];
        }
        return average/brBroevi;
    }

    int getSuma(){
        return suma();
    }

    double getAverage(){
        return average();
    }

    int getBr(){
        return brBroevi;
    }

};

class ListContainer{
    List *listi;
    int brElementi;
    int brObidi;
public:
    ListContainer(){
        this->brElementi=0;
        this->brObidi=0;
        this->listi=new List[0];
    }
    ListContainer(const ListContainer &lc){
        this->brElementi=lc.brElementi;
        this->listi=new List[lc.brElementi];
        for(int i=0;i<brElementi;i++){
            this->listi[i]=lc.listi[i];
        }
        this->brObidi=lc.brObidi;
    }
    ListContainer &operator=(ListContainer &lc){
        if(this!=&lc){
            this->brElementi=lc.brElementi;
            delete[]listi;
            this->listi=new List[lc.brElementi];
            for(int i=0;i<brElementi;i++){
                this->listi[i]=lc.listi[i];
            }
            this->brObidi=lc.brObidi;
        }
        return *this;
    }
    ~ListContainer(){
        delete[]listi;
    }

    void print(){
        if(brElementi==0){
            cout<<"The list is empty"<<endl;
            return;
        }
        for(int i=0;i<brElementi;i++){
            cout<<"List number: "<<i+1<<" List info: ";listi[i].pecati();
        }
        cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
        cout<<"Successful attempts: "<<brElementi<<" Failed attempts: "<<brObidi-brElementi<<endl;
    }

    int sum(){
        int suma=0;
        for(int i=0;i<brElementi;i++){
            suma+=listi[i].getSuma();
        }
        return suma;
    }

    double average(){
        double average=0.0;
        int brE=0;
        for(int i=0;i<brElementi;i++){
            average+=listi[i].getSuma();
            brE+=listi[i].getBr();
        }
        return average/brE;
    }

    void addNewList(List l){
        brObidi++;
        for(int i=0;i<brElementi;i++){
            if(listi[i].getSuma()==l.getSuma()){
                return;
            }
        }
        List *tmp=new List[brElementi+1];
        for(int i=0;i<brElementi;i++){
            tmp[i]=listi[i];
        }
        tmp[brElementi++]=l;
        delete[]listi;
        listi=tmp;
    }

};
int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}