#include <iostream>
#include<cstring>
#define MAX 30
using namespace std;
enum life_status{dead,alive};
struct date{
int day,month,year ;
};
struct node {
life_status ls ;
int nat_num ;
date bdate ;
char * name ;
char * city ;
char * mom_name ;
node * right ;
node * left ;
};

node * get_node (int nat_num , date bdate, char * name, char * mom_name,char* city ){
node *root= new node ;
    root->ls = alive;
    root->nat_num = nat_num ;
    root->bdate.day = bdate.day ;
    root->bdate.month = bdate.month;
    root->bdate.year = bdate.year ;
    root->name = new char[strlen(name)+1] ;
    strcpy(root->name,name) ;
    root->mom_name = new char[strlen(mom_name)+1] ;
    strcpy(root->mom_name,mom_name) ;
    root->city = new char[strlen(city)+1] ;
    strcpy(root->city,city) ;
    root->left =NULL ;
    root->right = NULL ;
return  root ;
}


node* insert_person(node * root ,int nat_num , date bdate, char * name, char * mom_name,char* city ){

if(root ==NULL){
root = get_node( nat_num , bdate,  name,  mom_name, city);
return root ;
}
else if(nat_num==root->nat_num){
    cout<<"\n National number is used already ";
 return root;
}
else if(nat_num>root->nat_num){

root->right = insert_person(root->right,nat_num , bdate,  name,  mom_name, city) ;
}
else if(nat_num<root->nat_num){
   root->left=  insert_person(root->left ,nat_num , bdate,  name,  mom_name, city) ;

}
};
node*search_person(int nat_num,node*root){

if(root ==NULL  ){
    cout<<"\n not found";
    return root;
}
else if(root->nat_num ==nat_num){

cout<<"\n Full name : "<<root->name<<endl ;
cout<<"\n National number : "<< root->nat_num<<endl ;
cout<<"\n Mother's name : "<< root->mom_name<<endl ;
cout<<"\n Date of birth : "<< root->bdate.day<<"/"<<root->bdate.month<<"/"<<root->bdate.year<<endl ;
cout<<"\n City of birth : "<< root->city<<endl ;
cout<<"\n Life status : ";
if(root->ls==0){
    cout<<"Dead";
}
else {
    cout<<"Alive";
}
return root ;
}

else if(nat_num>root->nat_num){
return search_person(nat_num,root->right);
}
else{

  return  search_person(nat_num,root->left);
}

}

node*update_data(node*root){
int choice ;
cout<<endl<<"1---update name";
cout<<endl<<"2---update mother's name";
cout<<endl<<"3---update city's name";
cout<<endl<<"4---update birth date"<<endl;
cout<<endl<<"5---update life status"<<endl;
cin>>choice ;
switch(choice){
case 1:{
    cout<<endl<<"Enter the updated name(end input using '!')";
    cin.getline(root->name,MAX,'!');
}break ;
case 2:{
    cout<<endl<<"Enter the updated Mother's name(end input using '!')";
    cin.getline(root->mom_name,MAX,'!');
}break ;
case 3:{
 cout<<endl<<"Enter the updated city name(end input using '!')";
 cin.getline(root->city,10,'!');

}break ;

case 4:{
    char dummychar;
    cout<<endl<<"Enter the updated Birth date (day/month/year)";
cin>>root->bdate.day>>dummychar>>root->bdate.month>>dummychar>>root->bdate.year;

}break ;
case 5:
{
if(root->ls==dead){
    root->ls= alive;
}
else{
    root->ls = dead ;
}
}break ;
}
return root;
}

int main()
{

node * root = NULL ;
cout<<"\n Civil Record Simulation";
while(1){
int choice ;
cout<<endl<<"1---Insert new person data";
cout<<endl<<"2---Search for a person";
cout<<endl<<"3---Update person data "<<endl;
cout<<"4---quit\n";
cin>>choice;
switch(choice){
case 1:{

char dummychar;
char*name = new char[MAX];
char*mom_name = new char[MAX];
char*city = new char[10];
date bdate ;
int nat_num ;
cout<<"Enter the national number :";
cin>>nat_num ;
cout<<endl<<"Enter the name :(end using '!')\n ";
cin.getline(name,MAX,'!');
cout<<endl<<"Enter mother's name :(end using '!')\n";
cin.getline(mom_name,MAX,'!');
cout<<endl<<"Enter the city's name :(end using '!')\n";
cin.getline(city,10,'!');
cout<<"Enter birth date (day/month/year)";
cin>>bdate.day>>dummychar>>bdate.month>>dummychar>>bdate.year;
root = insert_person(root,nat_num,bdate,name,mom_name,city);
delete[]name;
delete[]mom_name;
delete[]city;

}break;
case 2:
{int nat_num ;
        cout<<"\n Enter the national number\n ";
        cin>>nat_num ;
        search_person(nat_num,root);

}break;

case 3:
{
int nat_num ;
cout<<"\n enter the national number ";
cin>>nat_num;

node * update = search_person(nat_num,root);
if(update==NULL){
    break;
}
update =update_data(update);
}break;
case 4 :
    {
        exit(0);

    }


}


}



    return 0;
}
