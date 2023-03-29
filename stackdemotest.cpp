#include <iostream>

using namespace std;

template <typename T>
class stack {
public:
    stack(int size) {
        this->size = 0;
        this->capacity = size;
        this->arr = new T[capacity];
    }

    stack(const stack &s) {
        this->size = s.size;
        this->capacity = s.capacity;
        this->arr = new T[capacity];
        for (int i = 0; i < size; i++) {
            arr[i] = s.arr[i];
        }
    }

    ~stack() {
        delete [] arr;
    }

    const stack &operator=(const stack &s) {
        if (this != &s) {
            delete [] arr;
            this->size = s.size;
            this->capacity = s.capacity;
            this->arr = new T[capacity];
            for (int i = 0; i < size; i++) {
                arr[i] = s.arr[i];
            }
        }
        return *this;
    }

    bool empty() {
        return size == 0;
    }

    void push(const T &x) {
        if (size == capacity) {
            T *new_arr = new T[2*capacity];
            for (int i = 0; i < size; i++) {
                new_arr[i] = arr[i];
            }
            delete [] arr;
            arr = new_arr;
            capacity *= 2;
        }
        arr[size] = x;
        size++;
    }

    T pop() {
        if (size == 0) {
            throw "Stack is empty";
        }
        else {
            size--;
            return arr[size];
        }
    }

    int size() {
        return size;
    }

    friend ostream &operator<<(ostream &out, const stack &s) {
        for (int i = s.size-1; i >= 0; i--) {
            out << s.arr[i] << " ";
        }
        return out;
    }

private:
    T *arr;
    int size;
    int capacity;
};

#ifndef CONTEST
int main() {
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
