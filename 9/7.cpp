/*
Да се дефинира апстрактна класа User за која ќе се чуваат:

username (char[50])
password (char[50])
email (char[50])
Класата треба да содржи еден чист виртуелен метод double popularity().

Од оваа класа да се изведат две класи и тоа FacebookUser и TwitterUser.

За класата FacebookUser уште се чуваат и:

број на пријатели
број на лајкови и
број на коментари
Популарноста се пресметува така што се собираат бројот на пријатели, бројот на лајкови и бројот на коментари, но притоа бројот на лајкови се множи со коефициент на вредност на лајкот кој е ист за секој корисник и изнесува 0.1, а исто така и бројот на коментари се множи со ист таков коефициент кој е 0.5.

За класата TwitterUser уште се чуваат и:

број на следачи и
број на твитови
Популарноста се пресметува така што се собираат бројот на следачи и бројот на твитови, но притоа бројот на твитови се множи со коефициент на вредност на твитот кој е ист за секој корисник и изнесува 0.5.

Да се креира класа SocialNetwork која ќе содржи:

динамичка низа од покажувачи од класата User
број на тековни корисници и
максимален број на корисници кој може да го содржи мрежата и кој е ист за сите мрежи и иницијално е поставен на 5
Да се преоптовари операторот += со кој ќе се додава нов корисник.

Да се дефинира метод avgPopularity() кој ќе ја враќа просечната популарност на корисниците во мрежата.

Исто така да се овозможи промена на максималната големина на низата преку методот changeMaximumSize(int number).

Потребно е да се справите со следните исклучоци:

Доколку лозинката на корисникот не содржи барем 1 голема буква, 1 мала буква и 1 број да се фрли исклучок од класа InvalidPassword така што како параметар ќе се прати пораката Password is too weak.
Доколку емаилот на корисникот не содржи точно еднаш @ да се фрли исклучок од класа InvalidEmail така што како параметар ќе се прати пораката Mail is not valid.
Доколку проба да се додаде корисник во социјалната мрежа, а веќе максималниот број на корисници е пополнет да се фрли исклучок од класа MaximumSizeLimit така што како параметар ќе се прати максималниот број на корисници во мрежата.
Сите класи кои се справуваат со исклучоци треба да го имаат имплементирано методот void message() така што за првите две класи ќе ја печати пораката којашто е испратена како параметар, а за последната класа ќе печати You can't add more than N users, каде што N е параметарот кој е пратен. Исто така со try-catch блокови справете се со исклучоците на соодветните места во main(), каде што во catch ќе го повикате методот message() од соодветниот исклучок.

For example:

Input	                                                        Result
4
blazer Gargamel2  blazeryahoo.com 1 123 411 204
Scooby cart00nNetw0rk scoobydoo@gmail.com 1 282 1098 41
IronMan Avangers iron@man.com 2 678 1025
Dexter Massuc0 lisbon@dexter.com 2 418 299
EdSheeran D1v1d3 edsheeran@sheeran.com 2 10423 188
                                                                Mail is not valid.
                                                                Password is too weak.
                                                                2064.43
 */
#include<iostream>
#include<cstring>
using namespace std;

class InvalidPassword{
    char text[50];
public:
    InvalidPassword(char *text){
        strcpy(this->text, text);
    }
    void message(){
        cout<<text<<endl;
    }
};

class InvalidEmail{
    char text[50];
public:
    InvalidEmail(char *text){
        strcpy(this->text, text);
    }
    void message(){
        cout<<text<<endl;
    }
};

class MaximumSizeLimit{
    int n;
public:
    MaximumSizeLimit(int n=0){
        this->n=n;
    }
    void message(){
        cout<<"You can't add more than "<<n<<" users."<<endl;
    }
};

class User{
protected:
    char username[50];
    char password[50];
    char email[50];
public:
    User(char *username="", char *password="", char *email=""){
        strcpy(this->username, username);
        setPassword(password);
        setEmail(email);
    }
    virtual double popularity()=0;
    void setPassword(char *password=""){
        int mala=0, golema=0, br=0;
        for(int i=0;i<strlen(password);i++){
            if(password[i]>='A' && password[i]<='Z'){
                golema++;
            }
            else if(password[i]>='a' && password[i]<='z'){
                mala++;
            }
            else if(password[i]>='0' && password[i]<='9'){
                br++;
            }
        }
        if(!mala || !golema || !br){
            throw InvalidPassword("Password is too weak.");
        }
        strcpy(this->password, password);
    }
    void setEmail(char *email=""){
        int br=0;
        for(int i=0;i<strlen(email);i++){
            if(email[i]=='@'){
                br++;
            }
        }
        if(br==1){
            strcpy(this->email, email);
        }else{
            throw InvalidEmail("Mail is not valid.");
        }
    }
};

