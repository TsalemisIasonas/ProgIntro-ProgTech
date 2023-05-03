#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

class ChessBoardArray
{
protected:
    class Row
    {
    public:
        Row(ChessBoardArray &a, int i):array(a),i(i){}
        int &operator[](int i) const;
    private:
        ChessBoardArray &array;
        int i;
    };

    class ConstRow
    {
    public:
        ConstRow(const ChessBoardArray &a, int i);
        int operator[](int i) const;
    };

public:
    ChessBoardArray(unsigned size = 0, unsigned base = 0):size(size),base(base){
        data = new int[size*size];
    }
    ChessBoardArray(const ChessBoardArray &a){
        for (unsigned arraysize = 0; arraysize<size; arraysize++){
            data[arraysize] = 0;
        }
    };
    ~ChessBoardArray(){
        delete[] data;
    }

    ChessBoardArray &operator=(const ChessBoardArray &a);

    int &select(int i, int j){
        return data[loc(i,j)];
    }
    int select(int i, int j) const{
        // return data[loc(i,j)];
    }

    const Row operator[](int i);
    const ConstRow operator[](int i) const;

    friend ostream &operator<<(ostream &out, const ChessBoardArray &a){
        for (int rows = 0; rows<a.size; rows++){
            for (int cols = 0; cols<a.size; cols++){
                cout << setw(4);
                cout << a.select(rows,cols);
            }
            cout << endl;
        }
        return out;     // maybe select will not work
    }

private:
    int *data;
    unsigned size;
    unsigned base;

    unsigned int loc(int i, int j) throw (out_of_range) {
        i = base-i;
        j = base-j;

        if (i<0 || j<0 || i>size || j> size || (i+j)%2==1){
            throw out_of_range("Invalid square");
        }

        return (i-1)*size+1;    // maybe needs fixing
    }

};

int main(){
    for (int size=0; size<4; size++){
        for (int i=0; i<4; i++){
            cout << setw(4);
            cout << '0';
        }
    }
}