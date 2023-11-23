
#include <iostream>
#include<cstring>
#define MAX 24
using namespace std;
struct node {
char* number;
char * name ;
node * right ;
node * left ;
};

// the number is in char type to allow a more advanced search type of function (search_by_number(node * root , char * number))
//make memory and insertion functions
node * get_node(char* number , char * name ){
node * newnode = new node ;
newnode->number = new char[strlen(number)+1];
strcpy(newnode->number,number);
newnode->name = new char[strlen(name)+1];
strcpy(newnode->name,name) ;
newnode->left = NULL;
newnode->right = NULL;
return newnode ;
}
node * insert_node(node * root , char* number , char * name ){
if(root==NULL){
    root = get_node(number,name);
    return root ;
}
else if(strcmp(name,root->name)<=0){
    root->left =insert_node(root->left ,number ,name);
}
else {
    root->right = insert_node(root->right,number,name) ;
}
return root ;
}
void insert_via_user(node ** root){
char name[MAX];
char number[MAX] ;
cout<<"\nEnter the contact's name\n";
cin>>name;
cout<<endl<<"Enter the contact's number\n";
cin>>number ;
*root = insert_node(*root ,number,name) ;
}
//search functions
void show_node(node * root){
if(root==NULL){
return ;
}
cout<<endl<<"Name : "<<root->name<<endl;
cout<<endl<<"Number : "<<root->number<<endl;
}


void search_by_name(node* root,char *name){
if(root==NULL){
    return;
}
//this line if user sends a full correct name it's faster that way to find the contact wanted
else if(strcmp(root->name,name)==0){
show_node(root);
return ;
}

search_by_name(root->left,name);
//explanation of the following lines of codes is in search_by_number function
int s = strlen(name);
char * portion = new char[s];
for(int i = 0 ; i<s;i++){
    *(portion+i) = *(root->name+i);
}
*(portion+s)= '\0';
if(strcmp(portion,name)==0){
    show_node(root);
}
search_by_name(root->right,name) ;
return ;
}
void search_by_number(node*root,char*number){
if(root==NULL){
    return ;
}
else if(strcmp(root->number,number)==0){
show_node(root);
}
search_by_number(root->left,number);

//here we want to check if the portion the user gives us is exactly as the portion of the number in the current node (both of the same size)
//meaning if user sends "22" then we compare it with first 2 digits of the number in the node and so on
int s = strlen(number);
char * portion = new char[s];
for(int i = 0 ; i<s;i++){
    *(portion+i) = *(root->number+i);
}
//don't forget to put null at last character to prevent bugs of having some joker sticker in the end of the (portion) string
*(portion+s)= '\0';
//we compare that portion and then magic happens :)
if(strcmp(portion,number)==0){
    show_node(root);
}

search_by_number(root->right,number) ;
return ;
}
void search_via_user(node * contacts ){
char str[MAX] ;
int howsearch ;
cout<<endl<<"1---Search by name\n2---Search by number\n";
cin>>howsearch ;
switch(howsearch){
case 1:{
cout<<"\n Enter what you remember of the name" ;
cin>>str ;
search_by_name(contacts,str);
}break ;
case 2:{
cout<<"\n Enter what you remember of the number" ;
cin>>str ;
search_by_number(contacts,str) ;
}break ;
default :{
    cout<<"\nWrong input\n";

}break;
}
}


void inorder(node * root){
if(root==NULL){
    return ;
}
inorder(root->left);
show_node(root) ;
inorder(root->right) ;
}
//deletion functions
node * find_min(node * root){
if(root->left==NULL){
    return root ;
}
return find_min(root->left);
}
node * del_node(node * root, char*name){
if(root==NULL){
    printf("\nNo such contact exists");
    return root ;
}
else if(strcmp(name,root->name)<0){
    root->left = del_node(root->left ,name);
}
else if (strcmp(name,root->name)>0) {
   root->right = del_node(root->right,name) ;
}
else{
if(root->left==NULL&&root->right ==NULL){
    delete[]root ;
    root=NULL;
}
else if(root->left==NULL){
    node*temp = root;
    root =root->right ;
delete[]temp ;
temp = NULL ;
}
else if(root->right==NULL){
    node*temp = root;
    root =root->left ;
    delete[]temp;
    temp = NULL ;
}
else {
    node*temp = find_min(root->right) ;
    root->name = new char[strlen(temp->name)+1];
    strcpy(root->name,temp->name);
    root->number = (char*)malloc(sizeof(char)*strlen(temp->number)+1);
    strcpy(root->number,temp->number);
    root->right = del_node(root->right,temp->name);
}
return root ;
}
return root ;
}
node *del_all(node*root){
if(root==NULL){
    return root ;
}
root->left = del_all(root->left) ;
root = del_node(root,root->name);
if(root==NULL){
    return root ;
}
root->right = del_all(root->right);
return root ;
}

int main()
{
node * contacts = NULL ;
while(1){
int choice;
cout<<"\n1---Insert a new contact\n2---Search for a contact\n3---Show all contacts\n4---edit a contact\n5---Delete a contact";
cout<<"\n6---Delete all contacts\n7---exit\nChoice : ";
cin>>choice ;
switch(choice){
case 1:{
 insert_via_user(&contacts);
}break ;
case 2 :{
search_via_user(contacts) ;
}break ;
case 3 :{
inorder(contacts);
}break ;
case 4:{
char str[MAX];
search_via_user(contacts) ;
cout<<"\n Now enter the exact contact's name you want to edit\n";
cin>>str;
contacts = del_node(contacts,str);
insert_via_user(&contacts);
}break ;
case 5 :{
char str[MAX];
search_via_user(contacts) ;
cout<<endl<<"\n Now enter the exact name of the contact you want to delete\n";
cin>>str;
contacts = del_node(contacts,str);
}break ;
case 6:{
    if(contacts ==NULL){
        break ;
    }
    contacts = del_all(contacts);
    if(contacts==NULL){
        break ;
    }
    contacts = del_node(contacts,contacts->name);
}break;
case 7:{cout<<endl<<"\nThanks for using the software :) (Andrew)";
system("\npause\n");
exit(0);
}break;
}
}
return 0;
}
