/*
Да се дефинира класа Student за која се чува:
name(низа од карактери, динамички алоцирана) - неговото име
age (цел број) - колку години има
major (низа од карактери, динамички алоцирана) - што студира
За класата да се дефинира default конструктор, конструктор со аргументи и copy конструктор.

Потоа да се дефинира класа Classroom за која се чува:
students (динамички алоцирана низа од Студенти)
numStudents(int)
capacity(int)
За класата да се дефинира  default конструктор и конструктор со аргументи.

Треба за класата Classroom да се дефинираат следните методи:
add - да се додаде нов студент
remove - да се отстрани некој студент со дадено име name
findMedianAge - наоѓа која е медијаната за години на стидентите во дадениот Classroom.
Пример: 2 4 5 6 7 8 10
Медијана: 6

Пример: 2 4 5 7 8 10 12 20
Медијана: (7 + 8)/2

Мора да е растечки редослед!

По потреба може да се креираат get и set методи.

Сите студенти имаат уникатно име.
Да не се менува main функцијата.
For example:

Input	            Result
2
2
Alice 19 Biology
Bob 20 Physics
3
Charlie 22 Chemistry
Dave 21 Math
Eve 20 English
1
3
Bob
Charlie
Dave
                    Classroom 0
                    Alice (19, Biology)
                    Bob (20, Physics)

                    Classroom 1
                    Charlie (22, Chemistry)
                    Dave (21, Math)
                    Eve (20, English)

                    The median age in classroom 1 is: 21
                    After removing the elements:
                    Classroom 0
                    Alice (19, Biology)

                    Classroom 1
                    Eve (20, English)
 */
#include <iostream>
#include <string.h>
using namespace std;

class Student{
    char *name;
    int age;
    char *major;
public:
    Student(char *name="", int age=0, char *major=""){
        this->age=age;
        this->name=new char[strlen(name)+1];
        strcpy(this->name, name);
        this->major=new char[strlen(major)+1];
        strcpy(this->major, major);
    }
    Student(const Student &s){
        this->age=s.age;
        this->name=new char[strlen(s.name)+1];
        strcpy(this->name, s.name);
        this->major=new char[strlen(s.major)+1];
        strcpy(this->major, s.major);
    }
    Student &operator=(const Student &s){
        if(this!=&s){
            this->age=s.age;
            delete[]name;
            delete[]major;
            this->name=new char[strlen(s.name)+1];
            strcpy(this->name, s.name);
            this->major=new char[strlen(s.major)+1];
            strcpy(this->major, s.major);
        }
        return *this;
    }
    ~Student(){
        delete[]name;
        delete[]major;
    }
    char *getName(){
        return name;
    }
    int getAge(){
        return age;
    }
    char *getMajor(){
        return major;
    }

    bool daliIsti(Student s){
        return strcmp(name, s.name)==0;
    }

};

class Classroom{
    Student *students;
    int numStudents;
    int capacity;
public:
    Classroom(Student *students=0, int numStudents=0, int capacity=0){
        this->numStudents=numStudents;
        this->capacity=capacity;
        this->students=new Student[numStudents];
        for(int i=0;i<numStudents;i++){
            this->students[i]=students[i];
        }
    }
    Classroom(const Classroom &c){
        this->numStudents=c.numStudents;
        this->capacity=c.capacity;
        this->students=new Student[c.numStudents];
        for(int i=0;i<numStudents;i++){
            this->students[i]=c.students[i];
        }
    }

    Classroom &operator=(const Classroom &c){
        if(this!=&c){
            this->numStudents=c.numStudents;
            this->capacity=c.capacity;
            delete[]students;
            this->students=new Student[c.numStudents];
            for(int i=0;i<numStudents;i++){
                this->students[i]=c.students[i];
            }
        }
        return *this;
    }

    void add(Student s){
        Student *tmp = new Student[numStudents+1];
        for(int i=0;i<numStudents;i++){
            tmp[i]=students[i];
        }
        tmp[numStudents]=s;
        numStudents++;
        delete[]students;
        students=tmp;
    }

    void remove(char *name){
        int flag=0;
        for(int i=0;i<numStudents;i++){
            if(students[i].daliIsti(name)){
                flag=1;
            }
        }
        if(flag==0){
            return;
        }
        Student *tmp = new Student[numStudents-1];
        int j=0;
        for(int i=0;i<numStudents;i++){
            if(!students[i].daliIsti(name)){
                tmp[j]=students[i];
                j++;
            }
        }
        numStudents--;
        delete[]students;
        students=tmp;
    }

    Student *getStudents(){
        return students;
    }

    int getNumStudents(){
        return numStudents;
    }

    void printStudents(){
        for(int i=0;i<numStudents;i++){
            cout<<students[i].getName();
            cout<<" ("<<students[i].getAge()<<","<<" "<<students[i].getMajor()<<")"<<endl;
        }
        cout<<endl;
    }

};
double findMedianAge(Classroom classroom){
    Student *students=classroom.getStudents();
    int n=classroom.getNumStudents()/2;
    double m=students[n].getAge();
    if(classroom.getNumStudents() % 2 == 0)
        m = (students[n].getAge() + students[n - 1].getAge()) / 2.0;

    return m;
}
//DO NOT CHANGE
int main() {
    int numClassrooms, numStudents;
    cin >> numClassrooms;
    Classroom classrooms[100];
    Student students[100];

    // Testing add method
    for (int i = 0; i < numClassrooms; i++) {
        cin >> numStudents;
        for (int j = 0; j < numStudents; j++) {
            char name[100], major[100];
            int age;
            cin >> name >> age >> major;
            Student student(name, age, major);
            classrooms[i].add(student);
            students[i*numStudents + j] = student;
        }
        cout<<"Classroom "<<i<<endl;
        classrooms[i].printStudents();
    }


    // Testing findMedianAge method
    int targetClassroom;
    cin >> targetClassroom;
    double medianAge = findMedianAge(classrooms[targetClassroom]);
    cout << "The median age in classroom " << targetClassroom << " is: " << medianAge << endl;
    cout<<"After removing the elements:"<<endl; /// Added
    // Testing remove method
    cin >> numStudents;
    for (int j = 0; j < numStudents; j++) {
        char name[100];
        cin >> name;
        for (int i = 0; i < numClassrooms; i++) {
            classrooms[i].remove(name);
        }
    }
    for (int i = 0; i < numClassrooms; i++) {
        cout<<"Classroom "<<i<<endl;
        classrooms[i].printStudents();
    }

    return 0;
}

