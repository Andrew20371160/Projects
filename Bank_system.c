#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define max 20
typedef struct {
int acc_num ;
int rec ;
char * name ;
struct node * left ;
struct node * right ;
}node;
//get memory for new node(account)
 node * get_node(int acc_num , int rec , char * name ){
 node * newacc = malloc(sizeof(node)) ;
 newacc->acc_num =acc_num ;
 newacc->rec =rec;
 newacc->name =(char*)malloc(sizeof(char)*(strlen(name)+1));
 strcpy(newacc->name,name) ;
 newacc->left= NULL ;
 newacc->right  = NULL ;
return newacc;
}
//INSERTION FUNCTION
 node * insert( node * root,int num,int rec,char * name){
if(root==NULL){
    root =get_node(num,rec,name);
}
else if(num<root->acc_num){
    root->left = insert(root->left,num,rec,name);
}
else if(num>root->acc_num){
    root->right = insert(root->right,num,rec,name);
}
else if(num==root->acc_num){
printf("\n This account number is already used");
return root ;
}
return root ;
}
void show_acc(node*root){
if(root==NULL){
    return  ;
}
printf("\nAccount number : %d ",root->acc_num);
printf("\nName : %s ",root->name);
printf("\nRecord : %d \n",root->rec);
}

void show_nodes(node * root){
if(root==NULL){
    return ;
}
show_nodes(root->left) ;
show_acc(root);
show_nodes(root->right) ;
}
int total_accs(node *root){
static int i= 0  ;
if(root==NULL){
    return i;
}
root->left=total_accs(root->left) ;
i++;
root->left=total_accs(root->right) ;
return i;
}
node *search(node *root,int num){
if(root==NULL){
printf("\nNo such account exists\n");

    return root ;
}
if(num>root->acc_num){
    root->right=search(root->right,num) ;
}
else if(num<root->acc_num){
    root->left=search(root->left,num) ;
}
else if(num==root->acc_num){
printf("\nSearch result :\n");
show_acc(root);
return root ;
}
}
//deletion function
node * max_acc_num(node*root){
if(root->right==NULL){
    return root ;
}
root->right=max_acc_num(root->right) ;
}
node * del_node(node * root ,int num){
if(root==NULL){
    return root ;
}
else if(num>root->acc_num){
    root->right= del_node(root->right,num);
}
else if(num<root->acc_num){
    root->left= del_node(root->left,num);
}
else{
if(root->left==NULL&&root->right==NULL){
    free(root) ;
    root = NULL ;
}
else if(root->left==NULL){
    root=root->right ;
    root->right=del_node(root->right,num);
}
else if(root->right==NULL){
    root=root->left;
    root->left=del_node(root->left,num);
}
else {
node *temp = max_acc_num(root->left) ;
root->acc_num= temp->acc_num;
root->rec= temp->rec;
root->name = malloc(sizeof(char)*strlen(temp->name)+1);
strcpy(root->name,temp->name) ;
root->left = del_node(root->left,temp->acc_num);
}
return root ;
}
return root ;
}
//the following function deletes all nodes except for one so we del it in main func after execution
node *del_all(node *root){
if(root==NULL){
    return root ;
}
root->left=del_all(root->left);
root=del_node(root,root->acc_num);
if(root==NULL){

    return root ;
}
root->right=del_all(root->right);

return root ;
}



int main()
{
node *root =NULL;
root=insert(root,1,1553,"andrew");
root=insert(root,8,98111,"james");
root=insert(root,9,15156,"mark");

while(1){
int choice;
printf("***BANK SYSTEM***");
printf("\n\n1---insert an account\n2---search for an account\n3---show all accounts");
printf("\n4---delete an account\n5---delete all accounts\n6---exit\nChoice : ");
scanf("%d",&choice);
switch(choice){
case 1 :{
char  name[max] ;
int num ,rec;
printf("\nEnter the account number : ");
scanf("%d",&num);
printf("\nEnter the account record : ");
scanf("%d",&rec);
printf("\nEnter the account's holder name : ");
scanf("%s",name);
root=insert(root,num,rec,name);
}break;
case 2:{
int num;
printf("\nEnter the account number you are searching for : ");
scanf("%d",&num);
root=search(root,num) ;
}break;
case 3 :{
show_nodes(root);
}break;
case 4:{
int num;
printf("\nEnter the account number you are deleting : ");
scanf("%d",&num);
root=del_node(root,num) ;s
}break;
case 5:{
if(root==NULL){
    break;
}
root=del_all(root);
root=del_node(root,root->acc_num);
root=NULL;
//prev function leaves one account only
//that's how u delete it
}break;
case 6:{
printf("\nThanks for using the program (Andrew)\n");
system("pause\n");
exit(0);
}break;
default:{
printf("\nwrong input");
}break;
}

}



    return 0;
}
