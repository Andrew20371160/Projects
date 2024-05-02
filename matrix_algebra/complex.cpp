#include "complex.h"

    complex::complex(double _re,double _im){
        re =_re ;
        im = _im   ;
    }
    complex::complex(const complex&src){
        re = src.re  ;
        im = src.im ;
    }
    complex::~complex(){
    }
    double complex::get_re(void)const{
        return re ;
    }
    double complex::get_im(void)const{
        return im ;
    }
    void complex:: operator=(const complex&src){
        re = src.re  ;
        im = src.im ;
    }
    complex complex:: operator+(const complex&c2)const{
        return complex(re+c2.re,im+c2.im) ;
    }
    complex complex:: operator-(const complex&c2)const{
        return complex(re-c2.re,im-c2.im) ;
    }
    complex complex:: operator*(const complex&c2)const{
        return complex((re*c2.re-im*c2.im),(re*c2.im+im*c2.re));
    }
    complex complex:: operator/(const complex&c2)const{
        return (*this*conjugate(c2))/(abs(c2)*abs(c2)) ;
    }
    complex complex:: operator*(const double &scalar)const{
        return complex(scalar*re,scalar*im);
    }
    complex complex::operator/(const double &scalar)const{
        return complex(re/scalar,im/scalar);
    }
    void complex:: operator+=(const complex&c2){
        *this = *this+c2 ;
    }
    void complex::operator-=(const complex&c2) {
        *this = *this-c2 ;
    }
    void complex::operator*=(const complex&c2) {
        *this = *this*c2 ;
    }
    void complex::operator/=(const complex&c2){
        *this = *this/c2 ;
    }
    void complex::operator^=(const double &power){
        *this = *this^power;
    }
    void complex::operator*=(const double &scalar){
        *this = *this*scalar;
    }
    void complex::operator/=(const double &scalar){
        *this = *this/scalar;
    }
    complex complex:: operator^(const double &power) const{
        double rad = pow(abs(*this),power) ;
        double the = power*theta() ;

        return complex(rad*cos(the),rad*sin(the)) ;
    }

    double complex::theta(void)const{
        return atan2(im,re);
    }
    double abs(const complex&c){
        return sqrt(c.get_re()*c.get_re()+c.get_im()*c.get_im()) ;
    }
    bool complex::operator>(const complex&c2)const{
        return abs(*this)>abs(c2) ;
    }
    bool complex::operator<(const complex&c2)const{
        return abs(*this)<abs(c2) ;
    }
    bool complex::operator==(const complex&c2)const{
         return (abs(re-c2.re)<tolerance&&abs(im-c2.im)<tolerance);
    }
    bool complex::operator!=(const complex&c2)const{
        return !(*this==c2) ;
    }

    std::ostream& operator<<(std::ostream& os, const complex& c) {
        os << c.re;
        if(abs(c.im)>tolerance){
            if(c.im>0){
               os << "+";
            }
            os << c.im << "j";
        }
        return os;
    }
    string to_string(complex&c){
        string ret_str =to_string(c.get_re()) ;
        if(c.get_im()>0){
            ret_str+="+";
        }
        ret_str+=to_string(c.get_im()) ;
        return ret_str ;
    }

    // Template specialization for your complex type
    complex conjugate(const complex& val) {
        // Replace with your own implementation for complex numbers
        return complex(val.get_re(),val.get_im()*-1);
    }
    unsigned char conjugate(const unsigned char &val){
        return val ;
    }
    char conjugate(const char &val){
        return val ;
    }

    unsigned int conjugate(const unsigned int &val){
        return val ;
    }
    int conjugate(const int &val){
        return val ;
    }

    float conjugate(const float &val){
        return val ;
    }
     double conjugate(const double &val){
        return val ;
    }
    unsigned long conjugate(const unsigned long &val){
        return val ;
    }
    long conjugate(const long &val){
        return val ;
    }
    long long conjugate(const long long &val){
        return val ;
    }
    unsigned long long conjugate(const unsigned long long &val){
        return val ;
    }
    long double conjugate(const long double&val){
    return val ;
    }

    void complex ::operator=(const double & val) {
        re = val ;
        im = 0;
    }
