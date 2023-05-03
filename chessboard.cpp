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

    int &select(int i, int j);
    int select(int i, int j) const;

    const Row operator[](int i);
    const ConstRow operator[](int i) const;

    friend ostream &operator<<(ostream &out, const ChessBoardArray &a);

private:
    int *data;
    unsigned size;
    unsigned base;

};