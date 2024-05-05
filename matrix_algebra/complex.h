#ifndef COMPLEX_H_INCLUDED
#define COMPLEX_H_INCLUDED
#include <iostream>
#include <math.h>
#include <string.h>
//tolerance is used in calculations like inverse and gram-shmidt ,gauss
//this is sufficient for gram-shmidt since it requires a percision
const long double tolerance =1e-18;
//check_tolerance is for is_identity , is_zero , aka every function starting with is_
//modify this the way you want
const long double check_tolerance =1e-6;

using namespace std ;
const long double to_deg =180/M_PI;
const long double to_rad = M_PI/180 ;
class complex{
private:
    long double re,im ;
public:
    complex(long double _re=0,long double _im=0);
    complex(int);

    complex(const complex&);
    long double get_re(void)const;
    long double get_im(void)const;
    ~complex();
    complex operator+(const complex&)const ;
    complex operator-(const complex&)const ;
    complex operator*(const complex&)const ;
    complex operator/(const complex&)const ;
    void operator=(const long double & val);

    void operator+=(const complex&) ;
    void operator-=(const complex&) ;
    void operator*=(const complex&) ;
    void operator/=(const complex&) ;
    void operator^=(const long double &power);
    complex operator*(const long double &)const ;
    complex operator/(const long double &)const ;
    void operator*=(const long double &) ;
    void operator/=(const long double &) ;
    complex operator^(const long double &) const ;
    long double theta(void)const;
    bool operator>(const complex&)const;
    bool operator<(const complex&)const;
    bool operator==(const complex&)const;
    void operator=(const complex&) ;
    bool operator!=(const complex&)const;
    friend std::ostream& operator<<(std::ostream& os, const complex& c);

};
    string to_string(complex&);
    long double abs(const complex&);
    // General template function for all non-complex types
    complex conjugate(const complex& val);
    unsigned char conjugate(const unsigned char &val);
    char conjugate(const char &val);
    unsigned int conjugate(const unsigned int &val);
    int conjugate(const int &val);

    float conjugate(const float &val);
    double conjugate(const double &val);

    long double conjugate(const long double &val);
    unsigned long conjugate(const unsigned long &val);
    long conjugate(const long &val);
    long long conjugate(const long long &val);
    unsigned long long conjugate(const unsigned long long &val);
    complex pow(const complex &c,int power);
    // Template specialization for your complex type

#endif