class FacebookUser: public User{
    int brPrijateli;
    int brLajkovi;
    int brKomentari;
public:
    FacebookUser(char *username="", char *password="", char *email="", int brPrijateli=0, int brLajkovi=0, int brKometari=0) : User(username, password, email){
        this->brPrijateli=brPrijateli;
        this->brLajkovi=brLajkovi;
        this->brKomentari=brKometari;
    }
    double popularity(){
        return (brLajkovi*0.1) + (brKomentari*0.5) + brPrijateli;
    }
};

class TwitterUser: public User{
    int brSledaci;
    int brTvitovi;
public:
    TwitterUser(char *username="", char *password="", char *email="", int brSledaci=0, int brTvitovi=0) : User(username, password, email){
        this->brSledaci=brSledaci;
        this->brTvitovi=brTvitovi;
    }
    double popularity(){
        return (brTvitovi*0.5) + brSledaci;
    }
};

class SocialNetwork{
    User **users;
    int brKorisnici;
    static int MAX_KORISNICI;
    void copy(const SocialNetwork &sn){
        this->brKorisnici=sn.brKorisnici;
        this->users = new User * [brKorisnici];
        for(int i=0;i<brKorisnici;i++){
            users[i]=sn.users[i];
        }
    }
public:
    SocialNetwork(){
        this->brKorisnici=0;
        this->users = new User * [brKorisnici];
    }
    SocialNetwork(const SocialNetwork &sn){
        copy(sn);
    }
    SocialNetwork &operator=(const SocialNetwork &sn){
        if(this!=&sn){
            delete[]users;
            copy(sn);
        }
        return *this;
    }
    SocialNetwork &operator+=(User *u){
        if(brKorisnici==MAX_KORISNICI){
            throw MaximumSizeLimit(MAX_KORISNICI);
        }
        User **temp = new User*[brKorisnici+1];
        for(int i=0;i<brKorisnici;i++){
            temp[i]=users[i];
        }
        temp[brKorisnici++]=u;
        delete[]users;
        users=temp;
        return *this;
    }
    double avgPopularity(){
        double total=0;
        for(int i=0;i<brKorisnici;i++){
            total+=users[i]->popularity();
        }
        return total/brKorisnici;
    }
    static void changeMaximumSize(int number){
        SocialNetwork::MAX_KORISNICI=number;
    }
};
int SocialNetwork::MAX_KORISNICI=5;

int main() {

    SocialNetwork network = SocialNetwork();
    int n;
    cin >> n;
    char username[50];
    char password[50];
    char email[50];
    int userType;
    for (int i=0; i < n; ++i) {
        cin >> username;
        cin >> password;
        cin >> email;
        cin >> userType;
        if (userType == 1) {
            int friends;
            int likes;
            int comments;
            cin >> friends >> likes >> comments;

            // TODO: Try-catch
            try{
                User * u = new FacebookUser(username,password,email,friends,likes,comments);
                network += u;
            }
            catch(InvalidPassword &ip){
                ip.message();
            }
            catch (InvalidEmail &ie){
                ie.message();
            }
            catch (MaximumSizeLimit &ml){
                ml.message();
            }
        }
        else {
            int followers;
            int tweets;
            cin >> followers >> tweets;

            // TODO: Try-catch
            try{
                User * u= new TwitterUser(username,password,email,followers,tweets);
                network += u;
            }
            catch(InvalidPassword &ip){
                ip.message();
            }
            catch (InvalidEmail &ie){
                ie.message();
            }
            catch (MaximumSizeLimit &ml){
                ml.message();
            }
        }

    }
    network.changeMaximumSize(6);
    cin >> username;
    cin >> password;
    cin >> email;
    int followers;
    int tweets;
    cin >> followers >> tweets;

    // TODO: Try-catch
    try{
        User * u= new TwitterUser(username,password,email,followers,tweets);
        network += u;
    }
    catch(InvalidPassword &ip){
        ip.message();
    }
    catch (InvalidEmail &ie){
        ie.message();
    }
    catch (MaximumSizeLimit &ml){
        ml.message();
    }

    cout << network.avgPopularity();
}