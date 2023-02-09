#include <iostream>
#include<cstring>
#define MAX 15
using namespace std;
struct date{
int day ,month,year;
};
void datecpy(date*dest,date*src){
dest->day= src->day ;
dest->month = src->month ;
dest->year= src->year ;
}

struct node{
char * song_name ;
char * album ;
char * artist ;
date date_added ;
node * next ;
node*prev ;
};


node *get_node(char * song_name ,char * album ,char * artist ,date date_added ){
node * newsong = new node ;
newsong->song_name = new char[strlen(song_name)+1];
strcpy(newsong->song_name,song_name);
newsong->artist = new char[strlen(artist)+1];
strcpy(newsong->artist,artist);
newsong->album = new char[strlen(album)+1];
strcpy(newsong->album,album);
datecpy(&(newsong->date_added),&date_added) ;
newsong->next = newsong;
newsong->prev  = newsong ;
return newsong;
}
void show_data(node*song){
if(song==NULL){
    return ;
}
else{
cout<<endl<<"Song name : "<<song->song_name ;
cout<<endl<<"Artist : "<<song->artist ;
cout<<endl<<"Album : "<<song->album ;
cout<<endl<<"Date added : "<<song->date_added.day<<"/"<<song->date_added.month<<"/"<<song->date_added.year<<endl ;
}
}
node * enque(node*tail ,char * song_name ,char * album ,char * artist ,date date_added ){
if(tail ==NULL){
    tail = get_node(song_name,album,artist,date_added);
}
else {
    node* newsong= get_node(song_name,album,artist,date_added);
    newsong->next= tail->next ;
    newsong->prev = tail ;
    tail->next->prev=newsong ;
    tail->next  = newsong ;

}
return tail ;
}
node * add_via_user(node *tail){
char sname[MAX],artist[MAX],album[MAX] ;
date date_added ;
char dummychar;
cout<<"\nEnter the song's name\n";
cin>>sname ;
cout<<"\nEnter the artist's name\n";
cin>>artist ;
cout<<"\nEnter the album's name\n";
cin>>album ;
cout<<"\nEnter the song's release date(day/month/year)\n";
cin>>date_added.day>>dummychar>>date_added.month>>dummychar>>date_added.year ;
tail =enque(tail,sname,album,artist,date_added);
cout<<endl<<"\nSong added!!!\n";
return tail ;
}
void play_all(node*tail ){
if(tail ==NULL){
    cout<<"\nPlaylist is empty\n";
    return ;
}
node*ptr= tail ->next ;
do{
show_data(ptr);
ptr =ptr->next ;
}while(ptr!=tail->next) ;
}
void get_portion(char*portion,char *full_text,int s ){

for(int i = 0 ;i<=s;i++){
    *(portion+i)= *(full_text+i);
}

*(portion+s)= NULL;
}
void search_by_name(char * name , node*tail,int mode ){
if(tail==NULL){
    cout<<"\nPlaylist is empty\n";
    return ;
}

node*ptr = tail->next;
switch (mode){
case 1 :{
do{
if(*ptr->song_name==*name){
int s = strlen(name);
char *portion = new char [s+1];
get_portion(portion,ptr->song_name,s);
if(strcmp(portion,name)==0){
    show_data(ptr);
}
delete[]portion ;
}
ptr = ptr->next ;
}while(ptr!=tail->next);
}break ;
case 2 :{
do{
if(*ptr->album==*name){
int s = strlen(name);
char *portion = new char [s+1];
get_portion(portion,ptr->album,s);
if(strcmp(portion,name)==0){
    show_data(ptr);
}
delete[]portion ;
}
ptr = ptr->next ;
}while(ptr!=tail->next);
}break ;
case 3 :{
do{
if(*ptr->artist==*name){
int s = strlen(name);
char *portion = new char [s+1];
get_portion(portion,ptr->artist,s);
if(strcmp(portion,name)==0){
    show_data(ptr);
}
delete[]portion ;
}
ptr = ptr->next ;
}while(ptr!=tail->next);
}break ;
default:play_all(tail);break ;
}
}
void search_via_user(node*tail){
int mode ;
char text[MAX];
cout<<"\nSearch by :\n1---song's name\n2---album's name\n3---artist's name\n";
cin>>mode;
cout<<"\nEnter the text related to what you just chose from the previous options";
cin>>text;
search_by_name(text,tail,mode);
}

