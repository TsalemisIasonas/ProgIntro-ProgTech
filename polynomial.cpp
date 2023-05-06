#include <iostream>
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
        Term(int exp, int coeff, Term *n):exponent(exp),coefficient(coeff),next(n){}
        friend class Polynomial;
        friend Polynomial operator+(const Polynomial &p, const Polynomial &q);
        friend Polynomial operator*(const Polynomial &p, const Polynomial &q);

        friend ostream &operator<<(ostream &out, const Polynomial &p);
    };
    Term *head;

    void insertEnd(int coeff, int exp){
    if (head==nullptr){
        head = new Term(exp, coeff, nullptr);
        return;
    }
    Term *temp = head;
    while(temp->next!=nullptr)
        temp=temp->next;
    temp->next = new Term(exp, coeff, nullptr);
}


public:
    Polynomial(){
        head = nullptr;
    }
    Polynomial(const Polynomial &p){
        head = nullptr;
        for (Term *i=p.head; i!=nullptr; i = i->next){
            insertEnd(i->coefficient, i->exponent);
        }
    }
    ~Polynomial();

    Polynomial &operator=(const Polynomial &p);

        void addTerm(int expon, int coeff);
        double evaluate(double x);

        friend Polynomial operator+(const Polynomial &p, const Polynomial &q);
        friend Polynomial operator*(const Polynomial &p, const Polynomial &q);

        friend ostream &operator<<(ostream &out, const Polynomial &p);
    };

int main()
    {
        Polynomial p;    // 0
        p.addTerm(1, 3); // 3x

        p.addTerm(2, 1);  // x^2
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