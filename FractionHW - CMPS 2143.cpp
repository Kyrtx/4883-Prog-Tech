//Jesus Mendoza - CMPS 2143 - Proffesor Griffin - 9/5/2024
//Fractions and operators
//Add in subtraction and multiplication
#include <iostream>

using namespace std;

class Fraction {
    int num;
    int den;

    // private

public:
    // Griffin forgot to mention setters and getters.
    Fraction() { num = den = 1; }
    Fraction(int n, int d) {
        den = d;
        num = n;
    }
    void print() { cout << num << "/" << den << endl; }
    friend ostream& operator<<(ostream& os, const Fraction& rhs) {
        return os << rhs.num << "/" << rhs.den << endl;
    }
    Fraction operator+(const Fraction& rhs) {
        int commonDen = den * rhs.den;
        int numerator = num * rhs.den + rhs.num * den;
        return Fraction(numerator, commonDen);
    }
    Fraction operator-(const Fraction& rhs) {
        int commonDen = den * rhs.den;
        int numerator = num * rhs.den - rhs.num * den;
        return Fraction(numerator, commonDen);

    }
    Fraction operator*(const Fraction& rhs) {
        int numerator = num * rhs.num;
        int denominator = den * rhs.den;
        return Fraction(numerator, denominator);
    }
};

    int main() {
        Fraction F1(3, 8);
        Fraction F2(3, 4);
        F1.print();
        F2.print();

        cout << F1 << F2 << endl;

        F1 = F1 + F2;
        cout << "Testing F1 + F2: " << F1;

        Fraction F3;
        F3 = F1 - F2;
        cout << "Testing F1 - F2: " << F3;

        F2 = F3 * F1;
        cout << "Testing F3 * F1: " << F2;

        return 0;
    }