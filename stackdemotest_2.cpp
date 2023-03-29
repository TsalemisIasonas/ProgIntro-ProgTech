#include <iostream>

using namespace std;

template <typename T>
class stack
{
public:
    stack(int size)
    {
        capacity = size;
        topIndex = -1;
        array = new T[capacity];
    }

    stack(const stack &s)
    {
        capacity = s.capacity;
        topIndex = s.topIndex;
        array = new T[capacity];
        for (int i = 0; i <= topIndex; i++)
        {
            array[i] = s.array[i];
        }
    }

    ~stack()
    {
        delete[] array;
    }

    const stack &operator=(const stack &s)
    {
        if (this != &s)
        {
            delete[] array;
            capacity = s.capacity;
            topIndex = s.topIndex;
            array = new T[capacity];
            for (int i = 0; i <= topIndex; i++)
            {
                array[i] = s.array[i];
            }
        }
        return *this;
    }

    bool empty()
    {
        return topIndex == -1;
    }

    void push(const T &x)
    {
        if (topIndex == capacity - 1)
        {
            T *tempArray = new T[2 * capacity];
            for (int i = 0; i <= topIndex; i++)
            {
                tempArray[i] = array[i];
            }
            delete[] array;
            array = tempArray;
            capacity *= 2;
        }
        topIndex++;
        array[topIndex] = x;
    }

    T pop()
    {
        if (topIndex == -1)
        {
            throw "Stack is empty";
        }
        T temp = array[topIndex];
        topIndex--;
        return temp;
    }

    int size()
    {
        return topIndex + 1;
    }

    friend ostream &operator<<(ostream &out, const stack &s)
    {}
