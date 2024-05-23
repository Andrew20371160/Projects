#include<iostream>
#include<cmath>
#include<process.h>
using namespace std ;
const float pi = 3.14159265 ;
class shapes{
public :
virtual void dimensions ()= 0;
virtual float area () = 0 ;
virtual void print () =0 ;
};
class d2 :public shapes {
public:
void print(){
cout<<" area = "<<area();
cout<<endl<<" perimeter = "<<perimeter();

}
virtual float perimeter() = 0;
};
class d3 :public shapes {
public:
virtual float volume () = 0;
virtual float side_area() = 0;
void print(){
cout<<" area = "<<area();
cout<<endl<<" volume = "<<volume();
cout<<"\n side area = "<<side_area();

}
};
class rectangular :public d2{
private:
float l1 ,l2 ;
public:
void dimensions (){
cout<<"enter 1st length \n ";cin>>l1 ;
cout<<"enter 2nd length \n "; cin>>l2 ;
}
float area
(){
return(l1*l2);
}
float perimeter(){
return(2*(l1+l2));
}
};
class circle :public d2 {
private:
    float r ;
public:
  void dimensions (){
cout<<"enter the radius ";cin>>r ;
}
float area(){
return (pi *r*r );
}
float perimeter(){
return(2*pi*r );
}
};
class regular_polygon  :public d2 {
protected:
int n ;
float side  ;
public:
void dimensions (){
cout<<" \n enter the number of sides ";
cin>>n ;

cout<<"enter the side length ";
cin>>side ;
}
float area(){
switch(n ){
case 3 : return ((sqrt(3)/4)*side*side); break ;
case 4 : return( side * side) ;break ;
case (5): return((5*side*side)/(4*0.726542528));break ;
case 6 :return((3*sqrt(3)*side *side )/2); break ;
case 7 : return(3.634*side*side); break ;
case 8 : return (2*side*side *(1+sqrt(2))); break ;
case 9 : return((9/4)*side *side*2.74747742);break ;
case 10: return(7.694*side*side ) ;break ;
default : cout<<"the shapes are from regular triangles to decagons (write number of sides from 3:10 )";exit(0) ;
}

}
float perimeter(){
return(n*side);
}
};
class  triangles :public d2 {
private:
float a,b,c ;
int n ;
public:
void dimensions(){
cout<<"1--- normal triangle \n ";
cout<<"2--- right triangle \n ";
cout<<"3--- regular triangle ";
cin>>n ;
switch(n ){
case 1 : cout<<"\n enter a,b,c"; cin>>a>>b>>c ; break ;
case 2 : cout<<"\n enter a,b (bases of triangle enter c "; cin>>a>>b>>c; ;break ;
case 3 : cout<<"\n enter a ";cin>>a ; break ;
default: cout<<"\n 1 2 or 3 only ";  exit(0);
}


}
float area(){
switch(n ){
case 1 :return (0.25 * sqrt( (a + b + c) * (-a + b + c) * (a - b + c) * (a + b - c))) ;
case 2 :return ((0.5)*a*b ) ;break ;
case 3 : return ((sqrt(3)/4)*a*a); break ;

}
}
float perimeter(){
switch(n){
case 1 :return(a+b+c ); break ;
case 2 :return (a+b+c) ; break ;
case 3 :return(3*a ); break ;
}
}
};
class semi_deviant :public d2 {
private:
int n ;
float up ,down , height ,c ;
public:
void dimensions (){
cout<<"1--- right semi deviant \n ";
cout<<"2--- equal legs semi deviant ";
cin>>n ;
switch(n ){
case 1 : cout<<"\n enter upper and lower and height and the curve "; cin>>up>>down>>height>>c ;break ;
case 2 : cout<<"\n enter the upper and lower and height and the curve "; cin>>up>>down>>height>>c ;break ;
default:cout<<"wrong inputs "; exit(0);
}
}
float area(){
switch(n){

case 2: return((0.5)*(up +down )*height); break ;
case 1 : return ((up *height )+((0.5)*(down -up )*height )) ;break ;

}
}
float perimeter(){
switch(n)
{
case 1 :return (up+down+c+height) ;break ;
case 2 :return((2*c)+up+down);break ;
}
}
};
class parallelogram :public d2{
private :
float base , height ;
float b2 ;
public:
void dimensions(){
cout<<"\n enter the base and the height thats is vertical on the base ";
cin>>base>>height ;
cout<<"\n now enter the other base to calculate the perimeter ";
cin>>b2 ;
}
float area(){
return(base*height);
}
float perimeter(){
return(2*(base +b2 ));

}

};
class rhombus :public d2 {
private:
float d1 ,d2 ;
float length ;
public:
void dimensions(){
cout<<"\n enter the 1st Diameter and the 2nd Diameter ";
cin>>d1>>d2 ;
}
float area(){
return(0.5*d1*d2 );
}
float perimeter(){
length  =( 0.5*sqrt(d1*d1+d2*d2));
return(4*length );
}
};
class oval_shape : public d2 {
private:
float a,b;
public:
void dimensions(){
cout<<"\n enter the big and the small diameter (same repeat ) ";
cin>>a>>b ;
}
float area(){
return(a*b *pi);
}
float perimeter(){
return (pi*(3*(a+b)-sqrt((3*a+b)*(3*b+a))));
}
};
class cube :public d3 {
private:
float length ;
public :
void dimensions(){
cout<<"\n enter a side length ";
cin>>length ;
}

float volume(){
return(length*length*length);
}
float area(){
return(6*length*length);
}
float side_area(){
return (4*length*length);

}

};
class Parallel_rectangles  :public d3 {
protected:
float a,b ,height ;
public:
void dimensions(){
cout<<"\n enter a ,b , height  ";
cin>>a>>b>>height  ;
}
float volume (){
return(a*b*height );
}
float area(){
return (2*((a*b)+(b*height)+(a*height) ));
}
float side_area(){
return(2*height*(a+b));
}

};
class ball :public d3 {
private:
float r ;
public:
void dimensions(){
cout<<"\n  enter the radius of the ball ";
cin>>r ;

}
float area(){
return(4*pi*r*r );
}
float volume(){
return(((4)*pi*r*r*r)/(3));
}
float side_area(){
return 0;
}

};
class regular_pyramid : public d3 {
private:
float a,h ,s;
public:
void dimensions(){
cout<<"\n enter the side length and the height and enter slant height ";
cin>>a>>h>>s ;
}
float volume(){
return((a*a*h)/3);
}
float area (){

return ((2*a*s)+ (a*a))   ;
}
float side_area (){
return (2*a*s) ;

}



};
class cone :public d3 {
private:
float r ,h ;
public :
void dimensions(){
cout<<"\n enter the radius than the height of the cone ";
cin>>r>>h ;
}
float side_area(){
float s ;
s = sqrt((r*r) +(h*h));
return(pi*r*s);
}
float volume(){
return ((pi*r*r*h)/3);
}
float area(){
float s ;
s = sqrt((r*r) +(h*h));;
return((pi*r*s)+(pi*r*r)) ;

}


};
class cylinder :public d3 {
private:
float r ,h ;
public :
float area(){
return((2*pi*r)*(r+h));
}
void dimensions(){
cout<<"\n enter the radius and the height of the cylinder";
cin>>r>>h ;
}
float side_area(){
return(2*pi*r*h);
}
float volume(){
return (pi*r*r*h);

}


};
int main(){

cout<<" welcome to Shapes \n ";
system("pause");
char ch ;
do{
int n ;
cout<<"\n  1--- 2d shapes \n 2--- 3d shapes \n ";
cin>>n ;
int q ;
if(n==1){

     cout<<" 1--- regular polygons \n 2---rectangular \n 3--- circle \n 4--- triangles \n 5--- semi deviant \n 6---parallelogram \n 7---rhombus \n 8--- oval shape ";
     cin>>q ;
     switch(q){
     case 1 :{ regular_polygon * reg ; reg = new regular_polygon ;   reg->dimensions(); reg->print(); delete[]reg ; break ;}
     case 2 : {rectangular * re ; re = new rectangular ;re->dimensions(); re->print();delete[]re ; break ;}
     case 3 : {circle * ci ; ci = new circle ;  ci->dimensions() ; ci->print(); delete[]ci ;break ;}
     case 4 : {triangles * tr ;tr = new triangles ;  tr->dimensions() ; tr->print();delete[]tr ;break ;}
     case 5 : {semi_deviant * se ; se = new semi_deviant ;  se->dimensions(); se->print();  delete[]se  ;break ;}
     case 6 : {parallelogram *  pa ;pa = new parallelogram;  pa->dimensions(); pa->print() ; delete []pa; break ;}
     case 7 : {rhombus * rh ;rh = new rhombus ;  rh->dimensions(); rh->print() ; delete[]rh ;  break ;}
     case 8 : {oval_shape * ov ;  ov = new oval_shape ; ov->dimensions(); ov->print() ; delete []ov ;  break ;}
     default: {cout<<"\n wrong inputs "; continue ;cout<<endl;}
     }

}
else if (n==2 ){
    cout<<"1---cube \n 2---Parallel rectangles \n 3--- ball \n 4---regular pyramid \n 5---cone \n 6---cylinder \n ";
    int q1 ;
    cin>>q1 ;
    switch(q1){
    case 1 : {cube * cu ; cu = new cube ;  cu->dimensions();  cu->print() ; delete[]cu ;  break ;}
    case 2 : {Parallel_rectangles *pa ; pa = new Parallel_rectangles ;  pa->dimensions(); pa->print() ; delete []pa  ;break ;}
    case 3 : {ball * ba ; ba = new ball ; ba->dimensions() ; ba->print(); delete[]ba ;  break ;}
    case 4 : {regular_pyramid * regu ; regu = new regular_pyramid; regu->dimensions(); regu->print(); delete[]regu ;  break ;}
    case 5 : {cone * cy ;cy = new cone ;  cy->dimensions(); cy->print() ; delete[]cy ;  break ;}
    case 6 : {cylinder * cy ; cy =new cylinder ;  cy->dimensions() ; cy->print();  delete[]cy ; break ;}
    default: {cout<<"\n wrong input "; continue ;cout<<endl;}
}
}
else
   {

    cout<<"\n wrong input ";continue ;
    cout<<endl ;
}

cout<<"\n another shape ?(y/n ) \n ";
cin>>ch ;
}while(ch != 'n');

return 0;
}




