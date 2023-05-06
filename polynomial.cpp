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

    void addTerm(int expon, int coeff)
    {
        Term *newTerm = new Term(expon, coeff, nullptr);

        if (head == nullptr)
        {
            head = newTerm;
            return;
        }

        if (expon > head->exponent)
        {
            newTerm->next = head;
            head = newTerm;
            return;
        }

        Term *current = head;
        while (current->next != nullptr && expon < current->next->exponent)
        {
            current = current->next;
        }

        newTerm->next = current->next;
        current->next = newTerm;
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

friend Polynomial operator+(const Polynomial& p, const Polynomial& q){
    Polynomial result;
    Term *pTerm = p.head;
    Term *qTerm = q.head;

    while (pTerm != nullptr && qTerm != nullptr)
    {
        int coeffSum = 0;
        int exp = 0;

        if (pTerm == nullptr)
        {
            coeffSum = qTerm->coefficient;
            exp = qTerm->exponent;
            qTerm = qTerm->next;
        }
        else if (qTerm == nullptr)
        {
            coeffSum = pTerm->coefficient;
            exp = pTerm->exponent;
            pTerm = pTerm->next;
        }
        else if (pTerm->exponent > qTerm->exponent)
        {
            result.addTerm(pTerm->exponent, pTerm->coefficient);
            pTerm = pTerm->next;
        }
        else if (pTerm->exponent < qTerm->exponent)
        {
            result.addTerm(qTerm->exponent, qTerm->coefficient);
            qTerm = qTerm->next;
        }
        else
        {
            coeffSum = pTerm->coefficient + qTerm->coefficient;
            exp = pTerm->exponent;
            if(coeffSum != 0)
                result.addTerm(exp,coeffSum);                
            pTerm = pTerm->next;
            qTerm = qTerm->next;
        }
    }

    return result;
}




friend Polynomial operator*(const Polynomial &p, const Polynomial &q){
    Polynomial product;

    for (Term *pTerm = p.head; pTerm != nullptr; pTerm = pTerm->next)
    {
        for (Term *qTerm = q.head; qTerm != nullptr; qTerm = qTerm->next)
        {
            double coeff = pTerm->coefficient * qTerm->coefficient;
            int exp = pTerm->exponent + qTerm->exponent;
            product.insertEnd(coeff, exp);
        }
    }

    return product;
}


friend ostream& operator<<(ostream& out, const Polynomial& p) {
    string result;
    for (Term* i = p.head; i != nullptr; i = i->next) {
        if (i->coefficient < 0) {
            result += " - ";
        } else if (i != p.head) {
            result += " + ";
        }
        
        int abs_coeff = abs(i->coefficient);
        if (abs_coeff == 1 && i->exponent != 0) {
            result += "x";
        } else {
            result += to_string(abs_coeff);
            if (i->exponent != 0) {
                result += "x";
            }
        }
        
        if (i->exponent > 1) {
            result += "^" + to_string(i->exponent);
        } else if (i->exponent == 1) {
            result += "";
        }
    }
    out << result;
    return out;
}

};








int main()
{
    Polynomial p;    // 0
    p.addTerm(1, 3); // 3x

    p.addTerm(2, 1); // x^2
    p.addTerm(0, -1); // -1

    Polynomial q(p);  // x^2 + 3x - 1
    q.addTerm(1, -3); // -3x

    cout << "P(x) = " << p << endl;
    cout << "P(1) = " << p.evaluate(1) << endl;
    cout << "Q(x) = " << q << endl;
    cout << "Q(1) = " << q.evaluate(1) << endl;
    cout << "(P + Q)(x) = " << p + q << endl;
    cout << "(P * Q)(x) = " << p * q << endl;
}