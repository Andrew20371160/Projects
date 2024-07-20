//includes
#include <iostream>
#include <cstring>
using namespace std;
//Macros
enum library_categories {action=1,comedy,horror,romance} ;
//user defined data types
//Book node structure
struct node{
int book_num ;
int price ;
char *book_name;
char * author ;
node* left ;
node * right  ;
};

//library class
//abstracted from the user via library_controller class
class library{
    private :
    //root of the BST
    node* root ;
    //functions ineteracting with the BST are abstracted from the user
    node * add_at_empty(char * bname,char*author ,int bnum ,int price);
    node * insert_node(node*root ,char * bname,char*author ,int bnum ,int price);
    node * search_node(int bnum ,node*root );
    node * delete_node(int bnum ,node*root );
    void delete_all(node** root);
    public:
    //constructor
    library(void){
        root = NULL ;
    };
    //get root of the BST
    node * get_root(void){
        return root ;
    }
        //functions ineteracting with the BST is abstracted from the user
        //get insertion functionality
        void get_insertion_fcn(char * bname,char*author ,int bnum ,int price){
            root = insert_node(root , bname,author , bnum , price) ;
        }
        //get search functionality
        void get_search_fcn(int bnum){
            node * book_ptr = search_node(bnum,root) ;
            display_node(book_ptr) ;
        }
        //get delete functionality
        void get_delete_fcn(int bnum){
            root = delete_node(bnum,root) ;
        }
        void get_delete_category_fcn(void){
            delete_all(&root) ;
        }
        void get_display_fcn(void){
        if(root){
            inorder(root) ;
        }
        }
        void display_node(node * book_ptr) ;
        void category_books_numbers(node * root);
        void inorder(node * root);
};

//get memory for a new node
node * library :: add_at_empty(char * bname,char*author ,int bnum ,int price){
node * new_node = new node ;
new_node->price =price ;
new_node->book_num = bnum ;
new_node->book_name = new char[strlen(bname)+1] ;
strcpy(new_node->book_name,bname) ;
new_node->author = new char[strlen(author)+1];
strcpy(new_node->author,author);
new_node->right = NULL ;
new_node->left =NULL ;
return new_node ;
}

//insert a new node in the BST
node *library:: insert_node(node * root ,char * bname,char*author ,int bnum ,int price){
if(root==NULL){
    root =add_at_empty( bname,author , bnum , price) ;
    return root ;
}
else if(bnum==root->book_num){
cout<<endl<<"\nBook number already exists\n";
return root ;
}
else if (bnum <root->book_num){
    root->left =insert_node(root->left , bname,author , bnum , price) ;
}
else if(bnum>root->book_num) {
    root->right = insert_node(root->right , bname,author , bnum , price) ;
}
return root ;
}

//search for a book in the BST
node * library :: search_node(int bnum ,node*root ){
if(root ==NULL){
    return root  ;
}
else if (bnum ==root->book_num){
return root ;
}
else if(bnum<root->book_num){
    return search_node(bnum,root->left) ;
}
else {
 return search_node(bnum,root->right) ;
}
}

void library :: display_node(node * book_ptr) {
if(book_ptr){
cout<<endl<<"book name : "<<book_ptr->book_name ;
cout<<endl<<"book's author : "<<book_ptr->author ;
cout<<endl<<"book's number : "<<book_ptr->book_num ;
cout<<endl<<"book's price : "<<book_ptr->price ;
}
else{
    cout<<"\n book not found \n";
}
}
//delete a node from the BST
node * library :: delete_node(int bnum ,node*root ){
    if(root==NULL){
        return root ;
    }
    else if(bnum>root->book_num){
        root->right = delete_node(bnum,root->right) ;
    }
    else if(bnum<root->book_num){
        root->left = delete_node(bnum,root->left) ;
    }
    //found the node to be deleted
    else{
        if(root->left ==NULL&&root->right==NULL){
            delete  root ;
            return NULL ;
        }
        if(root->left==NULL){
            node * temp = root->right ;
            delete root ;
            return temp ;
        }
        else if(root->right==NULL){
            node * temp = root->left ;
            delete root ;
            return temp ;
        }
        else{
            //find node with minimum value in the right subtree
            node * temp = root->right ;
            while(temp->left!=NULL){
                temp = temp->left ;
            }
            //copy the data of the minimum node to the node to be deleted
            root->book_num = temp->book_num ;
            root->price = temp->price ;
            //delete the allocated memory of book name and author of the node to be deleted
            delete[] root->book_name;
            delete[] root->author;
            //allocate memory for the new book name and author
            root->book_name = new char[strlen(temp->book_name) + 1];
            root->author = new char[strlen(temp->author) + 1];
            //copy the book name and author
            strcpy(root->book_name, temp->book_name);
            strcpy(root->author, temp->author);
            //delete the minimum node
            root->right = delete_node(temp->book_num,root->right) ;
        }
    }
        return root  ;
}
void library :: delete_all(node** root) {
    if (*root != NULL) {
        delete_all(&(*root)->left);
        delete_all(&(*root)->right);
        delete[] (*root)->book_name;
        delete[] (*root)->author;
        delete (*root);
    }
    (*root) = NULL ;
}
//inorder traversal of the BST
void library :: inorder(node * root){
if(root==NULL){
    return  ;
}
inorder(root->left) ;
display_node(root) ;
inorder(root->right ) ;
}
//display all the books of a particular category
void library :: category_books_numbers(struct node * root){
if(root==NULL){
    return  ;
}
category_books_numbers(root->left) ;
cout<<endl<<"book name : "<<root->book_name ;
cout<<" book's number : "<<root->book_num <<endl;
category_books_numbers(root->right ) ;
}

