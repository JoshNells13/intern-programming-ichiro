#include <iostream>

using namespace std;

class Robot{
    private:


    protected :
        string nama;
        int batrei;
    public :
        Robot(string nama = "",int batrei = 0) : nama(nama),batrei(batrei) {}
        virtual void aksi(){
            cout << "Robot Kebanggan ITS kata Ku";
        }

};

class RoboAmba : public Robot{
    public:
        RoboAmba (string nama = "AMBATUKAM X MEN",int batrei = 50 ) : Robot(nama,batrei) {};
        void aksi() override{
            if(batrei >= 30){
                batrei -= 20;
                cout << nama  <<" Aksi Ambatukamm Dimulai Sisa Batrei: " << batrei << endl;
            }else{
                cout << nama  << " Batrei Nya Ngak Cukup Sayangg: " << batrei << endl;
            }
        }
};

class RoboGula : public Robot{
    public:
    RoboGula (string nama = "GULE GULE",int batrei = 50) : Robot(nama,batrei) {}
    void aksi() override{
        if(batrei >= 20){
            batrei -= 20;
            cout << nama << " Aksi Mencari Manis Dimulai Sisa Batrei: " << batrei << endl;
        }else{
            cout << nama << "Batrei Nya Ngak Cukup Sayangg: " << batrei << endl;
        }
    }
};



int main(){

    Robot* robot1 = new RoboAmba("Ambatukam-001",100);
    Robot* robot2 = new RoboGula("Sweet-022",100);

    robot1->aksi();
    robot2->aksi();
  
    

}