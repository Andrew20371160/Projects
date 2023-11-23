#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//NODE STRUCTURE
struct node {
int book_number ;
int price ;
char *book_name ;
char *author  ;
struct node * left ;
struct node * right ;
};

struct node * action = NULL ;
struct node * horror = NULL ;
struct node *comedy =NULL ;
struct node *romance = NULL ;
//get memory for new book
struct node * get_empty(int bnum,int price ,char * author,char *bname){
struct node * book = malloc(sizeof(struct node )) ;
book->book_number = bnum ;
book->price = price ;
book->book_name = (char *) malloc(sizeof(char)*(strlen(bname)+1)) ;
strcpy(book->book_name,bname) ;
book->author = (char *) malloc(sizeof(char)*(strlen(author)+1)) ;
strcpy(book->author ,author ) ;
book->right = NULL ;
book->left = NULL;
return book ;
};
//Insertion function
struct node * insert(struct node * root ,int bnum ,int price ,char * author,char*bname ){
if(root ==NULL){
    root =get_empty(bnum,price,author,bname ) ;
    return root ;
}
else if(bnum<root->book_number){
root->left =insert(root->left ,bnum,price,author,bname) ;
}
else{
root->right =insert(root->right,bnum,price,author,bname) ;
}
return root ;
};
void choose_category_for_insertion(int cat,int bnum,int price ,char * author,char *bname ){
switch(cat){
case 1 :action =insert(action,bnum,price,author,bname); break ;
case 2 :romance =insert(romance,bnum,price,author,bname); break ;
case 3 :horror =insert(horror,bnum,price,author,bname); break ;
case 4 :comedy =insert(comedy,bnum,price,author,bname); break ;
default : printf("\n wrong choice") ;return ;
}
}
//search function
void search_book(int bnum,struct node*root) ;
void bname_bnum(struct node*) ;
void choose_category_forsearch(int cat ){
int bnum;
switch(cat){
case 1 :{
bname_bnum(action) ;
printf("\nEnter book's number : ");
scanf("%d",&bnum) ;
search_book(bnum,action);
}break ;
case 2 :{
bname_bnum(romance) ;
printf("\nEnter book's number : ");
scanf("%d",&bnum) ;
search_book(bnum,romance);
}break ;
case 3 :{
bname_bnum(horror) ;
printf("\nEnter book's number : ");
scanf("%d",&bnum) ;
search_book(bnum,horror);
}break ;
case 4 :{
bname_bnum(comedy) ;
printf("\nEnter book's number : ");
scanf("%d",&bnum) ;
search_book(bnum,comedy);
}break ;
default : printf("\n wrong choice") ;return;
}
}
void search_book (int bnum,struct node *root ){
if(root ==NULL){
    printf("\n Book not found") ;
    return ;
}
else if (bnum<root->book_number){
   search_book(bnum,root->left) ;
}

else if (bnum>root->book_number){
     search_book(bnum,root->right) ;
}
else if(bnum==root->book_number){
printf("\n Book name :%s\n",root->book_name) ;
printf("\n Book author:%s\n",root->author) ;
printf("\n Book number:%d\n",root->book_number) ;
printf("\n Book price :%d\n",root->price) ;
return;
}
}
//display content of a category
void inorder_category(struct node * root ){
if(root==NULL){
    return ;
}
inorder_category(root->left) ;
{printf("\n Book name :%s\n",root->book_name) ;
printf("\n Book author:%s\n",root->author) ;
printf("\n Book number:%d\n",root->book_number) ;
printf("\n Book price :%d\n",root->price) ;
}
inorder_category(root->right) ;
}
//shows books names and their serial numbers
void bname_bnum(struct node * root){
if(root==NULL){
    return ;
}
bname_bnum(root->left) ;
{
printf("\n Book name :%s\n",root->book_name) ;
printf("\n Book number:%d\n",root->book_number) ;
}
bname_bnum(root->right) ;
}



int main(){

action =insert(action,1,10,"james","the killer");
action = insert(action,2,15,"mark","the shadow of a spy");
action = insert(action,3,10,"andrew","demon in you");
romance = insert(romance,4,10,"ahmed saad","ktab hyany");
romance = insert(romance,5,15,"abdelbaset hamoda","bosy kat");
romance = insert(romance,6,20,"hamdy zrzor ","kitkat");
horror = insert(horror,7,10,"sayd","the the") ;
horror = insert(horror,8,10,"lambart ","the 5 *6 !=30") ;
comedy = insert(comedy,9,10,"abdelbasset hamoda ","hya elodnya")  ;
comedy = insert(comedy,10,10,"abdelbasset 2tota","tona now ya b8law")  ;
comedy = insert(comedy,11,10,"andrew abdelbaset hamoda", "el e3agz weltfser fe bet elkber") ;
while(1){
int cat,choice ;
printf("\n 1-insert a book into the library\n") ;
printf("\n 2-search for a book in the library \n") ;
printf("\n 3-show category books\n") ;
printf("\n 4-quit\n") ;
scanf("%d",&choice);
switch(choice){
case 1 :{
int bnum, price ;
char  bname[15] ; char  author[15];
printf("\n Book name :") ;
scanf("%s",bname) ;
printf("\n Book author ") ;
scanf("%s",author) ;
printf("\n Book number ") ;
scanf("%d",&bnum) ;
printf("\n Book price ") ;
scanf("%d",&price) ;
printf(" \n please choose the category :\n 1-action\n 2-romance\n 3-horror\n 4-comedy \n ");
scanf("%d",&cat) ;
choose_category_for_insertion(cat,bnum,price,author,bname) ;
}break;
case 2 :{
printf(" \n please choose the category :\n 1-action\n 2-romance\n 3-horror\n 4-comedy \n ");
scanf("%d",&cat) ;
choose_category_forsearch(cat) ;
}break ;
case 3:{
printf(" \n please choose the category :\n 1-action\n 2-romance\n 3-horror\n 4-comedy \n ");
scanf("%d",&cat) ;
switch(cat){
case 1 :inorder_category(action); break ;
case 2 :inorder_category(romance); break ;
case 3 :inorder_category(horror) ;break ;
case 4 :inorder_category(comedy); break ;
default : printf("\n wrong choice") ; break ;
}
}break;
case (4): exit(0) ;
}

}

return  0;

}
