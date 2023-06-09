#include <iostream>

using namespace std;

template <typename T>
class stack {
public:
    stack(int size) {
        stackSize = size;
        myStack = new T[stackSize];
        topElement = -1;
    }

    stack(const stack &s) {
        stackSize = s.stackSize;
        myStack = new T[stackSize];
        topElement = s.topElement;
        for (int i = 0; i <= topElement; i++) {
            myStack[i] = s.myStack[i];
        }
    }

    ~stack() {
        delete[] myStack;
    }

    const stack &operator=(const stack &s) {
        if (this != &s) {
            delete[] myStack;
            stackSize = s.stackSize;
            myStack = new T[stackSize];
            topElement = s.topElement;
            for (int i = 0; i <= topElement; i++) {
                myStack[i] = s.myStack[i];
            }
        }
        return *this;
    }

    bool empty()const{
        return topElement == -1;
    }

    void push(const T &x) {
        myStack[++topElement] = x;
    }

    T pop() {
        return myStack[topElement--];
    }

    int size() {
        return topElement + 1;
    }

    friend ostream &operator<<(ostream &out, const stack &s) {
        out << "[";
        if (!s.empty()) {
            out << s.myStack[0];
            for (int i = 1; i <= s.topElement; i++) {
                out << ", " << s.myStack[i];
            }
        }
        out << "]";
        return out;
    }


private:
    T *myStack;
    int stackSize;
    int topElement;
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
