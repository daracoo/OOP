/*
Да се имплементира класа Game за која се чува:
title (низа од карактери)
Во класата да се имплементира виртуелна функција void displayInfo() која на екран печати информации за дадената игра и виртуелна функција int complexity() која ја враќа комплексноста на играта.

Потребно е да се имплементира класите BoardGame и CardGame кои што ќе наследуваат од класата Game.

За класата BoardGame дополнително се чуваат:

maxPlayers - максимален број на играчи (цел број)
Доколку максималниот број на играчи е поголем од 6 тогаш комплексноста е 10, доколку  максималниот број на играчи е поголем од 3 а помал од 6 тогаш комплексноста е 5, а доколку е помал од 3, тогаш комплексноста е 3.

Функцијата displayInfo() печати во формат:

Game: [наслов на игра]

Max players: [максимален број на играчи]

Complexity: [комплексност]

За класата CardGame дополнително се чуваат:

numCards - број на карти (цел број)
Доколку бројот на карти е поголем од 20 тогаш комплексноста е 10, доколку  бројот на карти е поголем од 10 а помал од 20 тогаш комплексноста е 5, а доколку е помал од 10, тогаш комплексноста е 3.

Функцијата displayInfo() печати во формат:

Game: [наслов на игра]

Number of cards: [број на карти]

Complexity: [комплексност]


Потребно е да се имплементира класата BoardCardGame која што ќе наследува од класите BoardGame и CardGame.

Комплексноста е пресметана на следниот начин: (комплексноста на CardGame + комплексноста на BoardGame)/2

Функцијата displayInfo() печати во формат:

Game: [наслов на игра]

Complexity: [комплексност]

Да се направи глобална функција Game *mostComplexCardGame(Game **games, int n) што ќе врати покажувач до најкомплексната игра со карти.


For example:

Input	    Result
0
6
1
Game1 7
0
Game2 8
1
Game3 2
0
Game4 15
1
Game5 7
0
Game6 9
1
            Game: Game4
            Number of cards: 15
            Complexity: 5
 */
#include <iostream>
#include <cstring>

using namespace std;

class Game{
protected:
    char title[20];
public:
    Game(char *title=""){
        strcpy(this->title,title);
    }
    virtual void displayInfo(){
        cout<<"Game: "<<title<<endl;
    }
    virtual int complexity()=0;
    virtual int getCards(){
        return 0;
    }
};

class BoardGame: virtual public Game{
protected:
    int maxPlayers;
public:
    BoardGame(char *title="", int maxPlayers=0) : Game(title){
        this->maxPlayers=maxPlayers;
    }
    int complexity(){
        if(maxPlayers>6){
            return 10;
        }else if(maxPlayers>3 && maxPlayers<6){
            return 5;
        }else if(maxPlayers<3){
            return 3;
        }
    }
    void displayInfo(){
        Game::displayInfo();
        cout<<"Max players: "<<maxPlayers<<endl;
        cout<<"Complexity: "<<complexity()<<endl;
    }
};

class CardGame: virtual public Game{
protected:
    int numCards;
public:
    CardGame(char *title="", int numCards=0): Game(title){
        this->numCards=numCards;
    }
    int complexity(){
        if(numCards>20){
            return 10;
        }else if(numCards>10 && numCards<20){
            return 5;
        }else if(numCards<10){
            return 3;
        }
    }
    void displayInfo(){
        Game::displayInfo();
        cout<<"Number of cards: "<<numCards<<endl;
        cout<<"Complexity: "<<complexity()<<endl;
    }
    int getCards(){
        return numCards;
    }
};

class BoardCardGame: public BoardGame, public CardGame{
public:
    BoardCardGame(char *title="", int maxPlayers=0, int numCards=0) : BoardGame(title, maxPlayers), CardGame(title, numCards),
                                                                      Game(title){

    }
    int complexity(){
        return (BoardGame::complexity() + CardGame::complexity()) / 2;
    }
    void displayInfo(){
        Game::displayInfo();
        cout<<"Complexity: "<<complexity()<<endl;
    }
};

Game *mostComplexCardGame(Game **games, int n){
    Game *max=games[0];
    for(int i=1;i<n;i++){
        if(games[i]->getCards()>max->getCards()){
            max=games[i];
        }
    }
    return max;
}

int main() {
    char title[50];
    int maxPlayers;
    int numCards;
    int n;
    int choice;

    cin>>choice;
    if(choice==1)
    {
        cin>>title;
        BoardCardGame boardCardGame(title, 8, 15);
        boardCardGame.displayInfo();
    }
    else {

        cin >> n;

        Game **g = new Game *[n];
        for (int i = 0; i < n; i++) {
            cin >> choice;
            if (choice == 1) {
                cin >> title >> maxPlayers;

                g[i] = new BoardGame(title, maxPlayers);
            } else {
                cin >> title >> numCards;

                g[i] = new CardGame(title, numCards);
            }

        }

        mostComplexCardGame(g,n)->displayInfo();

    }


    return 0;
}