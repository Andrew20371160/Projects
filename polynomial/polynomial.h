#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include "node.h"

using namespace std;

// Head points to the largest exponent node.
class Polynomial
{
private:
    Node* head;
public:
    // Constructor.
    Polynomial(Node* h = NULL);
    // Copy constructor
    Polynomial(const Polynomial& p);
    // Destructor
    ~Polynomial();
    // Print polynomial
    void print() const;
    void del_poly(void);
    void operator= (const Polynomial&) ;

    // #1 [i-ii-iii]
    void add_term(const double& c, const int& e);
    // #2
    Polynomial p_copy() const; // Returns a copy
    // #3
    void remove_term(const int& e);
    // #4
    double poly_val(const double& x) const;
    // #5
    Polynomial mul_term(const double& c,const int& e) const;
    // #6 [i-ii]
    bool operator ==(const Polynomial& p) const;
    // #7 [i-ii]
    bool operator !=(const Polynomial& p) const;
    // #8
    Polynomial operator + (const Polynomial& p) const;
    // #9 [i-ii]
    Polynomial operator - (const Polynomial& p) const;
    // #10
    Polynomial operator * (const Polynomial& p) const; // complexity O(n^2)?
    // #11 [i-ii]
    Polynomial operator / (const Polynomial& divisor) const;
    // #12 [i-ii]
    Polynomial operator % (const Polynomial& divisor) const;
    // #13
    Polynomial integrate () const;
    // #14
    Polynomial differentiate () const;
};

#endif // POLYNOMIAL_H
