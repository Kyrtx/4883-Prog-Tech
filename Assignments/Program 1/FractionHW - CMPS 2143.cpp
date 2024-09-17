/*****************************************************************************
*
*  Author:           Jesus Mendoza
*  Email:            jesus.kyx.mendoza11@gmail.com
*  Label:            Program 1 - Fraction Class
*  Title:            Create a Proper Fraction Class
*  Course:           CMPS 2143 - Object-Oriented Programming
*  Semester:         Fall 2024
*
*  Description:
*        This program implements a fraction class that overloads the addition (+), 
*        subtraction (-), multiplication (*), division (/), and equality (==) operators.
*        It simplifies fractions upon creation and ensures that denominators are never 
*        zero by setting them to 1 if a zero is provided. The class also includes methods 
*        for calculating the greatest common divisor (GCD), least common multiple (LCM), 
*        and least common denominator (LCD) to help in fraction operations.
*
*  Usage:
*        The program creates instances of fractions and performs various operations 
*        like addition, subtraction, multiplication, division, and checks for equality 
*        between fractions. The results of these operations are in the output.
*
*  Files: 
*        FractionHW - CMPS 2143.cpp
*
*****************************************************************************/
#include <iostream>

using namespace std;

/**
 * Fraction Class
 *
 * Description:
 *      A class that models fractions with overloaded operators for arithmetic 
 *      and comparison. It includes methods for simplifying fractions, calculating 
 *      the GCD, and handling zero denominators.
 *
 * Public Methods:
 *      - Fraction(int num = 0, int den = 1)
 *      - Fraction operator+(const Fraction& other) const
 *      - Fraction operator-(const Fraction& other) const
 *      - Fraction operator*(const Fraction& other) const
 *      - Fraction operator/(const Fraction& other) const
 *      - bool operator==(const Fraction& other) const
 *      - friend ostream& operator<<(ostream& os, const Fraction& frac)
 * 
 * Private Methods:
 *      - void reduce()
 *      - static int gcd(int a, int b)
 *      - static int lcm(int a, int b)
 *      - static int lcd(int a, int b)
 * 
 * Usage:
 * 
 *      Fraction f1(1, 2);
 *      Fraction f2(3, 4);
 *      Fraction sum = f1 + f2;
 *      cout << "Sum: " << sum << endl;  // Outputs the sum of fractions.
 *
 */
class Fraction {
private:
    int numerator;   // Numerator of the fraction
    int denominator; // Denominator of the fraction

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
    /**
     * Public : Fraction
     * 
     * Description:
     *      Constructor that initializes a fraction with a numerator and denominator.
     *      If the denominator is zero, it outputs an error and sets it to 1.
     * 
     * Params:
     *      int : numerator (default = 0)
     *      int : denominator (default = 1)
     * 
     * Returns:
     *      None
     */
    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) {
        if (den == 0) {
            cout << "Error: Denominator cannot be zero." << endl;
            denominator = 1;  // Set a default valid denominator
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

/**
 * Function : gcd
 *
 * Description:
 *      Calculates the greatest common divisor (GCD) of two integers using
 *      the Euclidean algorithm.
 *
 * Params:
 *      int : first integer
 *      int : second integer
 * 
 * Returns:
 *      int : the GCD of the two integers
 */
int Fraction::gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/**
 * Function : lcm
 *
 * Description:
 *      Calculates the least common multiple (LCM) of two integers.
 *
 * Params:
 *      int : first integer
 *      int : second integer
 * 
 * Returns:
 *      int : the LCM of the two integers
 */
int Fraction::lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

/**
 * Function : lcd
 *
 * Description:
 *      Calculates the least common denominator (LCD) of two integers, 
 *      which is essentially the LCM for fractions.
 *
 * Params:
 *      int : first denominator
 *      int : second denominator
 * 
 * Returns:
 *      int : the LCD of the two denominators
 */
int Fraction::lcd(int a, int b) {
    return lcm(a, b);
}

/**
 * Function : operator+
 *
 * Description:
 *      Overloads the addition operator to add two fractions.
 *
 * Params:
 *      const Fraction& : the other fraction to add
 * 
 * Returns:
 *      Fraction : the resulting fraction after addition
 */
Fraction Fraction::operator+(const Fraction& other) const {
    int common_denominator = lcd(denominator, other.denominator);
    int new_numerator = (numerator * (common_denominator / denominator)) +
                        (other.numerator * (common_denominator / other.denominator));
    return Fraction(new_numerator, common_denominator);
}

// Similarly add comments for other operators like -, *, /, == and output (<<) operator

// Main function for testing
int main() {
    // Create some fractions
    Fraction frac1(1, 2);  // 1/2
    Fraction frac2(3, 4);  // 3/4

    // Perform operations
    Fraction sum = frac1 + frac2;     // Add fractions
    Fraction diff = frac1 - frac2;    // Subtract fractions
    Fraction prod = frac1 * frac2;    // Multiply fractions
    Fraction quot = frac1 / frac2;    // Divide fractions

    // Print results
    cout << "Sum: " << sum << endl;
    cout << "Difference: " << diff << endl;
    cout << "Product: " << prod << endl;
    cout << "Quotient: " << quot << endl;

    // Test equality operator or whatever
    Fraction frac3(2, 4);  // Equivalent to 1/2 after reduction
    if (frac1 == frac3) {
        cout << frac1 << " is equal to " << frac3 << endl;
    } else {
        cout << frac1 << " is not equal to " << frac3 << endl;
    }

    return 0;
}
