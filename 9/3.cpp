/*
Да се креира класа PositiveIntegers во која што ќе се чуваат информации за:

низа од позитивни броеви (>0) (динамички алоцирана низа од цели броеви)
број на елементи во низата
максимален капацитет на низата
За класата да се имплементираат:

потребниот конструктор (погледнете во главната функција како се креира објект од оваа класа)
метод void increaseCapacity(int c) којшто го зголемува максималниот капацитет на низата за бројот с
оператор за додавање на нов број во низата од позитивни броеви +=
број се додава ако и само ако
оператор за множење * за множење на низата со друг цел број
Пример, низата има објекти (1 2 3 4 5) и истата се множи со 2, резултатот ќе биде (1 2 3 4 5)*2 = (2 3 6 8 10)
оператор за делење \ за делење на низата до друг цел број
потребно е секој елемент од низата да биде делив со тој број, како и делителот не смее да биде нула.
оператор [] за пристап до елемент од низата
Потребно е да се дефинираат класи за исклучоци и секој од нив да има метод void message() којшто ќе принта соодветна порака кога исклучокот ќе биде фатен. Можните исклучоци се следните:

ArithmeticException (се фрла ако се проба да се дели со нула)
принта порака Division by zero is not allowed
NumbersNotDivisibleException (се фрла ако се проба да се дели низата со некој број, а барем еден елемент од низата не е делив со тој број)
принта порака Division by number [делителот] is not supported
ArrayFullException (се фрла ако се проба да се додади елемент во низа која и е исполнет максималниот капацитет)
принта порака The array is full. Increase the capacity
IndexOutOfBoundsException (се фрла доколку се проба да се пристапи до елемент од низата со несоодветен индекс)
принта порака Index [индексот] is out of bounds
NumberIsNotPositiveException (се фрла доколку се проба да се внесе во низата број што не е позитивен или е нула)
принта порака Number [бројот] is not positive integer.
For example:

Input	Result
3
3
2
4
6
2
2
8
10
        ===FIRST ATTEMPT TO ADD NUMBERS===
        Size: 3 Capacity: 3 Numbers: 2 4 6
        ===INCREASING CAPACITY===
        Size: 3 Capacity: 5 Numbers: 2 4 6
        ===SECOND ATTEMPT TO ADD NUMBERS===
        Size: 5 Capacity: 5 Numbers: 2 4 6 8 10
        ===TESTING DIVISION===
        Division by zero is not allowed
        Size: 5 Capacity: 5 Numbers: 2 4 6 8 10
        Size: 5 Capacity: 5 Numbers: 1 2 3 4 5
        ===TESTING MULTIPLICATION===
        Size: 5 Capacity: 5 Numbers: 6 12 18 24 30
        ===TESTING [] ===
        PositiveIntegers[-1] = Index -1 is out of bounds
        PositiveIntegers[2] = 6
        PositiveIntegers[3] = 8
        PositiveIntegers[12] = Index 12 is out of bounds

 */
#include<iostream>
#include<cstring>
using namespace std;

class ArithmeticException{
public:
    void message(){
        cout<<"Division by zero is not allowed"<<endl;
    }
};

class NumbersNotDivisibleException{
    int n;
public:
    NumbersNotDivisibleException(int n){
        this->n=n;
    }
    void message(){
        cout<<"Division by "<<n<<" is not supported"<<endl;
    }
};
class ArrayFullException{
public:
    void message(){
        cout<<"The array is full. Increase the capacity"<<endl;
    }
};

class IndexOutOfBoundsException{
    int index;
public:
    IndexOutOfBoundsException(int index){
        this->index=index;
    }
    void message(){
        cout<<"Index "<<index<<" is out of bounds"<<endl;
    }
};

class NumberIsNotPositiveException{
    int number;
public:
    NumberIsNotPositiveException(int number=0){
        this->number=number;
    }
    void message(){
        cout<<"Number "<<number<<" is not positive integer"<<endl;
    }
};

