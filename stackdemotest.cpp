#include <iostream>

using namespace std;

template <typename T>
class stack {
public:
    stack(int size) {
        this->max_size = size;
        this->data = new T[max_size];
        this->top_index = -1;
    }

    stack(const stack &s) {
        this->max_size = s.max_size;
        this->data = new T[max_size];
        this->top_index = s.top_index;
        for (int i = 0; i <= top_index; i++) {
            this->data[i] = s.data[i];
        }
    }

    ~stack() {
        delete[] data;
    }

    const stack &operator=(const stack &s) {
        if (this != &s) {
            delete[] this->data;
            this->max_size = s.max_size;
            this->data = new T[max_size];
            this->top_index = s.top_index;
            for (int i = 0; i <= top_index; i++) {
                this->data[i] = s.data[i];
            }
        }
        return *this;
    }

    bool empty() {
        return top_index == -1;
    }

    void push(const T &x) {
        data[++top_index] = x;
    }

    T pop() {
        return data[top_index--];
    }

    int size() {
        return top_index + 1;
    }

friend ostream& operator<<(ostream& out, const stack& s) {
    out << "[";
    if (!s.empty()) {
        out << s.data[0];
        for (int i = 1; i <= s.top_index; i++) {
            out << ", " << s.data[i];
        }
    }
    out << "]";
    return out;
}


private:
    T *data;
    int max_size;
    int top_index;
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
