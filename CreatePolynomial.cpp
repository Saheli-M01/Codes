//Polynomial from factors
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to multiply two polynomials
vector<int> multiplyPolynomials(const vector<int>& poly1, const vector<int>& poly2) {
    vector<int> result(poly1.size() + poly2.size() - 1, 0);

    // Multiply each term of poly1 with each term of poly2
    for (size_t i = 0; i < poly1.size(); ++i) {
        for (size_t j = 0; j < poly2.size(); ++j) {
            result[i + j] += poly1[i] * poly2[j];
        }
    }
    return result;
}

// Function to create polynomial from factors
vector<int> createPolynomial(const vector<pair<int, int>>& factors) {
    vector<int> polynomial = {1}; // Start with 1 as the polynomial

    for (const auto& factor : factors) {
        int a = factor.first;
        int b = factor.second;

        // Create a polynomial for each factor (ax + b)
        vector<int> currentFactor = {b, a}; // Represents b + ax
        polynomial = multiplyPolynomials(polynomial, currentFactor);
    }
    return polynomial;
}

// Function to display polynomial in the form ax^n + bx^(n-1) + ... + constant
void displayPolynomial(const vector<int>& polynomial) {
    int degree = polynomial.size() - 1;

    for (int i = degree; i >= 0; --i) {
        int coef = polynomial[degree - i];
        if (coef == 0) continue;

        // Print coefficient
        if (i < degree && coef > 0) cout << " + ";
        if (i < degree && coef < 0) cout << " - ";
        if (i == degree && coef < 0) cout << "-";

        // Print absolute value of coefficient if it's not 1 or -1, or if it's the constant term
        if (abs(coef) != 1 || i == 0) cout << abs(coef);

        // Print variable and exponent
        if (i > 0) cout << "x";
        if (i > 1) cout << "^" << i;
    }
    cout << endl;
}

int main() {
    int numFactors;
    cout << "Enter the number of factors: ";
    cin >> numFactors;

    vector<pair<int, int>> factors(numFactors);
    cout << "Enter each factor in the form (ax + b), input a and b:" << endl;

    for (int i = 0; i < numFactors; ++i) {
        int a, b;
        cout << "Factor " << i + 1 << ": ";
        cin >> a >> b;
        factors[i] = make_pair(a, b);
    }

    vector<int> polynomial = createPolynomial(factors);
    cout << "The expanded polynomial is: ";
    displayPolynomial(polynomial);

    return 0;
}
