#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

class ChessBoardArray
{
private:
    int *data;
    unsigned size;
    unsigned base;

    unsigned int loc(int i, int j) const throw(out_of_range);

public:
    class Row
    {
    private:
        ChessBoardArray &parent;
        unsigned int row;

    public:
        Row(ChessBoardArray &a, int i);
        int &operator[](int i) const;
    };

    class ConstRow
    {
    private:
        const ChessBoardArray &parent;
        unsigned int row;

    public:
        ConstRow(const ChessBoardArray &a, int i);
        int operator[](int i) const;
    };

    ChessBoardArray(unsigned size = 0, unsigned base = 0);
    ChessBoardArray(const ChessBoardArray &a);
    ~ChessBoardArray();

    ChessBoardArray &operator=(const ChessBoardArray &a);

    int &select(int i, int j);
    int select(int i, int j) const;

    const Row operator[](int i);
    const ConstRow operator[](int i) const;

    friend ostream &operator<<(ostream &out, const ChessBoardArray &a);
};

ChessBoardArray::Row::Row(ChessBoardArray &a, int i)
    : parent(a), row(i)
{
}

int &ChessBoardArray::Row::operator[](int i) const
{
    return parent.data[parent.loc(row, i)];
}

ChessBoardArray::ConstRow::ConstRow(const ChessBoardArray &a, int i)
    : parent(a), row(i)
{
}

int ChessBoardArray::ConstRow::operator[](int i) const
{
    return parent.data[parent.loc(row, i)];
}

ChessBoardArray::ChessBoardArray(unsigned size, unsigned base)
    : size(size), base(base)
{
    data = new int[size*size];
    for (unsigned i = 0; i < size*size; i++)
        data[i] = 0;
}

ChessBoardArray::ChessBoardArray(const ChessBoardArray &a)
    : size(a.size), base(a.base)
{
    data = new int[size*size];
    for (unsigned i = 0; i < size*size; i++)
        data[i] = a.data[i];
}

ChessBoardArray::~ChessBoardArray()
{
    delete [] data;
}

ChessBoardArray &ChessBoardArray::operator=(const ChessBoardArray &a)
{
    if (this != &a)
    {
        delete [] data;
        size = a.size;
        base = a.base;
        data = new int[size*size];
        for (unsigned i = 0; i < size*size; i++)
            data[i] = a.data[i];
    }
    return *this;
}

int &ChessBoardArray::select(int i, int j)
{
    return data[loc(i, j)];
}

int ChessBoardArray::select(int i, int j) const
{
    return data[loc(i, j)];
}

const ChessBoardArray::Row ChessBoardArray::operator[](int i)
{
    return Row(*this, i);
}

const ChessBoardArray::ConstRow ChessBoardArray::operator[](int i) const
{
    return ConstRow(*this, i);
}

unsigned int ChessBoardArray::loc(int i, int j) const throw(out_of_range)
{
    unsigned row = base + i;
    unsigned col = base + j;

    if (row >= size || col >= size)
    {
        throw out_of_range("Index out of range.");
    }

    if ((row % 2) == (col % 2))
    {
        throw out_of_range("Invalid index for chess board array.");
    }

    return row*size + col/2;
}

ostream &operator<<(ostream &out, const ChessBoardArray &a)
{
    for (unsigned i = 0; i < a.size; i++)
    {
        for (unsigned j = 0; j < a.size; j++)
        {
            if ((i + j) % 2 == 0)
            {
                out << setw(4) << " ";
            }
            else
            {
                out << setw(4) << a.select(i, j);
            }
        }
        out << endl;
    }

    return out;
}


int main() {
 ChessBoardArray a(4, 1); // size 4x4, rows and columns numbered from 1
 a[3][1] = 42;
 a[4][4] = 17;
 try { a[2][1] = 7; }
 catch(out_of_range &e) { cout << "a[2][1] is black" << endl; }
 try { cout << a[1][2] << endl; }
 catch(out_of_range &e) { cout << "and so is a[1][2]" << endl; }
 cout << a;
 }