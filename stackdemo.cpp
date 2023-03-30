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
            stackSize++;
        }
    }
    ~stack()
    {
        delete[] s;
    }

    const stack &operator=(const stack &s) {
        for (int i=0; i<s.stackSize; i++){
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
    void push(const T &x){
        if (stackSize < requestedSize){
            s[stackSize] = x;
            stackSize++;
        }
    }

    T pop() {
        stackSize-=1;
        T lastElement = s[stackSize];
        return lastElement;
    }
    int size()
    {
        return stackSize;
    }

    friend ostream &operator<<(ostream &out, const stack &s)
    {
        for (int i = 0; i < s.stackSize; i++)
        {
            out << s.s[i] << " ";
        }
        return out;
    }

private:
    int stackSize;
    int requestedSize;
    T *s;
};