class PositiveIntegers{
    int *pozitivni;
    int brElementi;
    int maxKapacitet;
    void copy(const PositiveIntegers &pi){
        this->maxKapacitet=pi.maxKapacitet;
        this->brElementi=pi.brElementi;
        this->pozitivni=new int[brElementi];
        for(int i=0;i<brElementi;i++){
            pozitivni[i]=pi.pozitivni[i];
        }
    }
public:
    PositiveIntegers(int maxKapacitet=0){
        this->maxKapacitet=maxKapacitet;
        this->brElementi=0;
        pozitivni=new int[brElementi];
    }
    PositiveIntegers(const PositiveIntegers &pi){
        copy(pi);
    }
    PositiveIntegers &operator=(const PositiveIntegers &pi){
        if(this!=&pi){
            delete[]pozitivni;
            copy(pi);
        }
        return *this;
    }
    ~PositiveIntegers(){
        delete[]pozitivni;
    }
    void increaseCapacity(int c){
        maxKapacitet+=c;
    }
    PositiveIntegers &operator+=(int pi){
        if(brElementi==maxKapacitet){
            throw ArrayFullException();
        }
        if(pi<=0){
            throw NumberIsNotPositiveException(pi);
        }
        int *temp = new int[brElementi+1];
        for(int i=0;i<brElementi;i++){
            temp[i]=pozitivni[i];
        }
        temp[brElementi++]=pi;
        delete[]pozitivni;
        pozitivni=temp;
        return *this;
    }
    PositiveIntegers operator *(int number){
        PositiveIntegers pi(*this);
        for(int i=0;i<brElementi;i++){
            pi.pozitivni[i]*=number;
        }
        return pi;
    }
    PositiveIntegers operator/(int number){
        if(number==0){
            throw ArithmeticException();
        }
        for(int i=0;i<brElementi;i++){
            if(pozitivni[i]%number!=0){
                throw NumbersNotDivisibleException(number);
            }
        }
        PositiveIntegers pi(*this);
        for(int i=0;i<brElementi;i++){
            pi.pozitivni[i]/=number;
        }
        return pi;
    }
    int &operator[](int index)
    {
        if(index<0 || index>brElementi)
        {
            throw(IndexOutOfBoundsException(index));
        }
        return pozitivni[index];
    }
    void print(){
        cout<<"Size: "<<brElementi<<" Capacity: "<<maxKapacitet<<" Numbers: ";
        for(int i=0;i<brElementi;i++){
            cout<<pozitivni[i]<<" ";
        }
        cout<<endl;
    }
};

int main() {

    int n,capacity;
    cin >> n >> capacity;
    PositiveIntegers pi (capacity);
    for (int i=0;i<n;i++){
        int number;
        cin>>number;
        try{
            pi+=number;
        }
        catch (ArrayFullException &ae){
            ae.message();
        }
        catch (NumberIsNotPositiveException &np){
            np.message();
        }

    }
    cout<<"===FIRST ATTEMPT TO ADD NUMBERS==="<<endl;
    pi.print();
    int incCapacity;
    cin>>incCapacity;
    pi.increaseCapacity(incCapacity);
    cout<<"===INCREASING CAPACITY==="<<endl;
    pi.print();

    int n1;
    cin>>n1;
    for (int i=0;i<n1;i++){
        int number;
        cin>>number;
        try{
            pi+=number;
        }
        catch (ArrayFullException &ae){
            ae.message();
        }
        catch (NumberIsNotPositiveException &np){
            np.message();
        }
    }
    cout<<"===SECOND ATTEMPT TO ADD NUMBERS==="<<endl;

    pi.print();
    PositiveIntegers pi1;

    cout<<"===TESTING DIVISION==="<<endl;

    try{
        pi1 = pi/0;
        pi1.print();
    }
    catch (NumbersNotDivisibleException &nn){
        nn.message();
    }
    catch (ArithmeticException &a){
        a.message();
    }

    try{
        pi1 = pi/1;
        pi1.print();
    }
    catch (NumbersNotDivisibleException &nn){
        nn.message();
    }
    catch (ArithmeticException &a){
        a.message();
    }

    try{
        pi1 = pi/2;
        pi1.print();
    }
    catch (NumbersNotDivisibleException &nn){
        nn.message();
    }
    catch (ArithmeticException &a){
        a.message();
    }

    cout<<"===TESTING MULTIPLICATION==="<<endl;
    pi1 = pi*3;
    pi1.print();



    cout<<"===TESTING [] ==="<<endl;
    try{
        cout<<"PositiveIntegers[-1] = "<<pi[-1]<<endl;
    }
    catch (IndexOutOfBoundsException &i){
        i.message();
    }
    try{
        cout<<"PositiveIntegers[2] = "<<pi[2]<<endl;
    }
    catch (IndexOutOfBoundsException &i){
        i.message();
    }
    try{
        cout<<"PositiveIntegers[3] = "<<pi[3]<<endl;
    }
    catch (IndexOutOfBoundsException &i){
        i.message();
    }
    try{
        cout<<"PositiveIntegers[12] = "<<pi[12]<<endl;
    }
    catch (IndexOutOfBoundsException &i){
        i.message();
    }

    return 0;
}
