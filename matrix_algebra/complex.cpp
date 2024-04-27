#include "complex.h"

    complex::complex(float _re,float _im){
        re =_re ;
        im = _im   ;
    }
    complex::complex(const complex&src){
        re = abs(src.re)>tolerance?src.re:0  ;
        im = abs(src.im)>tolerance?src.im:0 ;
    }
    complex::~complex(){
    }
    float complex::get_re(void)const{
        return re ;
    }
    float complex::get_im(void)const{
        return im ;
    }
    void complex:: operator=(const complex&src){
        re = abs(src.re)>tolerance?src.re:0  ;
        im = abs(src.im)>tolerance?src.im:0 ;
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
    complex complex:: operator*(const float&scalar)const{
        return complex(scalar*re,scalar*im);
    }
    complex complex::operator/(const float&scalar)const{
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
    void complex::operator^=(const float&power){
        *this = *this^power;
    }
    void complex::operator*=(const float&scalar){
        *this = *this*scalar;
    }
    void complex::operator/=(const float&scalar){
        *this = *this/scalar;
    }
    complex complex:: operator^(const float&power) const{
        float rad = pow(abs(*this),power) ;
        float the = power*theta() ;
        return complex(rad*cos(the*to_rad),rad*sin(the*to_rad)) ;
    }

    float complex::theta(void)const{
        if(abs(re)>tolerance){
            float val =atan(abs(im)/abs(re))*to_deg;
            if(re>0&&im>0){
                return val ;
            }
            else if(re<0&&im>0){
                return 180-val ;
            }
            else if(re<0&&im<0){
                return 270 - val ;
            }
            else{
                return 360-val ;
            }
        }
        else{
            return(im>0)?90:180 ;
        }
    }
    float abs(const complex&c){
        return sqrt(c.get_re()*c.get_re()+c.get_im()*c.get_im()) ;
    }
    bool complex::operator>(const complex&c2)const{
        return abs(*this)>abs(c2) ;
    }
    bool complex::operator<(const complex&c2)const{
        return abs(*this)<abs(c2) ;
    }
    bool complex::operator==(const complex&c2)const{
        return abs(abs(*this)-abs(c2))<=tolerance ;
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
    void complex ::operator=(const float& val) {
        re = val ;
        im = 0;
    }

