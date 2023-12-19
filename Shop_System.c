#include <stdio.h>
#include <stdlib.h>
#include<string.h>
struct node {
int product_num ;
char * product_name;
int price ;
struct node * right ;
struct node * left  ;

};
struct node * get_empty(int pnum,int price,char * str ){
struct node * root = malloc(sizeof (struct node )) ;
root ->price = price ;
root->product_num = pnum ;
root->product_name =(char*) malloc(sizeof (strlen(str)+1))  ;
strcpy(root->product_name,str)  ;
root->right = NULL  ;
root->left =NULL;
return root ;
};

struct node *insert_product(struct node *root,int pnum ,int price ,char *str ){
if(root ==NULL){
    root = get_empty(pnum,price,str)  ;
}
else if(pnum <root->product_num){
    root->left =insert_product(root->left ,pnum,price,str) ;
}
else {
    root->right =insert_product(root->right ,pnum,price,str) ;
}
return root ;
};
void search(int pnum,struct node *root ){
if(root==NULL){
    printf("\n product not found") ;
    return ;
}
else if (pnum<root->product_num ){
    search(pnum,root->left) ;
}
else if(pnum>root->product_num){
    search(pnum,root->right) ;
}
else {
    printf("\n product number :%d\n product name :%s\n product price : %d\n ",root->product_num,root->product_name,root->price);
}

}
struct node * find_min(struct node *root ){
if(root ==NULL){
    return root  ;
}
else if(root->left ==NULL){
    return root ;
}
else {
    return find_min(root->left ) ;
}

};
struct node * del_product(int pnum,struct node * root ){
if(root ==NULL){
    return root ;
}
else if (pnum <root->product_num) {
    root ->left =del_product(pnum,root->left) ;

}
else if (pnum >root->product_num) {
    root ->right  =del_product(pnum,root->right) ;
}
else {
if(root ->left ==NULL && root->right ==NULL){
    free(root) ;
    root =NULL;
}
else if(root ->left ==NULL){
    struct node *temp = root ;
    root =root->right  ;
    free(temp) ;
}
else if(root ->right ==NULL){
    struct node *temp = root ;
    root =root->left   ;
    free(temp) ;
}
else {
struct node *temp = find_min(root->right ) ;
root ->product_num = temp->product_num ;
root ->product_name = temp->product_name ;
root ->price = temp->price  ;
del_product(temp->product_num,root->right );
}

}
return root ;
};


void shop(struct node *root ){
while(1){
int choice ;
printf("\n 1-insert a new product ");
printf("\n 2-search  ");
printf("\n 3-delete a certain product ");
printf("\n 4-exit ");
scanf("%d",&choice);
switch(choice){
case 1: {int pnum,price;char str[30]; printf("\n enter product number :\n") ;scanf("%d",&pnum) ;
printf(" enter product name :\n ");scanf("%s",str);
 printf(" enter product price :\n");scanf("%d",&price);
root = insert_product(root,pnum,price,str) ; break;
}
case 2 :{ int pnum  ;printf("\n enter product number :");scanf("%d",&pnum);
search(pnum,root)  ;
break ;
}
case 3:{int pnum ; printf("\n enter product name :");scanf("%d",&pnum) ; root =del_product(pnum,root); break ;}

case 4:exit(0) ;
default : printf("\n wrong choice "); shop(root) ;break;
}
}
}

int main()
{
struct node * product = NULL ;
shop(product ) ;

    return 0;
}
