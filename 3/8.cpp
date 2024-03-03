/*
Да се дефинира класа Employee во која ќе се чуваат информации за:

name(низа од максимум 100 карактери) -име на вработениот

surname(низа од максимум 100 карактери) - презиме

salary(цел број) - колку му е платата

методи кои што класата треба да ги има:

print()

-Принта во формат:
Employee name:

Employee surname:

Employee salary:

Да се дефинира класа TechCompany во која ќе се чуваат информации за:

name(низа од максимум 100 карактери) -име на фирмата

employees(низа од вработени)

numOfEmployees(цел број) - колку вработени има во фирмата

методи кои што класата треба да ги има:

print()

-Принта во формат:
Tech company name:

Number of employees:

 double getAverageOfEmployeeсSalary()

-Враќа средна врендност од платите на секој вработен во таа фирма


Сите променливи внатре во класите треба да бидат приватни. Соодветно во рамките на класите да се дефинираат:

конструктор (без и со параметри)

деструктор

set методи

get методи

copy constructor

Функции надвор од класата:

printCompanyWithHighestAverageSalary(TechCompany companies[], int numCompanies)

-Го враќа TechCompany објектот што има најголема средна вредност за плати на неговите вработени
printCompanyWithHighestStdSalary(TechCompany companies[], int numCompanies)

-Го враќа TechCompany објектот што има најголема стандардна девијација за плати на неговите вработени
VAR=∑for each Employee e[(e.salary−AVG)2]n−1STD=(√VAR)

-Помош: AVG е средната вредност на платите на сите вработен во таа фирма, STD е стандардна девијација, VAR  е помошна променлива. И прво квадрирајте го изразот па потоа додадете го во сумата!
isSameCompany(TechCompany company1, TechCompany company2)

-Враќа boolean вредност: две фирми се исти ако имаат исто име. Треба само да се првери дали им е исто името!
ДА НЕ СЕ МЕНУВА MAIN ФУНКЦИЈАТА.






For example:

Input	                Result
3
CompanyA
5
John Doe 50000
Jane Doe 70000
Bob Smith 60000
Anna Williams 80000
Michael Brown 55000
CompanyB
4
Alice Brown 80000
David Green 70000
Eve White 50000
Frank Black 65000
CompanyC
6
Laura Lee 100000
Benjamin Johnson 65000
Emma Davis 75000
Oliver Wilson 82000
Sophie Martinez 60000
William Clark 72000
                        -->Testing get and set methods for one object and copy constructor
                        copy
                        -->Testing addEmployee function
                        Number of employees in copy: 6
                        -->Testing copy of first employee
                        Employee name: John
                        Employee surname: Doe
                        Employee salary: 50000
                        -->Testing methods
                        Tech company with the highest average salary: CompanyC
                        Tech company with the highest standard deviation for salaries: CompanyC
                        The tech company: CompanyC has the highest standard deviation and highest average salary
 */
#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;

class Employee{
    char name[100];
    char surname[100];
    int salary;
public:
    Employee(){}
    Employee(const char *name, const char *surname, int salary){
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        this->salary=salary;
    }
    Employee(const Employee &e){
        strcpy(this->name, e.name);
        strcpy(this->surname, e.surname);
        this->salary=e.salary;
    }
    ~Employee(){}

    const char *getName()const{
        return name;
    }

    void setName(const char *name) {
        strcpy(this->name, name);
    }

    const char *getSurname()const{
        return surname;
    }

    void setSurname(const char *surname) {
        strcpy(this->surname, surname);
    }
    int getSalary()const{
        return salary;
    }

    void setSalary(int salary) {
        this->salary = salary;
    }

    void printEmployee(){
        cout<<"Employee name: "<<name<<endl;
        cout<<"Employee surname: "<<surname<<endl;
        cout<<"Employee salary: "<<salary<<endl;
    }
};

