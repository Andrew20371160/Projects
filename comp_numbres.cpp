#include <iostream>
#include<cmath>

using namespace std;
class Complex{
private:
    double re ,im ;
public:
    Complex( double a = 0.0 ,double b=0.0){re = a ; im = b ;    }
    friend istream& operator >> (istream& ,Complex &);

   friend ostream& operator<<(ostream &,Complex&);

    Complex operator +(const Complex cc2)const{

        double x = re +cc2.re ;
        double y= im +cc2.im ;
        return Complex(x,y);
    }
    Complex operator-(const Complex cc2)const {

        double x = re -cc2.re ;
        double y= im -cc2.im ;
        return Complex(x,y);
    }
    Complex operator *(const Complex cc2)const {

    double x  = (re *cc2.re +im *cc2.im *(-1));
  double y= re *cc2.im +cc2.re *im;
    return Complex(x,y) ;
    }

    Complex  operator /(Complex cc2)const {

        double k = ((cc2.re *cc2.re) +(cc2.im *(cc2.im*(-1))*(-1)));
       double x =( re *cc2.re +  im * ( -1 *cc2.im)*(-1))/k;
       double y = ((re *(-1)*cc2.im )+(im *cc2.re)) /k  ;
       return Complex(x,y);
    }
bool operator> ( Complex cc2 ){


return (mag() >  cc2.mag());
}
bool operator<( Complex cc2 ){
return (mag() < cc2.mag());
}
bool operator <=( Complex cc2){
return (mag() <= cc2.mag());
}
bool operator >=( Complex cc2){
return (mag() >= cc2.mag());

}
bool operator ==( Complex cc2){
return (mag() == cc2.mag());
}
double mag(){
        Complex cc1;
    double mag1 ;
      cc1.re=re*re;
        cc1.im=im*im;
        mag1  =cc1.re +cc1.im ;
        mag1 = sqrt(mag1);
        return mag1 ;

    }
void operator = (Complex cc2){
    re = cc2.re ;
    im = cc2.im ;
}
Complex operator +=(Complex cc2){

re = re + cc2.re ;
im += cc2.im ;
return Complex(re,im);

}
Complex operator -=(Complex cc2){

re = re -cc2.re ;
im = im -cc2.im ;
return Complex(re,im);

}
Complex operator *= (Complex cc2 ){
 double x = (re *cc2.re +im *cc2.im *(-1));
  im = re *cc2.im +cc2.re *im;
  re = x ;
    return Complex(re,im);
}
Complex operator /= (Complex cc2){


        double k = ((cc2.re *cc2.re) +(cc2.im *(cc2.im*(-1))*(-1)));
       double x =( re *cc2.re +  im * ( -1 *cc2.im)*(-1))/k;
       im= ((re *(-1)*cc2.im )+(im *cc2.re)) /k  ;
       re = x ;
       return Complex(re,im);

}
};
 istream& operator >> (istream & sin ,Complex &cc2 ){
        char ch ,op ;
    cout<<"enter the complex number \n" ;
    sin>>cc2.re>>op>>cc2.im>>ch ;
    return sin ;

    }
   ostream& operator<<(ostream & sout,Complex&   cc2){
  sout<<"("<<cc2.re<<","<<cc2.im<<")"<<endl;
   return sout ;
    }
int main()
{
Complex c1 ,c2 ,c3;
char ch ,ch2;
do{

cin>>c1>>ch>>c2 ;
switch(ch) {
case '+' :c3 =c1+c2 ; cout<<endl<<c3 ;break;
case '-' :c3 =c1 -c2 ; cout<<endl<<c3 ;break;
case '*' :c3 =c1*c2 ; cout<<endl<<c3 ;break;
case '/' :c3 =c1/c2 ; cout<<endl<<c3 ;break;
case  '>': cout<<(c1>c2)?"True":"false" ;break;
case  '<': cout<<(c1<c2)?"True":"false" ;break;

}

cout<<"\n another(y/n)? ";
cin>>ch2 ;
}while(ch2 != 'n') ;











    return 0;
}
