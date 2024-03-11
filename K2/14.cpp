/*
Во рамките на еден телекомуникациски оператор, СМС пораките се делат на регуларни и специјални. За секојa СМС порака се знае:

основна цена за една порака до 160 знаци (реален број)
претплатнички број на кој е испратена (низа од знаци со должина 12)
Класата за опишување на СМС пораки е апстрактна (5 поени).

За секоја Регуларна СМСдополнително се чуваат податоци за текстот на пораката и тоа дали е користена роаминг услуга (bool променлива). За секоја Специјална СМС дополнително се чуваат податоци за тоа дали е наменета за хуманитарни цели (bool променлива). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

Метод SMS_cena(), за пресметување на цената на испратена СМС порака на следниот начин: (10 поени)

За регуларна СМС - цената се зголемува за 300% од основната цена ако е испратена од странство, а 18% од дома и цената се формира врз база на тоа во колку СМС пораки ќе го собере текстот што сакаме да го испратиме. Една регуларна порака може да собере најмногу 160 знаци. Притоа, доколку се надмине 160-от знак, се започнува нова порака и цената се пресметува како за две или повеќе пораки (пр. за 162 знаци, цената на СМС е иста како и за 320 знаци).
За специјална СМС - цената се зголемува за 150% од основната цена ако пораката HE е наменета за хуманитарни цели. Доколку е наменета за тоа, данокот од 18% не се пресметува на цената.
Пресметувањето 18% данок на цената на сите СМС пораки е фиксен и не се менува, додека пак процентот од 300% за регуларни и 150% за специјални СМС е променлив и во зависност од операторот може да се менува. Да се обезбеди механизам за можност за нивно менување. (5 поени)
Преоптоварен оператор << за печатење на податоците за СМС пораките во формат: (5 поени)

Тел.број: цена
Да се имплементира функција vkupno_SMS со потпис:

void vkupno_SMS(SMS** poraka, int n)
во која се печати вкупниот број на регуларни СМС пораки и нивната вкупна цена, како и бројот на специјални СМС пораки и нивната вкупна цена во проследената низа посебно. (15 поени)

Да се обезбедат сите потребни функции за правилно функционирање на програмата (5 поени).
 */
#include <iostream>
#include <cstring>
using namespace std;

class SMS
{
protected:
    float cena;
    char telbroj[14];
    static const float tax;
public:
    SMS(){}
    SMS(char *telbroj,float cena)
    {
        strcpy(this->telbroj,telbroj);
        this->cena=cena;
    }
    virtual ~SMS(){}

    virtual float SMS_Cena()=0;

    char *getTel()
    {
        return telbroj;
    }

};
const float SMS::tax=0.18;

class RegularSMS:public SMS
{
protected:
    char *text;
    bool roaming;
    static float vartax;
public:
    RegularSMS(char *telbroj,float cena,char *text,bool roaming):SMS(telbroj,cena)
    {
        this->roaming=roaming;
        this->text=new char[strlen(text)+1];
        strcpy(this->text,text);
    }
    ~RegularSMS()
    {
        delete [] text;
    }
    float SMS_Cena()
    {
        float total=cena;

        if(roaming==true)
        {
            total*=(1+vartax/100);
        }
        else
        {

            total=total*(1+SMS::tax);
        }
        if(strlen(text)>160)
        {
            total=total*(1+strlen(text)/160);

        }
        return total;
    }
    friend ostream &operator<<(ostream &out,RegularSMS &sp)
    {

        out<<"Tel: "<<sp.telbroj<<" - cena: "<<sp.SMS_Cena()<<"den."<<endl;
        return out;
    }
    static void set_rProcent(int num)
    {
        vartax=num;
    }

};
float RegularSMS::vartax=300;

class SpecialSMS:public SMS
{
protected:
    bool humanitarnost;
    static float taxvar;
public:
    SpecialSMS(char *telbroj,float cena,bool humanitarnost):SMS(telbroj,cena)
    {
        this->humanitarnost=humanitarnost;
    }
    ~SpecialSMS(){}
    float SMS_Cena()
    {
        float total=cena;

        if(humanitarnost==false)
        {
            total*=(1+taxvar/100);
        }
        return total;
    }
    friend ostream &operator<<(ostream &out,SpecialSMS &sp)
    {
//        out<<sp.telbroj<<": "<<sp.SMS_Cena()<<endl;
        out<<"Tel: "<<sp.telbroj<<" - cena: "<<sp.SMS_Cena()<<"den."<<endl;
        return out;
    }
    static void set_sProcent(int num)
    {
        taxvar=num;
    }
};
float SpecialSMS::taxvar=150;


void vkupno_SMS(SMS** poraka, int n)
{
    int reg,spec;
    float cenreg=0,censpec=0;
    reg=spec=0;

    for(int i=0;i<n;i++)
    {
        RegularSMS *r=dynamic_cast<RegularSMS *>(poraka[i]);
        if(r!=0)
        {
            reg++;
            cenreg+=r->SMS_Cena();
        }
        SpecialSMS *s=dynamic_cast<SpecialSMS *>(poraka[i]);
        if(s!=0)
        {
            spec++;
            censpec+=s->SMS_Cena();
        }
    }

    cout<<"Vkupno ima "<<reg<<" regularni SMS poraki i nivnata cena e: "<<cenreg<<endl;
    cout<<"Vkupno ima "<<spec<<" specijalni SMS poraki i nivnata cena e: "<<censpec<<endl;

}
ostream &operator<<(ostream &out,SMS &sp)
{
    RegularSMS *r=dynamic_cast<RegularSMS *>(&sp);
    if(r!=0)
    {
        cout<<*r;
    }
    SpecialSMS *sr=dynamic_cast<SpecialSMS *>(&sp);
    if(sr!=0)
    {
        cout<<*sr;
    }
    return out;
}

int main(){

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i<n; i++){

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            }
            else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}
