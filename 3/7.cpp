/*
Да се дефинира класа Film во која ќе се чуваат информации за:

name(низа од максимум 100 карактери) -име на филмот

rating (децимален број) - рејтинг на филмот

revenue(децимален број) - колку заработил филмот во милиони долари

Сите променливи внатре во класата треба да бидат приватни. Соодветно во рамките на класата да се дефинираат:

конструктор (без и со параметри)

деструктор

set методи

get методи

Да се дефинираат следните методи во класата:

display() која што ќе ги печати информациите за сметката во следниот формат:

Name of film: …

Rating: …

Revenue: …

Надвор од класата:

printMostPopularFilm(Film *films, int n) која што ќе го најде филмот со најголема заработувачка,

ДА НЕ СЕ МЕНУВА MAIN ФУНКЦИЈАТА.




For example:

Input	                Result
10
Inception 8.8 828.3
Titanic 7.8 2187.5
Avatar 7.8 2787.9
Jaws 8.0 470.7
Rocky 8.1 225.0
Grease 7.2 394.5
Alien 8.4 1043.4
Jumanji 7.0 962.1
Gladiator 8.5 460.5
Memento 8.4 39.7
                        -->Testing set methods and display()
                        Name of film: Memento
                        Rating: 8.4
                        Revenue: 39.7

                        -->Testing printMostPopularFilm()
                        Name of film: Avatar
                        Rating: 7.8
                        Revenue: 2787.9
 */
#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;

class Film{
    char name[100];
    float rating;
    float revenue;
public:
    Film(){}
    Film(char *name, float rating, float revenue){
        strcpy(this->name, name);
        this->rating=rating;
        this->revenue=revenue;
    }
    void setName(char *name){
        strcpy(this->name, name);
    }
    char *getName(){
        return name;
    }
    void setRating(float rating){
        this->rating=rating;
    }
    float getRating(){
        return rating;
    }
    void setRevenue(float revenue){
        this->revenue=revenue;
    }
    float getRevenue(){
        return revenue;
    }
    void display(){
        cout<<"Name of film: "<<getName()<<endl;
        cout<<"Rating: "<<getRating()<<endl;
        cout<<"Revenue: "<<getRevenue()<<endl;
    }
};
void printMostPopularFilm(Film *films, int n){
    int index=-1;
    int max=films[0].getRevenue();
    for(int i=0;i<n;i++){
        if(films[i].getRevenue()>max){
            max=films[i].getRevenue();
            index=i;
        }
    }
    films[index].display();
}
// DO NOT CHANGE THE MAIN FUNCTION
int main() {
    int n;
    cin >> n;
    Film films[100];

    char name[100];
    double rating;
    double revenue;

    for (int i = 0; i < n-1; i++)  {
        cin>>name;
        cin >> rating;
        cin >> revenue;

        // testing constructor with arguments
        films[i] = Film(name, rating, revenue);

    }


    // testing set methods and display for last element
    cin>>name;
    cin >> rating;
    cin >> revenue;
    films[n-1].setName(name);
    films[n-1].setRating(rating);
    films[n-1].setRevenue(revenue);

    cout<<"-->Testing set methods and display()"<<endl;
    films[n-1].display();
    cout<<endl;

    cout<<"-->Testing printMostPopularFilm()"<<endl;
    printMostPopularFilm(films , n);
    return 0;
}