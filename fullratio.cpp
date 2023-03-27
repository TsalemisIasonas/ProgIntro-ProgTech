#include <iostream>
#ifndef CONTEST
#include "fullratio.hpp"
#endif

using namespace std;

rational::rational(int n, int d) {
    nom = n / gcd(n,d);
    den = d / gcd(n,d);
}

rational operator+(const rational &x, const rational &y) {
    int divider = rational::gcd((x.nom * y.den + y.nom * x.den),x.den * y.den);
    return rational((x.nom * y.den + y.nom * x.den)/divider, (x.den * y.den)/divider);
}

rational operator-(const rational &x, const rational &y) {
    int divider = rational::gcd((x.nom * y.den - y.nom * x.den),x.den * y.den);
    return rational((x.nom * y.den - y.nom * x.den)/divider, (x.den * y.den)/divider);
}

rational operator*(const rational &x, const rational &y) {
    int divider = rational::gcd(x.nom*y.nom,x.den*y.den);
    return rational((x.nom*y.nom)/divider,(x.den*y.den)/divider);
}

rational operator/(const rational &x, const rational &y) {
    int divider = rational::gcd(x.nom*y.den,x.den*y.nom);
    return rational((x.nom*y.den)/divider,(x.den*y.nom)/divider);
}

std::ostream & operator<<(std::ostream &out, const rational &x) {
    if ((x.nom>0 && x.den<0) || (x.nom<0 && x.den>0)){
        out << '-' << abs(x.nom) << "/" << abs(x.den);
    }
    else out <<abs(x.nom) << '/' << abs(x.den);
    return out;
}



int rational::gcd(int a, int b){
    a = abs(a);
    b = abs(b);
    while (a > 0 && b > 0){
        if (a > b)
            a = a % b;
        else
            b = b % a;
    }
    return a + b;
}