node*del_by_name(char * name , node*tail ){
if(tail==NULL){
    cout<<"\nPlaylist is empty\n";
    return tail;
}
else if(strcmp(tail->song_name,name)==0){
    node*temp = tail ;
    tail = tail->prev ;
    temp->prev->next= temp->next;
    temp->next->prev = temp->prev ;
}
else{
node *ptr = tail->next;
do{
if(strcmp(ptr->song_name,name)==0){
    ptr->next->prev = ptr->prev;
    ptr->prev->next = ptr->next;
    delete[]ptr;
    ptr = NULL ;
    return tail ;
}
ptr = ptr->next;
}while(ptr!=tail);
}
return tail ;
}
int list_size(node*tail){
int s = 0 ;
if(tail==NULL){
return s ;
}
node*ptr = tail ->next ;
do{
s++;
ptr = ptr->next ;
}while(ptr!=tail->next);
return s;
}
void cpynode(node * dest , node * src ){
dest->song_name = new char[strlen(src->song_name)+1];
strcpy(dest->song_name,src->song_name) ;
dest->artist = new char[strlen(src->artist)+1];
strcpy(dest->artist,src->artist) ;
dest->album = new char[strlen(src->album)+1];
strcpy(dest->album,src->album) ;
datecpy(&dest->date_added,&src->date_added);
}
void switch_data(node *ptr1,node *ptr2 ){
node * ptr =get_node(ptr1->song_name,ptr1->album,ptr1->artist,ptr1->date_added);
cpynode(ptr1,ptr2);
cpynode(ptr2,ptr);
delete[]ptr ;
}

void bsort(node *tail ){
if(tail==NULL||tail->next ==tail){
    return ;
}
int s = list_size(tail);
node*ptr1 = tail->next ;
node*ptr2 = tail->next ;
for(int i =0 ; i <s ; i++){
ptr1 = ptr2 ;
for(int j =i+1;j<=s;j++){
    if(strcmp(ptr2->song_name,ptr1->song_name)>0){
        switch_data(ptr2,ptr1);
}
ptr1=ptr1->next;
}
ptr2=ptr2->next;
}
}
node * del_all(node *tail ){
if(tail==NULL){
    cout<<"\nPlaylist is empty\n";
    return tail;
}
node *ptr  =tail->next;
do{
tail = del_by_name(ptr->song_name,tail);
ptr = ptr->next ;
}while(ptr!=tail);
del_by_name(tail->song_name,tail);
tail  =NULL ;
return tail ;
}
void interface(node *tail){
while(1){
int choice ;
cout<<"\n1---Insert a song\n2---Search for song\n3---Show all songs\n4---sort in alphabetical order";
cout<<"\n5---How many songs do i have?\n6---Delete a song\n7---Delete all songs\n8---exit\nChoice:";
cin>>choice;
switch(choice){
case 1:{
tail = add_via_user(tail);
}break ;
case 2:{
search_via_user(tail);
}break;
case 3:{
play_all(tail);
}break;
case 4:{
bsort(tail);
}break;
case 5:{
cout<<"\nYou have "<<list_size(tail)<<endl;
}break;
case 6:{
char text[MAX];
search_via_user(tail);
cout<<"\n now enter the exact song's name ";
cin>>text;
tail =del_by_name(text,tail);
cout<<endl<<"Song deleted!!!\n";
}break;
case 7:{
tail =del_all(tail);
}break;
case 8:{
cout<<"\n Thank's for trying it out\n";
cout<<"\n(by:Andrew Karam)\n";
system("pause");
exit(0);
}break;
}
}
}
int main()
{
node * tail = NULL ;
interface(tail);
tail=del_all(tail);
tail = NULL ;
    return 0;
}
