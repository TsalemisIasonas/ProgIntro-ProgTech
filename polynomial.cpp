#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class Polynomial
{
protected:
    class Term
    {
    protected:
        int exponent;
        int coefficient;
        Term *next;
        Term(int exp, int coeff, Term *n) : exponent(exp), coefficient(coeff), next(n) {}
        friend class Polynomial;
        friend Polynomial operator+(const Polynomial &p, const Polynomial &q);
        friend Polynomial operator*(const Polynomial &p, const Polynomial &q);

        friend ostream &operator<<(ostream &out, const Polynomial &p);
    };
    Term *head;

    void insertEnd(int coeff, int exp)
    {
        if (head == nullptr)
        {
            head = new Term(exp, coeff, nullptr);
            return;
        }
        Term *temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = new Term(exp, coeff, nullptr);
    }
    void destroy()
    {
        Term *current = head;
        Term *next;
        while (current != nullptr)
        {
            next = current->next;
            delete current;
            current = next;
        }
    }

public:
    Polynomial()
    {
        head = nullptr;
    }
    Polynomial(const Polynomial &p)
    {
        head = nullptr;
        for (Term *i = p.head; i != nullptr; i = i->next)
        {
            insertEnd(i->coefficient, i->exponent);
        }
    }
    ~Polynomial()
    {
        destroy();
    }

    Polynomial &operator=(const Polynomial &p)
    {
        if (this != &p)
        {
            destroy();
            new (this) Polynomial(p);
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

    double evaluate(double x)
    {
        double result = 0;
        Term *temp = head;
        while (temp != nullptr)
        {
            result += (temp->coefficient) * pow(x, temp->exponent);
            temp = temp->next;
        }
        return result;
    }



    friend Polynomial operator + (const Polynomial &p, const Polynomial &q) {
        Polynomial result;
        Term *pterm, *qterm, *resterm;

        pterm = p.head;
        qterm = q.head;

        while(pterm != nullptr && qterm != nullptr) {
            if(pterm->exponent > qterm->exponent) {
                result.addTerm(pterm->exponent, pterm->coefficient);
                pterm = pterm->next;
            }
            else if(qterm->exponent > pterm->exponent) {
                result.addTerm(qterm->exponent,qterm->coefficient);
                qterm = qterm->next;
            }
            else {
                result.addTerm(pterm->exponent, pterm->coefficient + qterm->coefficient);
                pterm = pterm->next; 
                qterm = qterm->next;
            }
        }

        if(pterm == nullptr) {
            resterm = qterm;
        }
        else if(qterm == nullptr) {
            resterm = qterm;
        }

        while(resterm != nullptr){
            result.addTerm(resterm->exponent, resterm->coefficient);
            resterm = resterm->next;
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

    friend ostream &operator<<(ostream &out, const Polynomial &p)
    {
        string result;
        for (Term *i = p.head; i != nullptr; i = i->next)
        {
            if (i->coefficient < 0)
            {
                result += " - ";
            }
            else if (i != p.head)
            {
                result += " + ";
            }

            int abs_coeff = abs(i->coefficient);
            if (abs_coeff == 1 && i->exponent != 0)
            {
                result += "x";
            }
            else
            {
                result += to_string(abs_coeff);
                if (i->exponent != 0)
                {
                    result += "x";
                }
            }

            if (i->exponent > 1)
            {
                result += "^" + to_string(i->exponent);
            }
            else if (i->exponent == 1)
            {
                result += "";
            }
        }
        out << result;
        return out;
    }
};

// int main()
// {
//     Polynomial p;    // 0
//     p.addTerm(1, 3); // 3x

//     p.addTerm(2, 1);  // x^2
//     p.addTerm(0, -1); // -1

//     Polynomial q(p);  // x^2 + 3x - 1
//     q.addTerm(1, -3); // -3x

//     cout << "P(x) = " << p << endl;
//     cout << "P(1) = " << p.evaluate(1) << endl;
//     cout << "Q(x) = " << q << endl;
//     cout << "Q(1) = " << q.evaluate(1) << endl;
//     cout << "(P + Q)(x) = " << p + q << endl;
//     cout << "(P * Q)(x) = " << p * q << endl;
// }