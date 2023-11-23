#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define max 20
//Node structure
typedef struct {
int sernum ;
int quantity ;
char * type ;
float price ;
struct node * left  ;
struct node * right ;
}node;
//get memory for a new node
node * get_node(int sernum, int quantity,char * type,float price){
node * cloth =(node*)malloc(sizeof(node));
cloth->left = NULL ;
cloth->right= NULL ;
cloth->sernum= sernum ;
cloth->quantity =quantity ;
cloth->price = price ;
cloth->type = (char*)malloc(sizeof(char)*(strlen(type)+1));
strcpy(cloth->type,type) ;
return cloth ;
}
//insert a new node into the BST
node * insert_cloth(node * root ,int sernum, int quantity,char * type,float price){
if(root==NULL){
    root= get_node(sernum , quantity,type,price) ;
}
else if(sernum<root->sernum){
    root->left = insert_cloth(root->left,sernum,quantity,type,price) ;
}
else if (sernum>root->sernum) {
        root->right = insert_cloth(root->right,sernum,quantity,type,price) ;

}
else  {
    printf("\nCan't have 2 products with same serial number!\n") ;

}
 return root  ;
}
//Getting data from user to insert a new product
void add_cloth_via_user(node**root){
int sernum,quantity;
float price ;
char product[max];
printf("\nEnter the serial number");
scanf("%d",&sernum) ;
printf("\nEnter the quantity");
scanf("%d",&quantity) ;
printf("\nEnter the cloth type");
scanf("%s",product) ;
printf("\nEnter the price ");
scanf("%f",&price) ;
*root = insert_cloth(*root,sernum,quantity,product,price) ;
}
//used in the adjust function below it (return an address of a node of the same serial number)
node *get_address(int sernum , node * root){
if(root==NULL){
    return root ;
}
else if(root->sernum ==sernum) {
    return root ;
}
else if(sernum<root->sernum){
    return get_address(sernum,root->left);
}
else {
    return get_address(sernum,root->right);
}
}
//Adjust data by the user
void adjust(int sernum,node ** root){
node * temp = get_address(sernum,*root);
if(temp==NULL){
    return ;
}
else{
int choice ;
printf("\nSpecify what to update :\n1---Quantity\n2---price\n3---Type\nChoice : ");
scanf("%d",&choice);
switch(choice){
case 1 :{
printf("\nEnter the new quantity : ");
scanf("%d",&temp->quantity);
}break;
case 2 :{
printf("\nEnter the new price : ");
scanf("%f",&temp->price);
}break;
case 3 :{
temp->type= (char*)malloc(sizeof(char)*max) ;
printf("\nEnter  the new type : ");
scanf("%s",temp->type);
}break ;
default:{
printf("\nWrong input!");
}break;
}
}
}
//show data of a certain product
void show_data(int sernum, node *  root){
if(root==NULL){
    return ;
}
else if(sernum==root->sernum){
    printf("\nSerial number : %d\n",root->sernum) ;
    printf("\nType : %s \n",root->type) ;
    printf("\nQuantity : %d\n",root->quantity) ;
    printf("\nPrice : %.2f $\n",root->price) ;
    return ;
}
else if(sernum<root->sernum){
    show_data(sernum,root->left);
}
else{
    show_data(sernum,root->right)  ;
}
}
//show all data of the each product in the factory
void show_alldata(node*root){
if(root ==NULL){
    return ;
}
show_alldata(root->left) ;
    printf("\nSerial number : %d\n",root->sernum) ;
    printf("\nType : %s \n",root->type) ;
    printf("\nQuantity : %d\n",root->quantity) ;
    printf("\nPrice : %.2f $\n",root->price) ;
show_alldata(root->right);
}
//used in deletion function (gets the node with maximum serial number in the factory)
node * get_max(node * root){
if(root->right==NULL){
    return root ;
}
else{
    return get_max(root->right);
}
}
//Deletion function
node * stop_product(int sernum , node * root){
if(root==NULL){
    return root  ;
}
else if(sernum>root->sernum){
    root->right = stop_product(sernum,root->right) ;
}
else if(sernum<root->sernum){
    root->left= stop_product(sernum,root->left) ;
}
else {
    if(root->left ==NULL&&root->right  ==NULL){
        free(root) ;
        root = NULL ;
    }
    else if(root->left==NULL){
        node * temp = root ;
        root = root->right ;
        free(temp) ;
        temp =NULL ;
    }
    else if(root->right==NULL){
        node * temp = root ;
        root = root->left ;
        free(temp) ;
        temp =NULL ;
    }
    else {
        node * temp = get_max(root->left);
        root->sernum = temp ->sernum;
        root->price = temp ->price;
        root->type = (char*)malloc(sizeof(char)*(strlen(temp->type)+1));
        root->quantity = temp ->quantity;
       root->left= stop_product(temp->sernum,root->left) ;
    }
return root ;
}
return root ;
}

int main()
{
node *factory  = NULL;
while(1){
int choice ;
int sernum;
printf("\nCloth factory system\n")    ;
printf("\n1---Insert a new product\n2---Search for a product\n3---Adjust a product's data"
"\n4---Stop producing a product\n5---show all products data\n6---exit\nChoice : ");
scanf("%d",&choice);
switch(choice){
case 1:{
add_cloth_via_user(&factory);
}break;
case 2 :{
printf("\nEnter the serial number");
scanf("%d",&sernum);
show_data(sernum,factory);
}break;
case 3 :{
printf("\nEnter the serial number");
scanf("%d",&sernum);
adjust(sernum,&factory);
}break;
case 4 :{
printf("\nEnter the serial number");
scanf("%d",&sernum);
factory = stop_product(sernum,factory);
}break;
case 5:{
show_alldata(factory);
}break;
case 6:{
printf("\nThanks for using the system :) (Andrew Karam)\n");
system("pause");
free(factory);
exit(0);
}
}
}


    return 0;
}
