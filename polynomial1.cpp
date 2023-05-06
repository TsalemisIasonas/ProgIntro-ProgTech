#include <iostream>
#include <cmath>

using namespace std;

class Polynomial {
protected:
    class Term {
    protected:
        int exponent;
        int coefficient;
        Term *next;
        
        Term(int e, int c, Term *n) {
            exponent = e;
            coefficient = c;
            next = n;
        }
        
        friend class Polynomial;
        friend Polynomial operator + (const Polynomial &p, const Polynomial &q);
        friend Polynomial operator * (const Polynomial &p, const Polynomial &q);
        friend ostream & operator << (ostream &out, const Polynomial &p);
    };
    
    Term *head;

    void destroy() {
        Term *p = head;
        while(p != nullptr) {
            Term *q = p;
            p = p->next;
            delete q;
        } 
    }
    
    void InsertEnd(const int &e, const int &c) {
        Term *n = new Term(e, c, nullptr);
        Term *p;

        if(head == nullptr) {
            head = n;
            return;
        } 
        
        p = head;
        while(p->next != nullptr) {
             p = p->next;
        }
        p->next = n;
    }

public:
    Polynomial() {
        head = nullptr;
    }
    
    Polynomial(const Polynomial &p) {
        head = nullptr;
        for(Term *i = p.head; i != nullptr; i = i->next) {
            InsertEnd(i->exponent, i->coefficient);
        }
    }
    
    ~Polynomial() {
        destroy();
    };

    Polynomial & operator = (const Polynomial &p) {
        destroy();
        head = nullptr;
        for(Term *i = p.head; i != nullptr; i = i->next) {
            InsertEnd(i->exponent, i->coefficient);
        }
        return *this;
    }

    void addTerm(int e, int c) {
        Term *n = new Term(e, c, nullptr);
        Term *p, *q;

        if(c == 0) {
            delete n;
            return;
        }

        if(head == nullptr) {
            head = n;
            head->next = nullptr;
            return;
        }

        if(head->exponent == e) {
            head->coefficient += c;
            if(head->coefficient == 0) {
                p = head;
                head = head->next;
                delete p;
            }
            delete n;
            return;
        }

        p = head;
        q = p->next;
        while(q != nullptr && q->exponent > e) {
            p = q;
            q = q->next; 
        }
        if(q != nullptr && q->exponent == e) {
            q->coefficient += c;
            if(q->coefficient == 0) {
                p->next = q->next;
                delete q;
            }
            delete n;
        } else {
            if(n->exponent < p->exponent) {
                n->next = p->next;
                p->next = n;
            } else {
                n->next = p;
                head = n;
            }
        }
    }
    double evaluate(double x) {
        double result = 0;
        Term *p = head;
        while(p != nullptr) {
            result += (double) p->coefficient * pow(x, p->exponent);
            p = p->next;
        }
        return result;
    }

    friend Polynomial operator + (const Polynomial &p, const Polynomial &q) {
        Polynomial result;
        Term *i, *j, *k;

        i = p.head;
        j = q.head;

        while(i != nullptr && j != nullptr) {
            if(i->exponent > j->exponent) {
                result.addTerm(i->exponent, i->coefficient);
                i = i->next;
            }
            else if(j->exponent > i->exponent) {
                result.addTerm(j->exponent,j->coefficient);
                j = j->next;
            }
            else {
                result.addTerm(i->exponent, i->coefficient + j->coefficient);
                i = i->next; 
                j = j->next;
            }
        }

        if(i == nullptr) {
            k = j;
        }
        else if(j == nullptr) {
            k = i;
        }

        while(k != nullptr){
            result.addTerm(k->exponent, k->coefficient);
            k = k->next;
        }
        return result;
    }
    friend Polynomial operator * (const Polynomial &p, const Polynomial &q) {
        Polynomial result;

        for(Term *i = p.head; i != nullptr; i = i->next) {
            for(Term *j = q.head; j != nullptr; j = j->next) {
                result.addTerm(i->exponent + j->exponent, i->coefficient * j-> coefficient);
            }
        }
        return result;
    }

    friend ostream & operator << (ostream &out, const Polynomial &p) {
        Term *n = p.head;

        if(n == nullptr) {
            out << "0";
            return out;
        }

        if(n->coefficient < 0) 
            out << "- ";
        if(abs(n->coefficient) != 1) 
            out << abs(n->coefficient);
        if(n->exponent == 0 && abs(n->coefficient) == 1) 
            out << "1";
        if(n->exponent == 1) 
            out << "x";
        else if(n->exponent != 0) 
            out << "x^" << n->exponent;
        n = n->next;
        while(n != nullptr) {
            if(n->coefficient < 0) {
                out << " - ";
            }
            else {
                out << " + ";
            }
            if(abs(n->coefficient) != 1 || n->exponent == 0) {
                out << abs(n->coefficient);
            }
            if(n->exponent == 1) {
                out << "x";
            }
            else if(n->exponent != 0) {
                out << "x^" << n->exponent;
            }
            n = n->next;
        }

        return out;
    }
};


