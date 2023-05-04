#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

class ChessBoardArray
{
protected:
    int *data;
    unsigned arraysize;
    int arraybase;
    unsigned int loc(int i, int j) const throw(out_of_range){
        int newi = i-arraybase;
        int newj = j-arraybase;
        if (newi <0 || newj <0 || newi >= arraysize || newj>= arraysize || (i+j)%2==1) throw out_of_range("Forbidden");
        return (newi*arraysize + newj)/2;
    }
    class Row
    {
    public:
        Row(ChessBoardArray &a, int i): array(a), j(i){}
        int &operator[](int i) const{
            return array.select(j,i);
        }
    private:
        ChessBoardArray &array;
        int j;
    };

    class ConstRow
    {
    public:
        ConstRow(const ChessBoardArray &a, int i): array(a), j(i){}
        int operator[](int i) const{
            return array.select(j,i);
        }
    private:
        const ChessBoardArray &array;
        int j;
    };

public:
    ChessBoardArray(unsigned size = 0, unsigned base = 0){
        data = new int [(size*size+1)/2];
        arraysize = size;
        arraybase = base;
    }
    ChessBoardArray(const ChessBoardArray &a){
        data = new int [(a.arraysize*a.arraysize+1)/2];
        arraysize = a.arraysize;
        arraybase = a.arraybase;
        for (unsigned i = 0; i<(a.arraysize*a.arraysize+1)/2; i++){
            data[i] = a.data[i];
        }
    }
    ~ChessBoardArray(){
        delete[] data;
    }

     ChessBoardArray &operator=(const ChessBoardArray &a)
    {
        delete[] data;
        arraybase = a.arraybase;
        arraysize = a.arraysize;
        
        data = new int[(arraysize * arraysize + 1)/2];
        for (unsigned i = 0; i < (arraysize * arraysize + 1)/2; i++)
        {
            data[i] = a.data[i];
        }

        return *this;
    }

    int &select(int i, int j){
        return data[loc(i,j)];
    }
    int select(int i, int j) const{
        return data[loc(i,j)];
    }

    const Row operator[](int i){
        return Row(*this, i);
    }
    const ConstRow operator[](int i) const{
        return ConstRow(*this, i);
    }

    friend ostream &operator<<(ostream &out, const ChessBoardArray &a){
        for (int i = 0; i< a.arraysize; i++){
            for (int j = 0; j<a.arraysize; j++){
                cout << setw(4);
                if ((i+j)%2==0){
                    cout <<a.select(i+a.arraybase,j+a.arraybase);
                }
                else cout <<0;
            }
            cout <<endl;
        }
        return out;
    }
};












