//Jesus Mendoza - Proffessor Griffin - Object Oriented Programming
// Fraction Class Program
//Program 1
#include <iostream>
#include <stdexcept>

using namespace std;

class Fraction {
private:
    int numerator;
    int denominator;

    // Helper function to reduce the fraction
    void reduce() {
        int gcd_val = gcd(numerator, denominator);
        numerator /= gcd_val;
        denominator /= gcd_val;
        // Ensure the denominator is positive
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    // Constructor
    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) {
        if (den == 0) {
            throw invalid_argument("Denominator cannot be zero.");
        }
        reduce(); // Simplify the fraction
    }

    // Overloaded addition operator
    Fraction operator+(const Fraction& other) const;

    // Overloaded subtraction operator
    Fraction operator-(const Fraction& other) const;

    // Overloaded multiplication operator
    Fraction operator*(const Fraction& other) const;

    // Overloaded division operator
    Fraction operator/(const Fraction& other) const;

    // Overloaded equality operator
    bool operator==(const Fraction& other) const;

    // Overload output operator for printing fractions
    friend ostream& operator<<(ostream& os, const Fraction& frac);

    // Static function to calculate the GCD
    static int gcd(int a, int b);

    // Static function to calculate the LCM
    static int lcm(int a, int b);

    // Static function to calculate the LCD
    static int lcd(int a, int b);
};

// Custom GCD function using the Euclidean algorithm
int Fraction::gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// LCM function
int Fraction::lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

// LCD function (same as LCM for fractions)
int Fraction::lcd(int a, int b) {
    return lcm(a, b);
}

// Addition of two fractions
Fraction Fraction::operator+(const Fraction& other) const {
    int common_denominator = lcd(denominator, other.denominator);
    int new_numerator = (numerator * (common_denominator / denominator)) +
                        (other.numerator * (common_denominator / other.denominator));
    return Fraction(new_numerator, common_denominator);
}

// Subtraction of two fractions
Fraction Fraction::operator-(const Fraction& other) const {
    int common_denominator = lcd(denominator, other.denominator);
    int new_numerator = (numerator * (common_denominator / denominator)) -
                        (other.numerator * (common_denominator / other.denominator));
    return Fraction(new_numerator, common_denominator);
}

// Multiplication of two fractions
Fraction Fraction::operator*(const Fraction& other) const {
    return Fraction(numerator * other.numerator, denominator * other.denominator);
}

// Division of two fractions
Fraction Fraction::operator/(const Fraction& other) const {
    if (other.numerator == 0) {
        throw invalid_argument("Cannot divide by zero.");
    }
    return Fraction(numerator * other.denominator, denominator * other.numerator);
}

// Equality check
bool Fraction::operator==(const Fraction& other) const {
    return (numerator == other.numerator && denominator == other.denominator);
}

// Output operator for fractions
ostream& operator<<(ostream& os, const Fraction& frac) {
    os << frac.numerator << "/" << frac.denominator;
    return os;
}

// Main function for testing
int main() {
    // Create some fractions
    Fraction frac1(1, 2);
    Fraction frac2(3, 4);

    // Perform operations
    Fraction sum = frac1 + frac2;
    Fraction diff = frac1 - frac2;
    Fraction prod = frac1 * frac2;
    Fraction quot = frac1 / frac2;

    // Print results
    cout << "Sum: " << sum << endl;
    cout << "Difference: " << diff << endl;
    cout << "Product: " << prod << endl;
    cout << "Quotient: " << quot << endl;

    // Test equality operator
    Fraction frac3(2, 4);
    if (frac1 == frac3) {
        cout << frac1 << " is equal to " << frac3 << endl;
    } else {
        cout << frac1 << " is not equal to " << frac3 << endl;
    }

    return 0;
}
