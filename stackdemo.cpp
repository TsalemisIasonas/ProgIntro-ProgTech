#include <iostream>

using namespace std;

template <typename T>
class stack{
public:
    stack(int size){
        this->stackSize = 0;
        this->requestedSize = size;
        this->s = new T[requestedSize];
    } 
    stack(const stack &s) {
        this->stackSize = s.stackSize;
        this->requestedSize = s.requestedSize;
        this->s = new T[requestedSize];
        for (int i=0; i<requestedSize; i++){
            this->s[i] = s.s[i];
            stackSize++;
        }
    }
    ~stack() {}

    bool empty() {
        if (stackSize==0) return false;
        return true;
    }
    void push(const T &x){
        int index = requestedSize-stackSize;
        s[index] = x;
        stackSize++;
    } 
    // T pop() {}
    int size() {
        return stackSize;
    }

    friend ostream &operator<<(ostream &out, const stack &s) {
        for (int i=0; i<s.stackSize; i++){
            out << s.s[i];
        }
        return out;
    }

private:
    int stackSize;
    int requestedSize;
    T* s;
};

#ifndef CONTEST
 int main () {
 // let’s play with integers...
 stack<int> s(10);
 cout << "s is empty: " << s << endl;
 s.push(42);
 cout << "s has one element: " << s << endl;
//  s.push(17);
//  s.push(34);
//  cout << "s has more elements: " << s << endl;
 cout << "How many? " << s.size() << endl;
//  stack<int> t(5);
//  t.push(7);
//  cout << "t: " << t << endl;
//  t = s;
// cout << "popping from s: " << s.pop() << endl;

//  s.push(8);
//  stack<int> a(s);
//  t.push(99);
//  a.push(77);
//  cout << "s: " << s << endl;
//  cout << "t: " << t << endl;
//  cout << "a: " << a << endl;
//  // now with doubles...
//  stack<double> c(4);
//  c.push(3.14);
//  c.push(1.414);
//  cout << "c contains doubles " << c << endl;
//  // and with characters...
//  stack<char> k(4);
//  k.push('$');
//  cout << "k contains a character " << k << endl;
 }
#endif
