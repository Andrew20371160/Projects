#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 20
/*Using a binary tree for managing various data types.
The program can be adapted for different systems like banks or schools.
*/
char system_name[max];
char int_name[max];
char float_name[max];
char char_name[max];
//Node structure
typedef struct {
int num ;
float fnum ;
char * str ;
struct node * left ;
struct node * right ;
}node ;

//get memory for a new node
node * getnode(int num , float fnum , char * str){
node * newnode= malloc(sizeof(node)) ;
newnode->num = num ;
newnode->fnum = fnum ;
newnode->str = (char*)malloc(sizeof(char)*(strlen(str)+1));
strcpy(newnode->str,str);
newnode->left=NULL ;
newnode->right=NULL ;

return newnode ;
}
//Insertion function
node * insert(node * root ,int num , float fnum , char * str){
if(root==NULL){
    root = getnode(num,fnum,str) ;
}
else if(num<root->num){
    root->left = insert(root->left,num,fnum,str) ;
}
else if(num>root->num){
    root->right = insert(root->right,num,fnum,str);
}
else {
    printf("\nCan't have 2 nodes with same %s \n",int_name);
}
return root ;
}
//takes data from user to insert it into the BST
void insert_via_user(node**root){
int num ;
float f1 ;
char str[max];
printf("\nEnter the %s : ",int_name);
scanf("%d",&num);
printf("\nEnter the %s : ",float_name);
scanf("%f",&f1);
printf("\nEnter the %s : ",char_name);
scanf("%s",str);
(*root) = insert(*root,num,f1,str);
}
//this function returns the address of the wanted node
//make sure to get that on a temp pointer not the root
node * get_node_address(int num , node * root){
if(root==NULL){
    return root ;
}
else if(num==root->num){
    return root ;
}
else if(num<root->num){
    return get_node_address(num,root->left);
}
else {
    return get_node_address(num,root->right);
}
}
//show data function (can be combined with find_data function)
void showdata(node*ptr){
if(ptr==NULL){
    return ;
}
printf("\n%s : %d",int_name,ptr->num);
printf("\n%s : %.2f",float_name,ptr->fnum);
printf("\n%s : %s",char_name,ptr->str);
}
//Search function
void find_node(int num,node * root){
if(root==NULL){
    return ;
}
node * ptr = get_node_address(num,root) ;
showdata(ptr);
}
node * find_max(node*root){
if(root==NULL){
    return root ;
}
else if(root->right==NULL){
    return root ;
}
else {
    return find_max(root->right);
}
}
//Update for float data or the string
void update(int num,node**root){
node * ptr = get_node_address(num,*root);
showdata(ptr);
if(ptr ==NULL){
        printf("\nData not found!!");
    return ;
}
else{
int choice ;

printf("\nEnter what to update :1---%s",char_name);
printf("\n2---%s\nEnter : ",float_name);
scanf("%d",&choice) ;
switch(choice){
case 1 :{
scanf("%s",ptr->str) ;
}break ;
case 2 :{
scanf("%f",ptr->fnum);
}break;
default:{
return;
}
}
}
}
//Deletion function
node * del_data(int num,node*root){
if(root==NULL){
    return root  ;
}
else if(num<root->num){
    root->left = del_data(num,root->left);
}
else if(num>root->num){
    root->right = del_data(num,root->right) ;
}
else {
if(root->left==NULL&&root->right==NULL){
    free(root) ;
    root = NULL;
}
else if(root->left==NULL){
    node * temp = root;
    root = root->right;
    free(temp) ;
    temp =NULL;
}
else if(root->right==NULL){
    node * temp = root;
    root = root->left;
    free(temp) ;
    temp =NULL;
}
else {
node * temp = find_max(root->left);
root->num = temp->num;
root->fnum = temp->fnum;
root->str =(char*)malloc(sizeof(char)*strlen(temp->str)+1);
strcpy(root->str,temp->str);
del_data(temp->num,root->left);
}
return root ;
}
return root ;
}
//This function does 3 things (calls one of 3 function)
void find_update_del(int choice,node**root){
int num ;
printf("\nEnter the %s",int_name);
scanf("%d",&num) ;
switch(choice){
//Go to main function and you will know why the numbers are in this order
case 2 :{
find_node(num,*root);
}break;
case 3 :{
    update(num,root);
}break;
case 4:{
(*root)=del_data(num,*root);
}break ;
default:{
    return;
}
}
}
//Display all data
void inorder(node*root){
if(root==NULL){
    return  ;
}
inorder(root->left);
showdata(root) ;
inorder(root->right);
}


int main(){
node *root =NULL ;

printf("\nWelcome To POE (project of everything)");
printf("\nThe idea is that you can use the same software for multiple projects\n");
printf("\nType the name of the system : ");
scanf("%s",system_name);
printf("\nType the Special number name: ");
scanf("%s",int_name);
printf("\nType the Floating point data name : ");
scanf("%s",float_name);
printf("\nType the text data name : ");
scanf("%s",char_name);
while(1){
int choice;
printf("\n\n%s System\n\n",system_name) ;
printf("\n1---Insert data into the system\n2---Search\n3---Update data in the system"
"\n4---Delete\n5---Show all data\n6---Exit");
printf("\nEnter your choice : ");
scanf("%d",&choice);
switch(choice){
case 1: {
insert_via_user(&root);
}break ;
case 2:{
find_update_del(choice,&root);
}break;
case 3:{
find_update_del(choice,&root);
}break;
case 4:{
find_update_del(choice,&root);
}break ;
case 5:{
inorder(root);
}break;
case 6 :{
    printf("\nhope you had fun (Andrew karam :) )");
    system("pause");
    exit(0);
}
}
}
free(root) ;
return 0 ;
}
