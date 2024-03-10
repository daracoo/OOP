/*
Да се имплементира класа Car за која се чуваат информации за:

производител (низа од максимум 50 карактери)
модел (низа од максимум 50 карактери)
година на производство (цел број)
сериски број (низа од максимум 7 карактери)
цена (цел број)
За оваа класа да се имплементираат следните методи:
функција displayInfo() за печатење на информации во формат:
Manufacturer : [производител]
Model : [модел]
Year : [година на производство]
Serial number : [сериски број]
Price : [цена со ДДВ]
функција totalPrice() што ја враќа цената со 18% ДДВ.
Потоа да се имплементира класа ElectricCar за која покрај основните информации за автомобилот се чува и:

батерија (цел број, големина на батерија во киловат часови)
За оваа класа да се препокријат следните методи:

функција displayInfo() за печатење на информации во формат:
Model : [модел]
Battery : [батерија]
Serial number : [сериски број]
Price : [цена]
функција totalPrice() која што основната цена ја зголемува за Х(статичка променлива со вредност 5)% за секој еден киловат час. Доколку при пресметување на цената првата буква од серискиот број не е A, B, C да се фрли исклучок InvalidSerialNumberException кој на екран ќе печати "Invalid Serial Number Exception".
For example:

Input	Result
1
Toyota
Camry
2022
12345
25000
        --- Testing Car class ---
        Manufacturer : Toyota
        Model : Camry
        Year : 2022
        Serial number : 12345
        Price : 29500
 */
#include <iostream>
#include<cstring>

using namespace std;

class InvalidSerialNumberException{
    char text[50];
public:
    InvalidSerialNumberException(char *text){
        strcpy(this->text, text);
    }
    void message(){
        cout<<text<<endl;
    }
};

class Car{
protected:
    char prozivoditel[50];
    char model[50];
    int godinaP;
    char seriskiBroj[7];
    int cena;
public:
    Car(char *prozivoditel="", char *model="", int godinaP=0, char *seriskiBroj="", int cena=0){
        strcpy(this->prozivoditel, prozivoditel);
        strcpy(this->model, model);
        strcpy(this->seriskiBroj, seriskiBroj);
        this->godinaP=godinaP;
        this->cena=cena;
    }
    virtual void displayInfo(){
        cout<<"Manufacturer : "<<prozivoditel<<endl;
        cout<<"Model : "<<model<<endl;
        cout<<"Year : "<<godinaP<<endl;
        cout<<"Serial number : "<<seriskiBroj<<endl;
        cout<<"Price : "<<totalPrice()<<endl;
    }
    virtual double totalPrice(){
        return cena*1.18;
    }
};

class ElectricCar: public Car{
    int baterija;
    static double X;
public:
    ElectricCar(char *prozivoditel="", char *model="", int godinaP=0, char *seriskiBroj="", int cena=0, int baterija=0) : Car(prozivoditel, model, godinaP, seriskiBroj, cena){
        this->baterija=baterija;
    }
    void displayInfo(){
        try{
            double total=totalPrice();
            cout<<"Model : "<<model<<endl;
            cout<<"Battery : "<<baterija<<endl;
            cout<<"Serial number : "<<seriskiBroj<<endl;
            cout<<"Price : "<<total<<endl;
        }
        catch (InvalidSerialNumberException &i){
            i.message();
        }

    }
    double totalPrice(){
        if(seriskiBroj[0]!='A' && seriskiBroj[0]!='B' && seriskiBroj[0]!='C'){
            throw InvalidSerialNumberException("Invalid Serial Number Exception");
        }
        return cena*1.18+(cena*X);
    }
};
double ElectricCar::X=0.05;
int main()
{
    int choice;
    cin>>choice;
    if(choice==1)
    {
        cout<<"--- Testing Car class ---"<<endl;
        char manufacturer[50], model[50], serialNumber[7];
        int price, year;
        cin>>manufacturer>>model>>year>>serialNumber>>price;
        try{
            Car car(manufacturer, model, year, serialNumber, price);
            car.displayInfo();
        }
        catch (InvalidSerialNumberException &i){
            i.message();
        }

    }
    else if(choice==2)
    {
        cout<<"--- Testing ElectricCar class ---"<<endl;
        char manufacturer[50], model[50], serialNumber[7];
        int price, year, battery;
        cin>>manufacturer>>model>>year>>serialNumber>>price>>battery;
        try{
            ElectricCar car(manufacturer, model, year, serialNumber, price, battery);
            car.displayInfo();
        }
        catch (InvalidSerialNumberException &e){
            e.message();
        }

    }
    else if(choice==3)
    {
        cout<<"--- Testing Exceptions ---"<<endl;
        char manufacturer[50], model[50], serialNumber[7];
        int price, year, battery;
        cin>>manufacturer>>model>>year>>serialNumber>>price>>battery;

        try{
            ElectricCar car(manufacturer, model, year, serialNumber, price, battery);
            car.displayInfo();
        }
        catch (InvalidSerialNumberException &i){
            i.message();
        }
    }
    return 0;
}
