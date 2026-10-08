#include <iostream>

using namespace std;

class Robot{
protected:
    int x;
    int y;


public:
    virtual void Think(){

    }

};


class Striker : public Robot{   
public:
    void Think() override{

    }
    
};

class Field{
    private:
        static const int ROW = 12;
        static const int COLS = 18;

        char grid[ROW][COLS];

    public:
        Field(){
            for (int i = 0;i < ROW; i++){
                for(int j = 0; j < COLS;j++){
                    grid[i][j] = '.';
                }
            }
        }

        void display() {
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COLS; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
        
};


int main(){
    Striker striker;
    Field field;

    field.display();

    


}