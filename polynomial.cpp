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
        Term(int exp, int coeff, Term *n);
        friend class Polynomial;
    };

public:
    Polynomial();
    Polynomial(const Polynomial &p);
    ~Polynomial();

    Polynomial &operator=(const Polynomial &p);

        void addTerm(int expon, int coeff);
        double evaluate(double x);

        friend Polynomial operator+(const Polynomial &p, const Polynomial &q);
        friend Polynomial operator*(const Polynomial &p, const Polynomial &q);

        friend ostream &operator<<(ostream &out, const Polynomial &p);
    };


