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
    ConstRow(const ChessBoardArray &a, int i) : array(a), j(i){}; 
    int operator[](int i) const
    {
      return array.select(j, i);
    }

  private:
    const ChessBoardArray &array; 
    int j;                                
  };

public:
  ChessBoardArray(unsigned size = 0, unsigned base = 0) : data(new int[(size * size + 1) / 2]), arraybase(base), arraysize(size) {}

  ChessBoardArray(const ChessBoardArray &a) : data(new int[(a.arraysize * a.arraysize + 1) / 2]), arraybase(a.arraybase), arraysize(a.arraysize)
  {
    for (unsigned i = 0; i < ((arraysize * arraysize + 1) / 2); ++i)
      data[i] = a.data[i];
  }

  ~ChessBoardArray() { delete[] data; }

  ChessBoardArray &operator=(const ChessBoardArray &a)
  {
    delete[] data;
    arraybase = a.arraybase;
    arraysize = a.arraysize;
    data = new int[(arraysize * arraysize + 1) / 2];
    for (unsigned i = 0; i < ((arraysize * arraysize + 1) / 2); ++i)
      data[i] = a.data[i];
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
    for (int line = 0; line < a.arraysize; ++line)
    {
      for (int column = 0; column < a.arraysize; ++column)
      {
        cout << setw(4);
        if ((line + column) % 2 == 0) 
          cout << a.select(line + a.arraybase, column + a.arraybase); // access elements of even indexed rows and columns
        else
          cout << 0;
      }
      cout << endl;
    }
    return out;
  }

protected:
  int *data;
  int arraybase;
  unsigned arraysize;

  unsigned int loc(int i, int j) const throw(out_of_range)
  {
    int newi = i - arraybase, newj = j - arraybase;
    if (newi < 0 || newi >= arraysize || newj < 0 || newj >= arraysize || (i + j) % 2 == 1)
      throw out_of_range("invalid index");
    return (newi * arraysize + newj) / 2;
  }
};

int main() 
{
    ChessBoardArray a(4, 1); // size 4x4, rows and columns numbered from 1
    a[3][1] = 42;
    a[4][4] = 17;
    try { a[2][1] = 7; }
    catch(out_of_range &e) { cout << "a[2][1] is black" << endl; }
    try { cout << a[1][2] << endl; }
    catch(out_of_range &e) { cout << "and so is a[1][2]" << endl; }
    
    cout << a;
    
    return 0;
}
