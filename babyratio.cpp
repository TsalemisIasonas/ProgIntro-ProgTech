#ifndef CONTEST
#include "babyratio.hpp"
#endif
#include <iostream>

using namespace std;

rational::rational(int n, int d) {
    nom = n;
    den = d;
}

int rational::gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a%b);
}

rational rational::add(rational r) {
    int newNom = nom * r.den + r.nom * den;
    int newDen = den * r.den;
    int factor = gcd(newNom, newDen);
    return rational(newNom/factor, newDen/factor);
}

rational rational::sub(rational r) {
    int newNom = nom * r.den - r.nom * den;
    int newDen = den * r.den;
    int factor = gcd(newNom, newDen);
    return rational(newNom/factor, newDen/factor);
}

rational rational::mul(rational r) {
    int newNom = nom * r.nom;
    int newDen = den * r.den;
    int factor = gcd(newNom, newDen);
    return rational(newNom/factor, newDen/factor);
}

rational rational::div(rational r) {
    int newNom = nom * r.den;
    int newDen = den * r.nom;
    int factor = gcd(newNom, newDen);
    return rational(newNom/factor, newDen/factor);
}

void rational::print() {
    cout << nom << "/" << den;
}
