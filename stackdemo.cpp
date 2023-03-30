#include <iostream>

using namespace std;

template <typename T>
class stack
{
public:
    stack(int size)
    {
        this->stackSize = 0;
        this->requestedSize = size;
        this->s = new T[requestedSize];
    }
    stack(const stack &s)
    {
        this->stackSize = s.stackSize;
        this->requestedSize = s.requestedSize;
        this->s = new T[requestedSize];
        for (int i = 0; i < requestedSize; i++)
        {
            this->s[i] = s.s[i];
        }
    }
    ~stack()
    {
        delete[] s;
    }

    const stack &operator=(const stack &s)
    {

        delete[] this->s;
        this->s = new T[s.requestedSize];
        for (int i = 0; i < stackSize; i++)
        {
            this->s[i] = s.s[i];
        }
        return *this;
    }

    bool empty()
    {
        if (stackSize != 0)
            return false;
        return true;
    }
    void push(const T &x)
    {
            s[stackSize] = x;
            stackSize++;

    }

    T pop()
    {
        stackSize -= 1;
        T lastElement = s[stackSize];
        return lastElement;
    }
    int size()
    {
        return stackSize;
    }

    friend ostream &operator<<(ostream &out, const stack &s)
    {
        out << '[';
        if (s.stackSize > 0)
        {
            for (int i = 0; i < s.stackSize - 1; i++)
            {
                out << s.s[i] << ", ";
            }
            out << s.s[s.stackSize - 1];
        }
        out << ']';
        return out;
    }

private:
    int stackSize;
    int requestedSize;
    T *s;
};

