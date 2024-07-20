#include<iostream>
#define MAX 20
using namespace std ;
struct room{
bool isfull ;
int num ,id,period,gcount;
float price ;
char *name  ;
};
room hotel[40] ;
void checkin(int num){
if(hotel[num].isfull==1){
    cout<<endl<<"Room is taken\n";
    return ;
}
else {
    cout<<endl<<"Enter the ID ";
    cin>>hotel[num].id ;
    cout<<endl<<"Enter the period ";
    cin>>hotel[num].period;
    hotel[num].name =new char[MAX] ;
    cout<<endl<<"Enter the guest's name ";
    cin>>hotel[num].name;
    hotel[num].isfull = 1 ;
}
}
void checkout(int num ){
if(hotel[num].isfull==0){
    cout<<"\nRoom is empty";
    return ;
}
else {
    cout<<endl<<"Total price : "<<hotel[num].period*hotel[num].price<<" $";
    hotel[num].isfull = 0 ;
    hotel[num].id =0  ;
    hotel[num].period =0  ;
    delete[]hotel[num].name;
}
}
void showdata(int num){
cout<<endl<<"Room's number : "<<hotel[num].num<<endl;
cout<<endl<<"Guest capacity : "<<hotel[num].gcount<<endl;
cout<<endl<<"Price per night : "<<hotel[num].price<<endl;
}
void show_empty(int gcount){
for(int i = 0 ; i <40 ; i++){
    if(hotel[i].isfull==0&&hotel[i].gcount==gcount){
        showdata(i);
    }
}
}
void interface(){
while(1){
int choice;
cout<<endl<<"Hotel's system\n";
cout<<endl<<"1---Show empty rooms \n";
cout<<endl<<"2---Check in\n";
cout<<endl<<"3---Check out\n";
cout<<endl<<"4---exit\nChoice : ";
cin>>choice ;
switch(choice){
case 1 :{
int gcount ;
cout<<"\nEnter the guest count \n";
cin>>gcount;
show_empty(gcount);
}break ;
case 2:{
int num ;
cout<<endl<<"Enter the room's number " ;
cin>>num ;
checkin(num-1)  ;
}break ;
case 3:{
int num ;
cout<<endl<<"Enter the room's number " ;
cin>>num ;
checkout(num-1)  ;
}break ;
case 4 :{
system("pause");
cout<<endl<<"Well I guess hotels' systems are pretty simple :) (Andrew Karam)";
exit(0);
}
}
}
}
int main(){
for(int i =0 ; i <40;i++){
    hotel[i].num = i+1 ;
    hotel[i].isfull=0;
    hotel[i].period=0;
    hotel[i].gcount=0;
    hotel[i].isfull=0;
    hotel[i].id = 0 ;
    if(i<10){
        hotel[i].gcount = 1;
        hotel[i].price =5;
    }
    else if(i>10&&i<25){
        hotel[i].gcount = 2 ;
        hotel[i].price=10 ;
    }
    else {
        hotel[i].gcount=4 ;
        hotel[i].price = 20;
    }
}
interface() ;
return 0;
}
