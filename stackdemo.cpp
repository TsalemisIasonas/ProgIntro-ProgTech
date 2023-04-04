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
