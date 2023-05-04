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
        Row(ChessBoardArray &a, int i) : array(a), j(i) {}
        int &operator[](int i) const
        {
            return array.select(j, i);
        }

    private:
        ChessBoardArray &array;
        int j;
    };

    class ConstRow
    {
    public:
        ConstRow(const ChessBoardArray &a, int i) : array(a), j(i) {}
        int operator[](int i) const
        {
            return array.select(j, i);
        }

    private:
        const ChessBoardArray &array;
        int j;
    };

public:
    ChessBoardArray(unsigned size = 0, unsigned base = 0) : size(size), base(base)
    {
        data = new int[size * size];
        for (unsigned i =0; i<size*size; i++){
            data[i] = 0;
        }
    }
    ChessBoardArray(const ChessBoardArray &a) : data(new int[a.size * a.size]), size(a.size), base(a.base)
    {
        for (unsigned i = 0; i < a.size * a.size; i++)
        {
            data[i] = a.data[i];
        }
    };
    ~ChessBoardArray()
    {
        delete[] data;
    }

    ChessBoardArray &operator=(const ChessBoardArray &a)
    {
        delete[] data;
        data = new int[a.size * a.size];
        size = a.size;
        base = a.base;

        for (unsigned i = 0; i < a.size * a.size; i++)
        {
            data[i] = a.data[i];
        }

        return *this;
    }

    int &select(int i, int j)
    {
        return data[loc(i, j)];
    }
    int select(int i, int j) const
    {
        return data[loc(i, j)];
    }

    const Row operator[](int i)
    {
        return Row(*this, i);
    }

    const ConstRow operator[](int i) const
    {
        return ConstRow(*this, i);
    }

    friend ostream &operator<<(ostream &out, const ChessBoardArray &a)
    {
        for (unsigned i = 0; i < a.size; i++)
        {
            for (unsigned j = 0; j < a.size; j++)
            {
                out << setw(4) << a.select(i,j);
            }
            out << endl;
        }
        return out;
    }

private:
    int *data;
    unsigned size;
    unsigned base;

    unsigned loc(int i, int j) const throw(out_of_range)
    {
        i = base - i;
        j = base - j;

        if (i < 1 || j < 1 || i > size || j > size || (i + j) % 2 == 0)
        {
            throw out_of_range("Invalid square");
        }

        return (i - 1) * size + (j - 1);
    }
};

int main()
{
    ChessBoardArray a(4, 1); // size 4x4, rows and columns numbered from 1
    a[3][1] = 42;
    a[4][4] = 17;
    try
    {
        a[2][1] = 7;
    }
    catch (out_of_range &e)
    {
        cout << "a[2][1] is black" << endl;
    }
    try
    {
        cout << a[1][2] << endl;
    }
    catch (out_of_range &e)
    {
        cout << "and so is a[1][2]" << endl;
    }

    cout << a;

    return 0;
}