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
    stack(const stack &other)
    {
        this->stackSize = other.stackSize;
        this->requestedSize = other.requestedSize;
        this->s = new T[requestedSize];
        for (int i = 0; i < requestedSize; i++)
        {
            this->s[i] = other.s[i];
        }
    }
    ~stack()
    {
        delete[] s;
    }

    const stack &operator=(const stack &other)
    {
        if (this != &other) 
        {    
            T *temp = new T[other.requestedSize];
            for (int i = 0; i < other.stackSize; ++i)
            {
                temp[i] = other.s[i];
            }
            
            delete[] s;
            stackSize = other.stackSize;
            requestedSize = other.requestedSize;
            s = temp;
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
        if (stackSize < requestedSize)
        {
            *(s + stackSize++) = x;
        }
    }

    T pop()
    {
        if (stackSize == 0)
            throw out_of_range("stack<T>::pop(): empty stack");
        return s[--stackSize];
    }

    int size()
    {
        return stackSize;
    }

    friend ostream &operator<<(ostream &out, const stack &st)
    {
        out << '[';
        if (st.stackSize > 0)
        {
            for (int i = 0; i < st.stackSize - 1; i++)
            {
                out << st.s[i] << ", ";
            }
            out << st.s[st.stackSize - 1];
        }
        out << ']';
        return out;
    }
};

#ifndef CONTEST
int main()
{
    // let's play with integers...
    stack<int> s(10);
    cout << "s is empty: " << s << endl;
    s.push(42);
    cout << "s has one element: " << s << endl;
    s.push(17);
    s.push(34);
    cout << "s has more elements: " << s << endl;
    cout << "How many? " << s.size() << endl;
    stack<int> t(5);
    t.push(7);
    cout << "t: " << t << endl;
    t = s;
    cout << "popping from s: " << s.pop() << endl;

    s.push(8);
    stack<int> a(s);
    t.push(99);
    a.push(77);
    cout << "s: " << s << endl;
    cout << "t: " << t << endl;
    cout << "a: " << a << endl;
    // now with doubles...
    stack<double> c(4);
    c.push(3.14);
    c.push(1.414);
    cout << "c contains doubles " << c << endl;
    // and with characters...
    stack<char> k(4);
    k.push('$');
    cout << "k contains a character " << k << endl;
}
#endif