class TechCompany{
    char name[100];
    Employee employees[20];
    int numOfEmployees;
public:
    TechCompany(){}
    TechCompany(const char *name){
        strcpy(this->name, name);
        numOfEmployees=0;
    }
    TechCompany(const TechCompany &t){
        strcpy(this->name, t.name);
        this->numOfEmployees=t.numOfEmployees;
        for(int i=0;i<numOfEmployees;i++){
            this->employees[i]=t.employees[i];
        }
    }
    ~TechCompany(){}

    const char *getName()const{
        return name;
    }

    void setName(const char *name) {
        strcpy(this->name, name);
    }

    int getNumEmployees()const{
        return numOfEmployees;
    }

    const Employee& getEmployee(int index) const {
        return employees[index];
    }

    void addEmployee(const Employee &employee) {
        if (numOfEmployees < 20) {
            employees[numOfEmployees++] = employee;
        }
    }

    double getAverageOfEmployeesSalary(){
        double max=0;
        for(int i=0;i<numOfEmployees;i++){
            max+=employees[i].getSalary();
        }
        return max/numOfEmployees;
    }

    void print(){
        cout<<"Tech company name: "<<name<<endl;
        cout<<"Number of employees: "<<numOfEmployees<<endl;
    }
};

TechCompany printCompanyWithHighestAverageSalary(TechCompany companies[], int numCompanies){
    int index = -1;
    double highestAverage = -1;

    for (int i = 0; i < numCompanies; i++) {
        double averageSalary = companies[i].getAverageOfEmployeesSalary();
        if (averageSalary > highestAverage) {
            highestAverage = averageSalary;
            index = i;
        }
    }
    return companies[index];
}

TechCompany printCompanyWithHighestStdSalary(TechCompany companies[], int numCompanies) {
    int index = -1;
    double highestStd = -1;

    for (int i = 0; i < numCompanies; i++) {
        int numEmployees = companies[i].getNumEmployees();
        double avg = companies[i].getAverageOfEmployeesSalary();
        double sd = 0.0;

        for (int j = 0; j < numEmployees; j++) {
            double raz = companies[i].getEmployee(j).getSalary() - avg;
            sd += raz * raz;
        }

        double stdSalary = sqrt(sd / (numEmployees-1));

        if (stdSalary > highestStd) {
            highestStd = stdSalary;
            index = i;
        }
    }

    return companies[index];
}

bool isSameCompany(TechCompany company1, TechCompany company2){
    return (strcmp(company1.getName(),company2.getName())==0);
}
//DO NOT CHANGE main()

int main() {
    const int MAX_COMPANIES = 10;
    const int MAX_EMPLOYEES = 20;

    TechCompany companies[MAX_COMPANIES];

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        char name[100];
        std::cin >> name;

        TechCompany company(name);

        int m;
        std::cin >> m;

        for (int j = 0; j < m; j++) {
            char name[100];
            char surname[100];
            int salary;

            std::cin >> name;

            std::cin >> surname;

            std::cin >> salary;

            Employee employee(name, surname, salary);

            company.addEmployee(employee);
        }

        companies[i] = company;
    }

    TechCompany copy = companies[0];

    std::cout<<"-->Testing get and set methods for one object and copy constructor"<<std::endl;
    copy.setName("copy");
    std::cout << copy.getName() << std::endl;


    std::cout<<"-->Testing addEmployee function"<<std::endl;
    Employee newEmployee("John", "Doe", 5000);
    copy.addEmployee(newEmployee);
    std::cout << "Number of employees in copy: " << copy.getNumEmployees() << std::endl;


    std::cout<<"-->Testing copy of first employee"<<std::endl;
    Employee firstEmployee = copy.getEmployee(0);
    firstEmployee.printEmployee();


    std::cout<<"-->Testing methods"<<std::endl;
    TechCompany t = printCompanyWithHighestAverageSalary(companies, n);
    TechCompany t1 = printCompanyWithHighestStdSalary(companies, n);

    std::cout << "Tech company with the highest average salary: " << t.getName() << std::endl;
    std::cout << "Tech company with the highest standard deviation for salaries: " <<t1.getName() << std::endl;

    if (isSameCompany(t, t1)){
        std::cout<<"The tech company: "<<t.getName()<<" has the highest standard deviation and highest average salary"<<std::endl;
    }
    return 0;
}