//get memory for a new node
class library_controller : public library{
public:
//functions interacting with the user
void add_book_via_user(void);
void search_book_via_user(void);
void delete_book_via_user(void);
void delete_category_via_user(void) ;
};
//add a book to the BST (abstarction for the user)
void library_controller:: add_book_via_user(void){
char bname[30] ;
char author[30] ;
int bnum ; int price;
cout<<"\n enter book's name (note when you fininsh typing the book's name type '&' in the end then press enter same for book's author aswell .) :"<<endl;
cin.getline(bname,30,'&') ;
cin.ignore();
cout<<endl<<"\n enter author's name :";
cin.getline(author,30,'&');
cin.ignore();
cout<<endl<<"\n enter book's number :";
cin>>bnum ;
cin.ignore();
cout<<"\n enter book's price : ";
cin>>price ;
cin.ignore();
//get insertion functionality
get_insertion_fcn(bname,author,bnum,price) ;
};

//search for a book in the BST (abstarction from the user)
void library_controller:: search_book_via_user(void){
int bnum ;
cout<<"\n enter book's number :";
cin>>bnum ;
cin.ignore();
//get search functionality
get_search_fcn(bnum);
}

//delete a book from the BST (abstarction from the user)
void library_controller:: delete_book_via_user(void){
int bnum ;
cout<<"\n enter book's number :";
cin>>bnum ;
cin.ignore();
//get delete functionality
get_delete_fcn(bnum);
}
void library_controller::delete_category_via_user(void) {
if(get_root()){
    get_delete_category_fcn();
}
}
int main()
{
//create 4 categories of books
//4 BSTs for each category
library_controller categories[4] ;
//menu for the user
while(1){
//get the category choice from the user
//get the operation choice from the user
int cat_choice = 0,choice = 0;
cout<<endl<<"1. action"<<endl<<"2. comedy"<<endl<<"3. horror"<<endl<<"4. romance"<<endl<<"5. exit"<<endl;
cin>>cat_choice ;
cin.ignore();
//check if the category choice is valid
if(cat_choice>=action&&cat_choice<=romance){
//get the operation choice from the user
//interact with the user via library_controller class untill he exits the category
    while(choice!=6){
    cout<<endl<<"1. add book"<<endl<<"2. search book"<<endl<<"3. delete book"<<endl<<"4. display all books"<<"\n5. empty the category"<<endl<<"6. exit"<<endl;
    cin>>choice ;
    cin.ignore();
    switch (choice){
    case 1:{
        //add a book to the BST (abstarction for the user)
        categories[cat_choice-1].add_book_via_user() ;
    }break;
    case 2:{
        //search for a book in the BST (abstarction from the user)
        categories[cat_choice-1].search_book_via_user() ;
    }break;
    case 3:{
        //delete a book from the BST (abstarction from the user)
        categories[cat_choice-1].delete_book_via_user() ;
    }break;
    case 4:{
        //display all the books of a particular category
        categories[cat_choice-1].get_display_fcn() ;
    }break;
    case 5:{
        //delete all the books of a particular category
        categories[cat_choice-1].get_delete_category_fcn() ;
    }break;
    case 6:{
        break ;
    }
    default:{
        cout<<endl<<"invalid choice"<<endl;
    }
    }
}
}
else if(cat_choice==5){
//delete all the books of all the categories
for(int i = 0 ; i<4 ; i++){
    categories[i].get_delete_category_fcn() ;
}
cout<<endl<<"exiting"<<endl;
cout<<endl<<"thank you for using the software (Andrew :) )"<<endl;
system("pause") ;
exit(0) ;
}
else{
    cout<<endl<<"invalid choice"<<endl;
}
}
    return 0;
}
