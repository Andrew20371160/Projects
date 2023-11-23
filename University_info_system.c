#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define max 40
//student (node) structure definition
typedef struct {
int id,year;
float gpa;
char * name ;
char * lname ;
char * program ;
struct node * left ;
struct node *right ;
}node;
//allocate memory for new student
node * get_stud(int id,int year,float gpa,char *name,char*lname,char*program){
node * new_stud = malloc(sizeof(node));
new_stud->id=id ;
new_stud->year=year ;
new_stud->gpa=gpa ;
new_stud->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
strcpy(new_stud->name,name);
new_stud->lname = (char*)malloc(sizeof(char)*(strlen(lname)+1));
strcpy(new_stud->lname,lname);
new_stud->program = (char*)malloc(sizeof(char)*(strlen(program)+1));
strcpy(new_stud->program,program);
new_stud->left= NULL ;
new_stud->right= NULL ;
return new_stud ;
}
//Insertion function
node*insert(node*root,int id,int year,float gpa,char *name,char*lname,char*program){
if(root==NULL){
    root=get_stud(id,year,gpa,name,lname,program);
}
else if(id>root->id){
    root->right = insert(root->right,id,year,gpa,name,lname,program);
}
else if(id<root->id){
    root->left = insert(root->left,id,year,gpa,name,lname,program);
}
else if(id==root->id){
printf("\nCan't have two or more students of same ID\n");
 return root ;
}
    return root ;
}
//get data from user then insert it into the bst
void insert_via_user(node**root){
char name[max],lname[max],program[max];
int id,year;
float gpa;
printf("\nEnter the first name : ");
scanf("%s",name) ;
fflush(stdin);
printf("\nEnter the last name : ");
scanf("%s",lname) ;
fflush(stdin);
printf("\nEnter the program : ");
scanf("%s",program) ;
fflush(stdin);
printf("\nEnter the ID : ");
scanf("%d",&id) ;
printf("\nEnter the College year : ");
scanf("%d",&year) ;
if(year!=1){
printf("\nEnter previous year GPA : ");
scanf("%s",program) ;
}
else {
    gpa = 0.0;
}
*root=insert(*root,id,year,gpa,name,lname,program);
}
//Show data function
void show(node*root){
if(root==NULL){
    return ;
}
printf("\nStudent's ID : %d",root->id);
printf("\nStudent's Name : %s",root->name);
printf("\nStudent's last name : %s",root->lname);
printf("\nProgram : %s",root->program);
printf("\nStudent's GPA : %.2f",root->gpa);
printf("\nCollege year : %d\n",root->year);
}
//Search functions
node * find_id(node*root,int id){
if(root==NULL){
    return root ;
}
else if(id<root->id){
    root->left=find_id(root->left,id);
}
else if(id>root->id){
    root->right=find_id(root->right,id);
}
else if(id==root->id){
printf("\n----Search Results----\n") ;
show(root);
return root ;
}
return root ;
}
//Search by name
node*find_name(node*root,char * name){
if(root==NULL){
    return root ;
}
root->left = find_name(root->left,name);
//here is an algorithm that if the researcher wants to search with a part of a student's name
//It shows all possible matches
char flag = 0;
int i = 0 ;
while(*(name+i)&&*(root->name+i)){
if(*(name+i)!=*(root->name+i)){
flag= 1;
break ;
}
i++;
}
if((*(name+i)=='\0')&&flag==0){
show(root);
}
root->right = find_name(root->right,name);
return root ;
}

void how_search(node **root){
int choice ;
printf("\n1---Search by ID\n2---Search by name\nChoice : ");
scanf("%d",&choice);
switch(choice){
case 1 : {
int id ;
printf("\nEnter the ID : ");
scanf("%d",&id);
find_id(*root,id);
}break;
case 2 :{
char name[max] ;
printf("Enter the first name or part of it : ");
scanf("%s",name);
fflush(stdin);
find_name(*root,name) ;
}break;
default :{
printf("\nWrong input\n");
}break ;
}
}

