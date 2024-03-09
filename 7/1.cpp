/*
Да се дефинира апстрактна класа Employee којашто ќе содржи име на вработениот, години и работно искуство во години (integer). Да се дефинираат чисти виртуелни функции plata() и bonus() (double).

Од класата Employee да се изведе класа SalaryEmployee која покрај основните информации содржи и информација за основната плата. Бонусот на овие работници се пресметува како процент од основната плата, а процентот е бројот на години со работно искуство. На пример ако работеле 10 години, бонусот е 10 проценти од основната плата. Вкупната плата се пресметува како основната плата плус бонусот.

Од класата Employee исто така да се изведе класа HourlyEmployee која покрај основните информации содржи информација и за вкупниот број на часови кои ги одработил работникот и платата по час. Вкупната плата се пресметува како бројот на часови помножен со платата по час плус бонусот, додека бонусот се пресметува на следниот начин: За секој час над 320-тиот се добива 50 проценти од платата по час.

Од класата Employee на крај се изведува класата Freelancer која покрај основните информации содржи и број на проекти на кои работел вработениет и низа со суми кои ги добил за тие проекти (double). По направени 5 проекти, за секој нареден вработените добиваат бонус од 1000 денари. Вкупната плата на овој тип на вработени изнесува вкупната сума добиена од сите проекти плус бонусот.

Да се преоптовари операторот == кој ќе прима два објекти од класата Employee и ќе ги споредува според тоа дали имаат ист број на години.

Да се дефинира класа Company која ќе содржи информации за името на компанијата, бројот на вработени, и динамична низа од покажувачи од класата Employee или Employee **. За потребите на оваа класа треба да се дефинира конструктор кој прима само еден аргумент - името на компанијата, да се преоптовари операторот += и да се дефинираат следните методи:

double vkupnaPlata() - метод којшто ја враќа вкупната плата на сите вработени во компанијата
double filtriranaPlata(Employee * emp) - метод којшто ја враќа платата само на работниците кои се еднакви со дадениот вработен (според оператор ==)
void pecatiRabotnici() - метод којшто печати по колку вработени има од секој тип на работници во компанијата, а форматот на печатење можете да го видите од тест примерите
Hint: За потребите на последниот метод можете да искористите статички членови и статички функции во секоја од класата, dynamic_cast, виртуелна функција која ќе ја преоптоварите во секоја од класите или нешто друго по ваша желба.

For example:

Input	                    Result
Advokatsko_drustvo_Bambus
3
1 Lidija_Andova 31 5 16000
2 Martin_Kovacev 31 7 336 100
2 Tea_Vinarova 29 4 330 60
                            Vo kompanijata Advokatsko_drustvo_Bambus rabotat:
                            Salary employees: 1
                            Hourly employees: 2
                            Freelancers: 0
                            Vkupnata plata e: 71300
                            Filtriranata plata e: 51200
 */
#include<iostream>
#include<cstring>
using namespace std;

class Employee{
protected:
    char ime[50];
    int godini;
    int rabotnoIskustvo;
public:
    Employee(char *ime="", int godini=0, int rabotnoIskustvo=0){
        strcpy(this->ime, ime);
        this->godini=godini;
        this->rabotnoIskustvo=rabotnoIskustvo;
    }
    virtual double plata()=0;
    virtual double bonus()=0;

    bool operator==(Employee &e){
        return (godini==e.godini && bonus()==e.bonus());
    }

};

class SalaryEmployee: public Employee{
    int osnovnaPlata;
public:
    SalaryEmployee(char *ime="", int godini=0, int rabotnoIskustvo=0, int osnovnaPlata=0) : Employee(ime, godini, rabotnoIskustvo){
        this->osnovnaPlata=osnovnaPlata;
    }

    double bonus(){
        return (rabotnoIskustvo*osnovnaPlata)/100.0;
    }

    double plata(){
        return osnovnaPlata+bonus();
    }
};

class HourlyEmployee: public Employee{
    int brCasovi;
    int plataCas;
public:
    HourlyEmployee(char *ime="", int godini=0, int rabotnoIskustvo=0, int brCasovi=0, int plataCas=0) : Employee(ime, godini, rabotnoIskustvo){
        this->brCasovi=brCasovi;
        this->plataCas=plataCas;
    }

