#include <iostream>

using namespace std;

class Animal {
    private:
    string name;

    public:

    void setName(string name){
        this->name = name;
    }

    string getName(){
        return name;
    }

    virtual void suara(){
        cout << "Suara Hewan\n";
    }
};


class Cat : public Animal{
    public:
    void suara() override{
        cout << "Meoooongg\n";
    }
};

class Dog : public Animal{
    public:
    void suara() override{
        cout << "Gog Gog\n";
    }
};




int main(){
    Cat kucing;
    Dog anjing;

    
    kucing.setName("Kucing");
    anjing.setName("Anjing");
    
    cout << "Nama Hewan 1: "  << kucing.getName() << endl;
    cout << "Suara: "; 
    kucing.suara();
    
    cout << "Nama Hewan 2: "  << anjing.getName() << endl;
    cout << "Suara: ";
    anjing.suara();

}