//Show all students data of same program
node *show_program(node * root,char*program){
if(root==NULL){
    return root ;
}
root->left = show_program(root->left,program) ;
char flag = 0;
int i = 0 ;
while(*(program+i)&&*(root->program+i)){
if(*(program+i)!=*(root->program+i)){
flag= 1;
break ;
}
i++;
}
if((*(program+i)=='\0')&&flag==0){
show(root);
}
root->right = show_program(root->right,program);
return root ;
}
//update data
node*update(node*root,int id){
if(root==NULL){
    return root  ;
}
else if(id <root->id){
    root->left = update(root->left,id) ;
}
else if(id >root->id){
    root->right = update(root->right,id) ;
}
else{
int choice ;
printf("\nWhat do you want to update?(if you want to update a student's ID You have to delete it and insert the data again");
printf("\n1---First Name\n2---Last Name\n3---Gpa\n4---College Year\n5---Program\n6---Back to main menu\nChoice : ");
scanf("%d",&choice);
char str[max] ;
switch(choice){
case 1 :
{
printf("\nEnter the new name\n");
scanf("%s",str);
root->name=(char*)malloc(sizeof(char)*(strlen(str)+1));
strcpy(root->name,str);
}break ;
case 2 :
{
printf("\nEnter the new last name\n");
scanf("%s",str);
root->lname=(char*)malloc(sizeof(char)*(strlen(str)+1));
strcpy(root->lname,str);
}break ;
case 3 :{
printf("\nEnter the Gpa : ");
scanf("%f",&root->gpa);
}break ;
case 4 :{
printf("\nEnter the College year : ");
scanf("%d",&root->year);
}break ;
case 5 :
{
printf("\nEnter the new Program\n");
scanf("%s",str);
root->program=(char*)malloc(sizeof(char)*(strlen(str)+1));
strcpy(root->program,str);
}break ;

default : {return root ;}
}
}
return root ;
}

//Delete a student's data
node *get_max(node * root){
if(root==NULL){
    return root  ;
}
else if(root->right==NULL){
    return root ;
}
else {
    root->right = get_max(root->right) ;
}
return root ;
}

node* del_stud(node* root, int id) {
    if (root == NULL) {
        return root;
    }
    if (id < root->id) {
        root->left = del_stud(root->left, id);
    } else if (id > root->id) {
        root->right = del_stud(root->right, id);
    } else {
        if (root->left == NULL) {
            node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            node* temp = root->left;
            free(root);
            return temp;
        }
        node* temp = get_max(root->left);
        root->id = temp->id;
        root->gpa = temp->gpa;
        root->year = temp->year;
        strcpy(root->name, temp->name);
        strcpy(root->lname, temp->lname);
        strcpy(root->program, temp->program);
        root->left = del_stud(root->left, temp->id);
    }
    return root;
}


node* del_all(node* root) {
    if (root != NULL) {
        del_all(root->left);
        free(root->name);
        free(root->lname);
        free(root->program);

        free(root) ;
        del_all(root->right);
    }
    return NULL;
}



int main()
{
node * root = NULL ;
root =insert(root,10,2,3.4,"andrew","karam","engineering");
root =insert(root,8,2,3.4,"ahmed","hamdy","medical");
root =insert(root,12,2,3.4,"adam","maclaurin","law");
root =insert(root,6,2,3.4,"jackie","chan","commerce");
root =insert(root,4,2,3.4,"lauren","mark","engineering");
root =insert(root,2,2,3.4,"james","cameron","arts");
while(1){
int choice ;
printf("\n----University Information System----\n");
printf("\n1---Insert a new student\n2---Update a student's data\n3---Search for a student\n"
"4---Show students in a certain program\n5---Delete a student from the system\n6---delete all students"
"\n7---exit\nChoice : ");
scanf("%d",&choice);
fflush(stdin);
switch(choice){
case 1 :{
insert_via_user(&root) ;
}break ;

case 2:{
int id ;
printf("\nEnter the student's ID : ");
scanf("%d",&id);
root= update(root,id);
}break;
case 3:{
how_search(&root) ;
}break ;
case 4:{
char prog[max] ;
printf("\nEnter the program's name or part of it : ");
scanf("%s",prog) ;
fflush(stdin);
show_program(root,prog) ;
}break ;
case 5:{
int id ;
printf("\nEnter the student's ID : ");
scanf("%d",&id);
root=del_stud(root,id);
}break ;
case 6:{
root=  del_all(root);
}break;
case 7:{
printf("\nThanks for using the program :) (Andrew karam)\n");
system("pause");
exit(0);
}break ;
default:{
printf("\nWrong input\n");
}break;
}
}

    return 0;
}
