#include <iostream>  // include input/output stream library
#include <iomanip>   // include input/output manipulation library
#include <stdexcept> // include standard exception library
using namespace std; // use the standard namespace

class ChessBoardArray
{          // define a class called ChessBoardArray
protected: // protected members can only be accessed by derived classes
  class Row
  { // define a nested class called Row
  public:
    Row(ChessBoardArray &a, int i) : chessBoardArray(a), row(i) {} // constructor for Row
    int &operator[](int i) const
    {                                        // define the [] operator for Row, return by reference
      return chessBoardArray.select(row, i); // return the selected element of ChessBoardArray by reference
    }

  private:
    ChessBoardArray &chessBoardArray; // ChessBoardArray reference
    int row;                          // an integer for row index
  };
  class ConstRow
  { // define another nested class called ConstRow
  public:
    ConstRow(const ChessBoardArray &a, int i) : chessBoardArray(a), row(i){}; // constructor for ConstRow
    int operator[](int i) const
    {                                        // define the [] operator for ConstRow, return by value
      return chessBoardArray.select(row, i); // return the selected element of ChessBoardArray by value
    }

  private:
    const ChessBoardArray &chessBoardArray; // constant ChessBoardArray reference
    int row;                                // an integer for row index
  };

public:
  // Constructor with default arguments, creates a new ChessBoardArray object
  // with the specified size and base values. Allocates memory for data array.
  ChessBoardArray(unsigned size = 0, unsigned base = 0) : data(new int[(size * size + 1) / 2]), thebase(base), thesize(size) {}

  // Copy constructor, creates a new ChessBoardArray object by copying the data
  // from another ChessBoardArray object. Allocates memory for data array.
  ChessBoardArray(const ChessBoardArray &a) : data(new int[(a.thesize * a.thesize + 1) / 2]), thebase(a.thebase), thesize(a.thesize)
  {
    for (unsigned i = 0; i < ((thesize * thesize + 1) / 2); ++i)
      data[i] = a.data[i];
  }

  // Destructor, frees the memory allocated for the data array.
  ~ChessBoardArray() { delete[] data; }

  // Assignment operator, assigns the contents of another ChessBoardArray object
  // to this ChessBoardArray object. Allocates memory for data array.
  ChessBoardArray &operator=(const ChessBoardArray &a)
  {
    delete[] data;
    thebase = a.thebase;
    thesize = a.thesize;
    data = new int[(thesize * thesize + 1) / 2];
    for (unsigned i = 0; i < ((thesize * thesize + 1) / 2); ++i)
      data[i] = a.data[i];
    return *this;
  }

  // Returns a reference to the element at position (i,j) of the ChessBoardArray object.
  int &select(int i, int j)
  {
    return data[loc(i, j)];
  }

  // Returns a copy of the element at position (i,j) of the ChessBoardArray object.
  int select(int i, int j) const
  {
    return data[loc(i, j)];
  }

  // Returns a Row object representing the row at index i of the ChessBoardArray object.
  const Row operator[](int i)
  {
    return Row(*this, i);
  }

  // Returns a ConstRow object representing the row at index i of the ChessBoardArray object.
  const ConstRow operator[](int i) const
  {
    return ConstRow(*this, i);
  }

  // Overloads the << operator to output the ChessBoardArray object to the given ostream.
  friend ostream &operator<<(ostream &out, const ChessBoardArray &a)
  {
    for (int line = 0; line < a.thesize; ++line)
    {
      for (int sthlh = 0; sthlh < a.thesize; ++sthlh)
      {
        cout << setw(4);
        if ((line + sthlh) % 2 == 0)
          cout << a.select(line + a.thebase, sthlh + a.thebase);
        else
          cout << 0;
      }
      cout << endl;
    }
    return out;
  }

protected:
  int *data;
  int thebase;
  unsigned thesize;
  // Helper function to compute the index into the data array given row i and column j.
  // Throws an out_of_range exception if the indices are invalid.
  unsigned int loc(int i, int j) const throw(out_of_range)
  {
    int di = i - thebase, dj = j - thebase;
    if (di < 0 || di >= thesize || dj < 0 || dj >= thesize || (i + j) % 2 == 1)
      throw out_of_range("invalid index");
    return (di * thesize + dj) / 2;
  }
};

int main() 
{
    cout << "run";
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