#ifndef COMPLEX_H_INCLUDED
#define COMPLEX_H_INCLUDED
#include <iostream>
#include <math.h>
#include <string.h>
using namespace std ;
//feel free to edit this value the way you want
const float tolerance = 0.00001 ;
const float to_deg =180/M_PI;
const float to_rad = M_PI/180 ;
class complex{
private:
    float re,im ;
public:
    complex(float _re=0,float _im=0);
    complex(const complex&);
    float get_re(void)const;
    float get_im(void)const;
    ~complex();
    complex operator+(const complex&)const ;
    complex operator-(const complex&)const ;
    complex operator*(const complex&)const ;
    complex operator/(const complex&)const ;
    void operator=(const float& val);

    void operator+=(const complex&) ;
    void operator-=(const complex&) ;
    void operator*=(const complex&) ;
    void operator/=(const complex&) ;
    void operator^=(const float&power);
    complex operator*(const float&)const ;
    complex operator/(const float&)const ;
    void operator*=(const float&) ;
    void operator/=(const float&) ;
    complex operator^(const float&) const ;
    float theta(void)const;
    bool operator>(const complex&)const;
    bool operator<(const complex&)const;
    bool operator==(const complex&)const;
    void operator=(const complex&) ;
    bool operator!=(const complex&)const;
    friend std::ostream& operator<<(std::ostream& os, const complex& c);

};
    string to_string(complex&);
    float abs(const complex&);
    // General template function for all non-complex types
    complex conjugate(const complex& val);
    unsigned char conjugate(const unsigned char &val);
    char conjugate(const char &val);
    unsigned int conjugate(const unsigned int &val);
    int conjugate(const int &val);

    float conjugate(const float &val);
     double conjugate(const double &val);
    unsigned long conjugate(const unsigned long &val);
    long conjugate(const long &val);
    long long conjugate(const long long &val);
    unsigned long long conjugate(const unsigned long long &val);
    long double conjugate(const long double&val);
    // Template specialization for your complex type

#endif
