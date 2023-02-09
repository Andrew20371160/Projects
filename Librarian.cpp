#include <iostream>
#include<cstring>
using namespace std;
struct node{
int book_num ;
int price ;
char *book_name;
char * author ;
node* left ;
node * right  ;
};
node * action = NULL ;
node * comedy = NULL ;
node * horror = NULL ;
node * romance = NULL ;

node * add_at_empty(char * bname,char*author ,int bnum ,int price){
node * root = new node ;
root->price =price ;
root->book_num = bnum ;
root->book_name = new char[strlen(bname)+1] ;
strcpy(root->book_name,bname) ;
root->author = new char[strlen(author)+1];
strcpy(root->author,author);
root->right = NULL ;
root->left =NULL ;
return root ;
}
node *insert_node(node * root ,char * bname,char*author ,int bnum ,int price){
if(root==NULL){
    root =add_at_empty( bname,author , bnum , price) ;
}
else if (bnum <root->book_num){
    root->left =insert_node(root->left , bname,author , bnum , price) ;
}
else {
    root->right = insert_node(root->right , bname,author , bnum , price) ;
}
return root ;
}
void search_node(int bnum ,node*root ){
if(root ==NULL){
    return ;
}
else if (bnum ==root->book_num){
cout<<endl<<"book name : "<<root->book_name ;
cout<<endl<<"book's author : "<<root->author ;
cout<<endl<<"book's number : "<<root->book_num ;
cout<<endl<<"book's price : "<<root->price ;
return ;
}
else if(bnum<root->book_num){
    search_node(bnum,root->left) ;
}
else {
 search_node(bnum,root->right) ;
}

}
void  add_book_via_user(struct node ** root ){
char bname[30] ; char author[30] ; int bnum ; int price;
cout<<"\n enter book's name (note when you fininsh typing the book's name type '&' in the end then press enter same for book's author aswell .) :"<<endl;
cin.getline(bname,30,'&') ;
cout<<endl<<"\n enter author's name :";
cin.getline(author,30,'&');
cout<<endl<<"\n enter book's number :";
cin>>bnum ;
cout<<"\n enter book's price : ";
cin>>price ;
(*root) =insert_node((*root),bname,author,bnum,price) ;


};
void category_books_numbers(struct node * root){
if(root==NULL){
    return  ;
}
category_books_numbers(root->left) ;
cout<<endl<<"book name : "<<root->book_name ;
cout<<"book's number : "<<root->book_num <<endl;
category_books_numbers(root->right ) ;


}
void library();
void inorder(node *root) ;
void adjust(node ** root ){
int choice ;
cout<<"\n 1-insert a book ";
cout<<"\n 2-search a book ";
cout<<"\n 3-show books of the category ";
cout<<"\n 4-quit ";
cout<<"\n 5-back to main menu ";
cin>>choice ;
switch(choice){
case 1 : {
    add_book_via_user(root);
}break;

case 2:{
category_books_numbers(*root) ;
int bnum ;
cout<<endl<<"enter book's number"<<endl;
cin>>bnum ;
search_node(bnum,(*root));
}break;
case 3: inorder(*root) ; break ;

case 4 : exit(0);
default :cout<<"\n wrong choice"; break;

case 5:library() ; break;
}
library() ;

}


void inorder(node * root){
if(root==NULL){
    return  ;
}
inorder(root->left) ;
cout<<endl<<"book name : "<<root->book_name ;
cout<<endl<<"book's author : "<<root->author ;
cout<<endl<<"book's number : "<<root->book_num ;
cout<<endl<<"book's price : "<<root->price ;
inorder(root->right ) ;
}
void library(){
int cat ;
cout<<"\n enter the category of the book \n";
cout<<"\n 1-action \n 2-horror \n 3-comedy \n 4-romance \n 5-quit";
cin>>cat ;
switch(cat){
case 1 : adjust(&action) ;break ;
case 2 :  adjust(&horror) ;break ;
case 3 : adjust(&comedy) ;break ;
case 4 :  adjust(&romance) ;break ;
case 5 :exit(0) ;
default :cout<<"wrong input "; library() ;


}


}



int main()
{
action = insert_node(action,"max payne","mark",1,3)  ;
action = insert_node(action,"tomb raider","james",2,5)  ;
action = insert_node(action,"crank","stathom",3,9)  ;
horror = insert_node(horror,"the ring","belly",4,6) ;
horror = insert_node(horror,"ring the bell","kermet",5,9) ;
horror = insert_node(horror,"annabele origins","disney",3,66) ;
comedy = insert_node(comedy,"the big short","disney",7,66) ;
comedy = insert_node(comedy,"the wolf of wall street","harry potter",8,69) ;
comedy = insert_node(comedy,"money in the bank","wwe raw",8,2) ;
comedy = insert_node(comedy,"the other guys","good team",9,20) ;
romance = insert_node(romance,"me before you","abdelbasset hammoda",10,400) ;
library();





    return 0;
}
