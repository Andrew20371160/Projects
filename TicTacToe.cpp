#include<iostream>
#include<conio.h>
#define m 3
using namespace std;

int main(){
char area[m][m] ={{'n','n','n'},{'n','n','n'},{'n','n','n'}};
int inner = 0 , outer= 0 ;
char ch ;
while(1){
cout<<"\n enter 'g' if someone won or its a draw ";
cout<<"\n enter 'h' if if that's the place you want to play in ";
cout<<"\n (w,a,s,d) for movent";
cout<<"\n your position is : "<<inner+1<<","<<outer+1<<endl ;
for(int i = 0 ; i <m ;i++){
    for(int j= 0; j<m ; j++){
        cout<<area[i][j]<<" " ;
    }
    cout<<endl;
}

if((ch = getch())=='g'){
    break ;
}
switch(ch){
case 'w' :{
if(inner==0){
    break;
}
inner--;

}break ;
case 's' :{
if(inner==m-1){
    break;
}
inner++;
}break ;
case 'a' :{
if(outer==0){
    break;
}
outer--;

}break ;

case 'd' :{
if(outer==m-1){
    break;
}
outer++;
}break ;
case 'h':{
if(area[inner][outer]=='n'){

cout<<"\n Enter your character(X,O)";

cin>>area[inner][outer];

}
else{
  cout<<endl<<"that place is taken for "<<area[inner][outer];
    break;
}
}break;
}
}
cout<<"\n game finished";
cout<<"\n credits : Dinosaur : Andrew karam "<<endl;
system("pause");
return 0 ;
}