    double bonus(){
        if(brCasovi>320){
            return (brCasovi-320)*0.5*plataCas;
        }
        return 0;
    }

    double plata(){
        return (brCasovi * plataCas) + bonus();
    }
};

class Freelancer: public Employee{
    int brProekti;
    double sumi[10];
public:
    Freelancer(char *ime="", int godini=0, int rabotnoIskustvo=0, int brProekti=0, double *sumi=0) : Employee(ime, godini, rabotnoIskustvo){
        this->brProekti=brProekti;
        for(int i=0;i<brProekti;i++){
            this->sumi[i]=sumi[i];
        }
    }

    double bonus(){
        if(brProekti>5){
            return(brProekti-5)*1000;
        }
        return 0;
    }

    double plata(){
        double suma=0.0;
        for(int i=0;i<brProekti;i++){
            suma+=sumi[i];
        }
        return suma+bonus();
    }

};

class Company{
    char ime[50];
    int brVraboteni;
    Employee **vraboteni;


public:
    Company(char *ime=""){
        strcpy(this->ime, ime);
        this->brVraboteni=0;
        this->vraboteni=new Employee *[0];
    }
    ~Company(){
        delete[]vraboteni;
    }
    Company &operator+=(Employee *e){
        Employee **tmp= new Employee * [brVraboteni+1];
        for(int i=0;i<brVraboteni;i++){
            tmp[i]=vraboteni[i];
        }
        tmp[brVraboteni++]=e;
        delete[]vraboteni;
        vraboteni=tmp;
        return *this;
    }

    double vkupnaPlata(){
        double suma=0.0;
        for(int i=0;i<brVraboteni;i++){
            suma+=vraboteni[i]->plata();
        }
        return suma;
    }

    double filtriranaPlata(Employee *emp){
        double suma=0.0;
        for(int i=0;i<brVraboteni;i++){
            if(*vraboteni[i]==*emp){
                suma+= vraboteni[i]->plata();
            }
        }
        return suma;
    }

    void pecatiRabotnici(){
        int brSalary=0, brHourly=0, brFree=0;
        cout<<"Vo kompanijata "<<ime<<" rabotat:"<<endl;
        for(int i=0;i<brVraboteni;i++){
            SalaryEmployee *se=dynamic_cast<SalaryEmployee*>(vraboteni[i]);
            if(se!=0){
                brSalary++;
                continue;
            }
            HourlyEmployee *he=dynamic_cast<HourlyEmployee*>(vraboteni[i]);
            if(he!=0){
                brHourly++;
                continue;
            }
            Freelancer *fe=dynamic_cast<Freelancer*>(vraboteni[i]);
            if(fe!=0){
                brFree++;
                continue;
            }
        }
        cout<<"Salary employees: "<<brSalary<<endl;
        cout<<"Hourly employees: "<<brHourly<<endl;
        cout<<"Freelancers: "<<brFree<<endl;
    }
};


int main() {

    char name[50];
    cin >> name;
    Company c(name);

    int n;
    cin >> n;

    char employeeName[50];
    int age;
    int experience;
    int type;

    for (int i=0; i <n; ++i) {
        cin >> type;
        cin >> employeeName >> age >> experience;

        if (type == 1) {
            int basicSalary;
            cin >> basicSalary;
            c += new SalaryEmployee(employeeName, age, experience, basicSalary);
        }

        else if (type == 2) {
            int hoursWorked;
            int hourlyPay;
            cin >> hoursWorked >> hourlyPay;
            c += new HourlyEmployee(employeeName, age, experience, hoursWorked, hourlyPay);
        }

        else {
            int numProjects;
            cin >> numProjects;
            double projects[10];
            for (int i=0; i < numProjects; ++i) {
                cin >> projects[i];
            }
            c += new Freelancer(employeeName, age, experience, numProjects, projects);
        }
    }

    c.pecatiRabotnici();
    cout << "Vkupnata plata e: " << c.vkupnaPlata() << endl;
    Employee * emp = new HourlyEmployee("Petre_Petrov",31,6,340,80);
    cout << "Filtriranata plata e: " << c.filtriranaPlata(emp);

    delete emp;
}