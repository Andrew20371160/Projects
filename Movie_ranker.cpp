
#include <iostream>
#include<cstring>
using namespace std;
struct node{
char * movie_name ;
char * director ;
float rating ;
int year  ;
int views ;
node * right ,*left ;
};
#define by_rating 1
#define by_views 2 
#define by_year 3
node * get_node(int year ,int views,float rating,char*movie_name,char * director_name ){
node * root = new node ;
root ->year=  year;
root ->views= views;
root->rating = rating ;
root->movie_name = new char[strlen(movie_name)+1];
strcpy(root->movie_name,movie_name);
root->director= new char[strlen(director_name)+1];
strcpy(root->director,director_name);
root->left = NULL ;
root->right = NULL ;
return root ;
}
node * insert_node(node * root ,int year ,int views,float rating,char*movie_name,char * director_name,int arrange/*(arrange values 1 : rating , 2: views , 3:year)*/){
if(root==NULL){
    root = get_node( year , views, rating,movie_name, director_name );
    return root ;
}

else if(arrange==by_rating){
    if(rating<=root->rating){
        root->left = insert_node(root->left,year,views,rating,movie_name,director_name,arrange);
    }
    else if(rating>root->rating){
        root->right = insert_node(root->right,year,views,rating,movie_name,director_name,arrange);

    }
}
else if(arrange==by_views){
    if(views<=root->views){
        root->left = insert_node(root->left,year,views,rating,movie_name,director_name,arrange);
    }
    else if(views>root->views){
        root->right = insert_node(root->right,year,views,rating,movie_name,director_name,arrange);

    }
}
else if(arrange==by_year){
    if(year<=root->year){
        root->left = insert_node(root->left,year,views,rating,movie_name,director_name,arrange);
    }
    else if(year>root->year){
        root->right = insert_node(root->right,year,views,rating,movie_name,director_name,arrange);
}
}
//default is by_rating 
else{
     if(rating<=root->rating){
        root->left = insert_node(root->left,year,views,rating,movie_name,director_name,arrange);
    }
    else if(rating>root->rating){
        root->right = insert_node(root->right,year,views,rating,movie_name,director_name,arrange);

    }
}
}
void inorder(node * root){
if(root==NULL){
    return ;
}
inorder(root->left) ;
cout<<endl;
cout<<endl<<"Movie's name : "<<root->movie_name ;
cout<<endl<<"Director : "<<root->director;
cout<<endl<<"Rating : "<<root->rating;
cout<<endl<<"Total views : "<<root->views ;
cout<<endl<<"Year of production : "<<root->year;
inorder(root->right);
}
void reverse_order(node * root){
if(root==NULL){
    return ;
}
reverse_order(root->right) ;
cout<<endl<<"Movie's name : "<<root->movie_name ;
cout<<endl<<"Director : "<<root->director;
cout<<endl<<"Rating : "<<root->rating;
cout<<endl<<"Total views : "<<root->views ;
cout<<endl<<"Year of production : "<<root->year;
reverse_order(root->left);
}
//create a new bst sorted in different arrangement 
void copy_tree(node ** dest,node*src,int arrange){
if(src==NULL){
    return ;
}
//inorder traversal of the older BST
copy_tree(dest,src->left,arrange);
//Insert into the new bst based on user's needs using @arrange paramter
(*dest)= insert_node(*dest,src->year,src->views,src->rating,src->movie_name,src->director,arrange);
copy_tree(dest,src->right,arrange);

}
node*delete_a_rate(node*root){
if(root==NULL){
    return NULL ;
}
delete_a_rate(root->left) ;
delete[]root ;
delete_a_rate(root->right);
}
void incre_or_dec(node *root,int choice){
switch(choice){
case 1:reverse_order(root);break;
case 2:inorder(root);break;
default:{cout<<endl<<"by default : "<<endl;
reverse_order(root);
}break;

}
}
int main()
{
node * by_views  =NULL;
node * by_rating=NULL;
node * by_year =NULL;
int arrange ;
int choice;
by_rating = insert_node(by_rating,2001,15500,4.3,"the other guys","james?",1);
by_rating = insert_node(by_rating,2021,140532,2.2,"the big short","mike?",1);
by_rating = insert_node(by_rating,2006,1589,3.7,"the wolf of wall street ","me?",1);
by_rating = insert_node(by_rating,1970,136657,1.1,"blue elephant ","you?",1);
by_rating = insert_node(by_rating,2020,79552,0.5,"interstellar ","the cool guy who made batman aswell?",1);
by_rating = insert_node(by_rating,1980,115793,4.7,"the dark knight","clark?",1);
by_rating = insert_node(by_rating,1990,45697,4.9,"joker ","bruce wayne?",1);
by_rating = insert_node(by_rating,2022,202159,4.8,"Man of steel ","lambart?",1);
by_rating = insert_node(by_rating,2017,17,1.5,"elbeeda welhagar","messi?",1);
by_rating = insert_node(by_rating,2013,1556,3.9,"elkitkat","ronaldo?",1);
while(1){
cout<<endl<<"Rate by : 1---Rating\n          2---views\n          3---year\n          4---quit\n";
cin>>arrange ;
switch(arrange){
case 1:{
cout<<"\nDo you want decreasing or increasing order?(1/2)";
cin>>choice ;
incre_or_dec(by_rating,choice);
}break ;
case 2 :{
cout<<"\nDo you want decreasing or increasing order?(1/2)";
cin>>choice ;
copy_tree(&by_views,by_rating,arrange);
incre_or_dec(by_views,choice);
by_views =delete_a_rate(by_views);
}break;
case 3 :{
cout<<"\nDo you want decreasing or increasing order?(1/2)";
cin>>choice ;
copy_tree(&by_year,by_rating,arrange);
incre_or_dec(by_year,choice);
by_year =delete_a_rate(by_year);
}break;

case 4:{
cout<<endl<<"Software made by :Andrew Karam\n";
system("pause");
exit(0);
}
}

}
  return 0;
}
