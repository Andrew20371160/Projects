
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 20
struct date{
int day , month,year;
};
//numerical data
struct numerical{
int nat_num ;
struct date bdate;
};
//text data
struct text{
char *full_name ;
char * dad_name;
char  *mom_name;
char  *address ;
};
enum lifestatus {dead,alive};
//node structure
struct node{
struct numerical ndata ;
struct text tdata ;
enum lifestatus ls ;
struct node * right ;
struct node * left ;
};
// copy functions
void cpy_numer(struct numerical * dest , struct numerical * src ){
dest->nat_num = src->nat_num;
dest->bdate.day = src->bdate.day ;
dest->bdate.month=src->bdate.month ;
dest->bdate.year = src->bdate.year ;
}
void cpy_text(struct text * dest , struct text * src){
dest->address = (char*)malloc(sizeof(char)*(strlen(src->address)+1));
strcpy(dest->address,src->address) ;
dest->full_name = (char*)malloc(sizeof(char)*(strlen(src->full_name)+1));
strcpy(dest->full_name,src->full_name) ;
dest->mom_name = (char*)malloc(sizeof(char)*(strlen(src->mom_name)+1));
strcpy(dest->mom_name,src->mom_name) ;
dest->dad_name = (char*)malloc(sizeof(char)*(strlen(src->dad_name)+1));
strcpy(dest->dad_name,src->dad_name) ;
}
//occupy data for root function
struct node * get_data(struct numerical num_src,struct text text_src){
struct node * root = malloc(sizeof(struct node ));
cpy_numer(&root->ndata,&num_src) ;
cpy_text(&root->tdata,&text_src) ;
root->ls =alive;
root->right = NULL ;
root->left = NULL ;
return root ;
}
//insert func
struct node * insert(struct node * root ,struct numerical ndata , struct text tdata ){
if(root ==NULL){
    root = get_data(ndata,tdata) ;
        return root ;
}
else if(ndata.nat_num==root->ndata.nat_num){
printf("\nNational number already exist\n") ;
return root ;
}

else if(ndata.nat_num>root->ndata.nat_num){
    root->right = insert(root->right,ndata,tdata);
}

else if(ndata.nat_num<root->ndata.nat_num){
    root->left = insert(root->left,ndata,tdata);
}
return root ;
};
//search func
struct node * search(int nat_num,struct node *root ){
if(root ==NULL){
    printf("\nNo such national number\n");
    return root ;
}
else if(nat_num==root->ndata.nat_num){
printf("\nSearch result:\n");
printf("\nNational Number : %d",root->ndata.nat_num);
printf("\nFull Name: %s %s ",root->tdata.full_name,root->tdata.dad_name);
printf("\nMother's Name : %s",root->tdata.mom_name);
printf("\nDate of birth : %d/%d/%d",root->ndata.bdate.day,root->ndata.bdate.month,root->ndata.bdate.year);
printf("\nAddress : %s",root->tdata.address);
printf("\nLife status : ");
printf((root->ls)?"Alive\n":"Dead\n");
return root ;
}
else if (nat_num>root->ndata.nat_num){
    root->right = search(nat_num,root->right) ;
}
else if (nat_num<root->ndata.nat_num){
    root->left = search(nat_num,root->left) ;
}
return root ;
}

void insert_data_via_user(struct node ** root ){
struct numerical ndata  ;
struct text tdata  ;
//getting Numerical data
printf("Enter national number : ");
scanf("%d",&ndata.nat_num) ;
printf("Enter date of birth as follows(day month year)(hit space-bar after each number ): ");
scanf("%d",&ndata.bdate.day);
scanf("%d",&ndata.bdate.month);
scanf("%d",&ndata.bdate.year) ;
//getting text data
printf("\nEnter first Name : ");
tdata.full_name =(char*)malloc(sizeof(char)*max);
scanf("%s",tdata.full_name) ;
printf("\nEnter last Name : ");
tdata.dad_name =(char*)malloc(sizeof(char)*max);
scanf("%s",tdata.dad_name) ;
printf("\nEnter Mother's Name : ");
tdata.mom_name =(char*)malloc(sizeof(char)*max);
scanf("%s",tdata.mom_name) ;
printf("\nEnter address : ");
tdata.address =(char*)malloc(sizeof(char)*max);
scanf("%s",tdata.address) ;
(*root) = insert(*root,ndata,tdata) ;
}
struct node * update(struct node *root,int num ){
if(root ==NULL){
    printf("\nNo such national number\n");
    return root ;
}
else if(num<root->ndata.nat_num){
    root->left=update(root->left,num);
}
else if(num>root->ndata.nat_num){
    root->right=update(root->right,num);
}
else{
int choice;
printf("\n1---Update life status\n2---Update address\n3---Update first name"
"\n4---Update last name\n5---Update mother's name\nChoice : ");
scanf("%d",&choice);
switch(choice){
case 1 : root->ls =dead ;break;
case 2 :{
root->tdata.address = malloc(sizeof(char)*max) ;
scanf("%s",root->tdata.address);
}break;
case 3 :{
root->tdata.full_name = malloc(sizeof(char)*max) ;
scanf("%s",root->tdata.full_name);
}break;
case 4 :{
root->tdata.dad_name = malloc(sizeof(char)*max) ;
scanf("%s",root->tdata.dad_name);
}break;

case 5 :{
root->tdata.mom_name = malloc(sizeof(char)*max) ;
scanf("%s",root->tdata.mom_name);
}break;
default:{
printf("\nWront input\n");
}break ;
}

return root ;
}
return root ;
}
int main(){
struct node * root = NULL ;
while(1){
int choice;
printf("\n***Civil Record***\n");
printf("\n1---Insert a person\n2---Search for a person\n3---Update a person's data\n"
"4---exit\nChoice : "
);
scanf("%d",&choice);
switch(choice){
case 1:insert_data_via_user(&root);break ;
case 2:{
int num ;
printf("\nEnter the national number\n");
scanf("%d",&num);
root=search(num,root);
}break;
case 3:{
int num ;
printf("\nEnter the national number\n");
scanf("%d",&num);
root =search(num,root);
root=update(root,num);
}break;
case 4:{
printf("\nThanks for using the system :)(andrew)\n");
system("pause\n");
exit(0);
}
}



}



return 0 ;
}
