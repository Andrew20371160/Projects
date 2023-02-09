#include<iostream>
#include<string.h>
#define MAX 30
using namespace std ;
struct node {
int acc_num ,rec ;
char  *name ;
node * left ;
node * right ;
};
//get memory for new node
node * get_node(int acc_num , int rec ,char * name  ){
node * root = new node ;
root->acc_num = acc_num ;
root->rec = rec ;
root->name =(char*)malloc(sizeof(char)*MAX);
strcpy(root->name,name) ;
root->left = NULL ;
root->right = NULL ;
return root ;
}
//INSERTION FUNCTION
node * insert_node(int acc_num,int rec , char * name , node * root ){
if(root ==NULL){
    root = get_node(acc_num,rec,name);
    return root ;
}
else if (acc_num ==root->acc_num){
    cout<<"\n account number "<<acc_num<<" already in use \n";
    return root;
}
else if (acc_num >root->acc_num){
root->right =insert_node(acc_num,rec,name,root->right) ;
}

else if (acc_num <root->acc_num){
  root->left = insert_node(acc_num,rec,name,root->left) ;
}
return root ;
}
//DELETION FUNCTION
node * find_max(node * root ){
if(root ==NULL){
    return NULL ;

}
else if (root ->right==NULL){
    return root ;
}
return find_max(root->right) ;
}
node * del_node(int acc_num,node * root ){
if(root==NULL){
        cout<<"\nNo such account exists\n";
    return root ;
}
else if (acc_num >root->acc_num){
    root->right = del_node(acc_num,root->right) ;
}

else if (acc_num <root->acc_num){
    root->left = del_node(acc_num,root->left) ;
}
else {
    if(root->left ==NULL && root->right ==NULL){
        delete[]root;
        root =NULL ;
        return root ;
    }
    else if (root ->left == NULL){
        node * temp = root ;
        root = root->right ;
        delete[]temp ;
        temp = NULL ;
    }
    else if (root ->right == NULL){
        node * temp = root ;
        root = root->left ;
        delete[]temp ;
        temp = NULL ;
    }
else {
        node * temp = find_max(root->left) ;
        root->acc_num = temp->acc_num ;
        root->rec= temp ->rec ;
        root->name = (char*)malloc(sizeof(char)*MAX);
        strcpy(root->name,temp->name) ;
        root->left = del_node(temp->acc_num,root->left) ;
}
return root ;
}
    return root ;

}
//delete all nodes except for one node
node *del_all_nodes(node * root ){
if(root ==NULL){
    return root;
}
root->left = del_all_nodes(root->left);
root =del_node(root->acc_num,root);
if(root==NULL){
    return root ;
}
root->right =del_all_nodes(root->right);
return root ;
}
//SEARCH FUNCTION
node * search_node(int n , node * root ){
if(root ==NULL){
    return root ;
}
else if (root ->acc_num ==n){
cout<<"\n Account number : "<<root->acc_num;
cout<<endl<<"Full-Name : " <<root->name;
cout<<endl<<"Record : "<<root->rec<<endl;
return root;
}
else if (n>root->acc_num){
    root->right = search_node(n,root->right) ;
}
else {
    root->left =search_node(n,root->left) ;
}
return root ;
}


void show_nodes(node * root ){
if(root ==NULL){
    return ;
}
 show_nodes(root->left);
cout<<"\n Account number : "<<root->acc_num;
cout<<endl<<"Full-Name : " <<root->name;
cout<<endl<<"Record : "<<root->rec<<endl;
show_nodes(root->right) ;

}
void update_account(node ** root){
int choice , old_num ;
cout<<"\n specify what to update \n ";
cout<<"\n1---name\n2---record\n3---return to main menu\n";
cin>>choice ;
cout<<"\n enter the account number you want to update " ;
cin>>old_num;
(*root)= search_node(old_num,*root) ;
switch(choice){

case 1 : {
cout<<"\n enter the new name";
(*root)->name =(char*)malloc(sizeof(char)*MAX) ;
cin>>(*root)->name;
}break ;
case 2 :
{
cout<<"\n enter the new record ";
cin>>(*root)->rec ;
}break ;
case 3 : break ;
}



}

void enter_acc_via_user(node ** root ){
int acc_num,rec ;
char name[MAX] ;
cout<<"\n enter the account number ";
cin>>acc_num ;
cout<<endl<<"enter the name " ;
cin>>name;
cout<<endl<<"enter the record ";
cin>>rec;
*root =  insert_node(acc_num,rec,name,*root);
}
void interface(node * root ){
}
int main (){

node * root = NULL ;

cout<<"\n---BANK-INFORMATION-SYSTEM----\n";
while(1){
int n ;

cout<<endl<<"1---Insert an account\n2---Search for an account\n3---Delete an account";
cout<<endl<<"4---show all accounts\n5---Update account's data\n6---Delete every account\n7---quit\nChoice : ";
cin>>n ;
switch(n){
case 1 :{
enter_acc_via_user(&root);
}break ;
case 2 :{
int n  ;
cout<<endl<<"enter the account number ";
cin>>n ;
root =search_node(n,root);
}break ;
case 3 :{
int n ;
cout<<"\n enter the account number " ;
cin>>n ;
root =del_node(n,root) ;
}break ;
case 4 :show_nodes(root) ; break ;
case 5 :update_account(&root) ;break;
case 6: {
if(root==NULL){
break;
}
root = del_all_nodes(root);
root=del_node(root->acc_num,root);
}break ;
break ;
case 7 : cout<<"\n Thanks for using the system :) (Andrew) " ;system("\npause\n"); exit(0);
}
}
return 0 ;
}
