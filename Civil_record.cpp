#include <iostream>
#include<cstring>
using namespace std;

#define MAX 30
//life status of the person
enum life_status{dead,alive};
struct date{
int day,month,year ;
};
//node of the tree
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
class civil_record{
private:
//root of the tree
node*root  ;
//core functions
node * get_node (int nat_num , date bdate, char * name, char * mom_name,char* city );
node* insert_person(node * root ,int nat_num , date bdate, char * name, char * mom_name,char* city );
node*search_person(int nat_num,node*root);
node*update_data(node*root);
node * delete_tree(node*root);
public:
//constructor
civil_record(){
root = NULL ;
}
//abstracted functions
void get_insert_functionality(int nat_num , date bdate, char * name, char * mom_name,char* city){
root = insert_person(root,nat_num,bdate,name,mom_name,city);
}
void get_search_functionality(int nat_num){
search_person(nat_num,root);
}
void get_update_functionality(int nat_num){
node * temp = search_person(nat_num,root);
if(temp){
update_data(temp);
}
else{
    cout<<"\n not found";
}
}
void get_delete_functionality(void){
root = delete_tree(root);
}
};
//get node function
node* civil_record::get_node(int nat_num, date bdate, char* name, char* mom_name, char* city) {
    node* new_node = new node;
    new_node->ls = alive;
    new_node->nat_num = nat_num;
    new_node->bdate.day = bdate.day;
    new_node->bdate.month = bdate.month;
    new_node->bdate.year = bdate.year;
    new_node->name = new char[strlen(name) + 1];
    strcpy(new_node->name, name);
    new_node->mom_name = new char[strlen(mom_name) + 1];
    strcpy(new_node->mom_name, mom_name);
    new_node->city = new char[strlen(city) + 1];
    strcpy(new_node->city, city);
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}
//insert person function
node*civil_record :: insert_person(node * root ,int nat_num , date bdate, char * name, char * mom_name,char* city ){
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
return root ;
};
//search person function
node* civil_record :: search_person(int nat_num,node*root){
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
cout<<(root->ls==alive)?"Alive":"Dead";
return root ;
}
else if(nat_num>root->nat_num){
return search_person(nat_num,root->right);
}
else{
  return  search_person(nat_num,root->left);
}
}
//update data function
node* civil_record :: update_data(node*root){
    int choice ;
    cout<<endl<<"1---update name";
    cout<<endl<<"2---update mother's name";
    cout<<endl<<"3---update city's name";
    cout<<endl<<"4---update birth date"<<endl;
    cout<<endl<<"5---update life status"<<endl;
    cin>>choice ;
    cin.ignore();
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
        case 5:{
            root->ls= (root->ls==alive)?dead:alive;
        }break ;
        default:
            cout<<"\n wrong choice";    
    }
    return root;
}
node * civil_record:: delete_tree(node* root) {
    if (root == NULL) {
        return;
    }

    // Delete left subtree
    delete_tree(root->left);

    // Delete right subtree
    delete_tree(root->right);

    // Delete root node
    delete[] root->name;
    delete[] root->mom_name;
    delete[] root->city;
    delete root;
}

//controller class of the core bst functions
class controller : public civil_record{
public:
void insert_person_via_user(void);
void search_person_via_user(void);
void update_person_via_user(void);
void delete_tree_via_user(void);
}; 
//insert person via user function (abstracted from the main function)
void controller :: insert_person_via_user(void){
    char dummychar;
    char*name = new char[MAX];
    char*mom_name = new char[MAX];
    char*city = new char[10];
    date bdate ;
    int nat_num ;
    cout<<"Enter the national number :";
    cin>>nat_num ;
    cin.ignore();
    cout<<endl<<"Enter the name :(end using '!')\n ";
    cin.getline(name,MAX,'!');
    cout<<endl<<"Enter mother's name :(end using '!')\n";
    cin.ignore();
    cin.getline(mom_name,MAX,'!');
    cout<<endl<<"Enter the city's name :(end using '!')\n";
    cin.ignore();
    cin.getline(city,10,'!');
    cout<<"Enter birth date (day/month/year)";
    cin>>bdate.day>>dummychar>>bdate.month>>dummychar>>bdate.year;
    get_insert_functionality(nat_num,bdate,name,mom_name,city);
    delete[]name;
    delete[]mom_name;
    delete[]city;
}

//search person via user function (abstracted from the main function)
void controller :: search_person_via_user(void){
    int nat_num ;
        cout<<"\n Enter the national number\n ";
        cin>>nat_num ;
        get_search_functionality(nat_num);
}

void controller ::update_person_via_user(void){
int nat_num ;
cout<<"\n enter the national number ";
cin>>nat_num;
get_update_functionality(nat_num);
}
void controller ::delete_tree_via_user(void){
get_delete_functionality();
}

int main()
{
controller cr ; //object of the class
cout<<"\n Civil Record Simulation";
while(1){
int choice ;
cout<<endl<<"1---Insert new person data";
cout<<endl<<"2---Search for a person";
cout<<endl<<"3---Update person's data "<<endl;
cout<<"4---quit\n";
cin>>choice;
switch(choice){
case 1:{
cr.insert_person_via_user();
}break;
case 2:
{
    cr.search_person_via_user(); 
}break;

case 3:
{
    cr.update_person_via_user();
}break;
case 4 :
    {
        cr.delete_tree_via_user(); 
        cout<<"\n Bye Bye thanks for using this software (Andrew Karam :) )" ; 
        cout<<"\n Press any key to exit";
        system("pause");
        exit(0);

    }
}

}

    return 0;
}
