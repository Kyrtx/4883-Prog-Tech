/*****************************************************************************
*
*  Author:           Jesus Mendoza
*  Email:            jesus.kyx.mendoza11@gmail.com
*  Label:            Program 1 - Fraction Class
*  Title:            Create a Fraction Class with Operator Overloading
*  Course:           CMPS 2143 
*  Semester:         Fall 2024
*
*  Description:
*        This program implements a fraction class that supports arithmetic
*        operations (addition, subtraction, multiplication, division) and 
*        comparison (equality). The operations are performed by overloading
*        the appropriate operators to allow intuitive usage with fraction 
*        objects. Additionally, the class simplifies fractions and ensures 
*        they are kept in their lowest terms.
*
*  Usage:
*        - The program can be used to perform arithmetic operations between
*          two fractions and display the results.
*        - Compile and run the program to test different fraction operations.
*
*  Files:            
*        FractionHW - CMPS 2143.cpp
*
*****************************************************************************/

#include <iostream>

using namespace std;

/**
 * Class Fraction
 *
 * Description:
 *      This class represents a fraction with a numerator and denominator.
 *      It supports basic arithmetic operations such as addition, subtraction,
 *      multiplication, and division, and also provides a way to compare two
 *      fractions for equality. The class ensures the fraction is always stored
 *      in its reduced form.
 *
 * Public Methods:
 *      - Fraction(int num, int den)
 *      - Fraction operator+(const Fraction& other) const
 *      - Fraction operator-(const Fraction& other) const
 *      - Fraction operator*(const Fraction& other) const
 *      - Fraction operator/(const Fraction& other) const
 *      - bool operator==(const Fraction& other) const
 *      - friend ostream& operator<<(ostream& os, const Fraction& frac)
 *      - static int gcd(int a, int b)
 *      - static int lcm(int a, int b)
 *      - static int lcd(int a, int b)
 *
 * Private Methods:
 *      - void reduce()
 */
class Fraction {
private:
    int numerator;   // numerator of the fraction
    int denominator; // denominator of the fraction

    /**
     * reduce
     *
     * Description:
     *      Reduces the fraction to its lowest terms using the GCD.
     *      Ensures the denominator is always positive.
     */
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
    /**
     * Fraction (Constructor)
     *
     * Description:
     *      Constructs a fraction with a given numerator and denominator.
     *      If the denominator is zero, it defaults to 1 to avoid division by zero.
     */
    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) {
        if (den == 0) {
            cout << "Error: Denominator cannot be zero." << endl;
            denominator = 1;  // Set a default valid denominator
        }
        reduce(); // Simplify the fraction
    }

    /**
     * operator+
     *
     * Description:
     *      Overloads the addition operator to add two fractions.
     *
     * Returns:
     *      Fraction - the resulting fraction after addition
     */
    Fraction operator+(const Fraction& other) const;

    /**
     * operator-
     *
     * Description:
     *      Overloads the subtraction operator to subtract two fractions.
     *
     * Returns:
     *      Fraction - the resulting fraction after subtraction
     */
    Fraction operator-(const Fraction& other) const;

    /**
     * operator*
     *
     * Description:
     *      Overloads the multiplication operator to multiply two fractions.
     *
     * Returns:
     *      Fraction - the resulting fraction after multiplication
     */
    Fraction operator*(const Fraction& other) const;

    /**
     * operator/
     *
     * Description:
     *      Overloads the division operator to divide two fractions.
     *
     * Returns:
     *      Fraction - the resulting fraction after division
     *
     * Throws:
     *      invalid_argument - if division by zero is attempted
     */
    Fraction operator/(const Fraction& other) const;

    /**
     * operator==
     *
     * Description:
     *      Overloads the equality operator to compare two fractions.
     *
     * Returns:
     *      bool - true if the fractions are equal, false otherwise
     */
    bool operator==(const Fraction& other) const;

    /**
     * operator<<
     *
     * Description:
     *      Overloads the output stream operator to print a fraction.
     */
    friend ostream& operator<<(ostream& os, const Fraction& frac);

    /**
     * gcd
     *
     * Description:
     *      Calculates the greatest common divisor (GCD) of two integers
     *      using the Euclidean algorithm.
     */
    static int gcd(int a, int b);

    /**
     * lcm
     *
     * Description:
     *      Calculates the least common multiple (LCM) of two integers.
     */
    static int lcm(int a, int b);

    /**
     * lcd
     *
     * Description:
     *      Calculates the least common denominator (LCD) of two fractions,
     *      which is the same as the LCM of their denominators.
     */
    static int lcd(int a, int b);
};

// Implementation of GCD, LCM, and other methods

int Fraction::gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int Fraction::lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int Fraction::lcd(int a, int b) {
    return lcm(a, b);
}

Fraction Fraction::operator+(const Fraction& other) const {
    int common_denominator = lcd(denominator, other.denominator);
    int new_numerator = (numerator * (common_denominator / denominator)) +
                        (other.numerator * (common_denominator / other.denominator));
    return Fraction(new_numerator, common_denominator);
}

Fraction Fraction::operator-(const Fraction& other) const {
    int common_denominator = lcd(denominator, other.denominator);
    int new_numerator = (numerator * (common_denominator / denominator)) -
                        (other.numerator * (common_denominator / other.denominator));
    return Fraction(new_numerator, common_denominator);
}

Fraction Fraction::operator*(const Fraction& other) const {
    return Fraction(numerator * other.numerator, denominator * other.denominator);
}

Fraction Fraction::operator/(const Fraction& other) const {
    if (other.numerator == 0) {
        throw invalid_argument("Cannot divide by zero.");
    }
    return Fraction(numerator * other.denominator, denominator * other.numerator);
}

bool Fraction::operator==(const Fraction& other) const {
    return (numerator == other.numerator && denominator == other.denominator);
}

ostream& operator<<(ostream& os, const Fraction& frac) {
    os << frac.numerator << "/" << frac.denominator;
    return os;
}

// Main function for testing
int main() {
    Fraction frac1(1, 2);      // Fraction 1/2
    Fraction frac2(3, 4);      // Fraction 3/4

    Fraction sum = frac1 + frac2;     // Add fractions
    Fraction diff = frac1 - frac2;    // Subtract fractions
    Fraction prod = frac1 * frac2;    // Multiply fractions
    Fraction quot = frac1 / frac2;    // Divide fractions

    cout << "Sum: " << sum << endl;
    cout << "Difference: " << diff << endl;
    cout << "Product: " << prod << endl;
    cout << "Quotient: " << quot << endl;

    Fraction frac3(2, 4);  // Fraction 2/4, equivalent to 1/2

    if (frac1 == frac3) {
        cout << frac1 << " is equal to " << frac3 << endl;
    } else {
        cout << frac1 << " is not equal to " << frac3 << endl;
    }

    return 0;
}
