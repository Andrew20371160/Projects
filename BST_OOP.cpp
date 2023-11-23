#include<iostream>
using namespace std ;
struct node{
int data ;
node * right ;
node * left ;
};
node * get_node(int d ){
    node * newnode = new node  ;
    newnode->data = d ;
    newnode->left = NULL ;
    newnode->right = NULL;
    return newnode ;
}
node * insert_node(int d ,node * root ){
if(root ==NULL){
    root  =get_node(d);
    return root ;
}
else if (d<=root->data){
    root ->left= insert_node(d,root->left) ;
}
else{
    root->right = insert_node(d,root->right);
}
}
void inorder(node * root ){
if(root ==NULL){
    return ;
}
else{
inorder(root->left );
cout<<root->data ;
inorder(root->right);
}
}
node * find_max(node * root ){

if(root->right==NULL){
    return root ;
}
find_max(root->right);
}
node * del_node(int d , node * root){
if(root ==NULL){
    return root ;
}
else if(d <root ->data){
    root->left = del_node(d,root->left);
}

else if(d >root ->data){
    root->right = del_node(d,root->right);
}
else{
if(root->left ==NULL&&root->right ==NULL){
    delete[]root;
    root = NULL ;
}
else if(root->left ==NULL){
    node* temp= root;
    root =root->right ;
    delete[]temp ;
}
else if(root->right ==NULL){
    node* temp= root;
    root =root->left;
    delete[]temp ;
}
else {
    node*temp = find_max(root->left) ;
    root ->data = temp->data;
    root->left= del_node(temp->data,root->left);
}

}
return root ;
}



class bst {
private:
node * root = NULL ;
public:
    bst(){
    root = NULL;
    }
    void insert_data(int d){
    root = insert_node(d,root);
    }
    void del_data(int d ){
    root = del_node(d,root);
    }
    void show_data(){
        cout<<endl;

    inorder(root);
}


};


int main(){
bst b1 ;
b1.insert_data(5);
b1.insert_data(2);
b1.insert_data(7);
b1.show_data();
b1.del_data(88);
b1.show_data();

return 0 ;
}
