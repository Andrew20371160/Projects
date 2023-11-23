#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>

int main()
{
srand(time(0));
char arr[10][10] ;
for(int i = 0 ; i <10 ; i++){
    for(int j = 0 ; j<10;j++){
        arr[i][j] = '-';
    }
}
int px = (0+rand()%10) , py = 0+rand()%10 ;
int x=9,y=9;
arr[x][y] = 'x' ;
char control ;

while(1){
for(int i  = 0 ; i <10 ; i++){
        printf("\n");
    for(int j=  0 ; j<10; j++){
        printf("%c ",arr[i][j]);
    }
}    printf("\n\n\n\n\n\n\n");
if(x==px&&y==py){printf("\nYOU WON!!!\n");
system("pause\n") ;
exit(0);

}
control =getch();
switch(control){
case 'w' :{
    if(x>0){
    arr[x][y] = '-' ;arr[--x][y] ='x' ;
    }
    else{
        arr[x][y]='-';
        x = 9 ;
        arr[x][y] = 'x' ;
    }

    }break;
case 's' :{
    if(x<9){
    arr[x][y] = '-' ;arr[++x][y] ='x' ;
    }
    else{
        arr[x][y]='-';
        x = 0 ;
        arr[x][y] = 'x' ;
    }

    }break;
case 'a' :{
    if(y>0){
    arr[x][y] = '-' ;arr[x][--y] ='x' ;
    }
    else{
        arr[x][y]='-';
        y = 9 ;
        arr[x][y] = 'x' ;
    }
    }break;
case 'd' :{
    if(y<9){
    arr[x][y] = '-' ;arr[x][++y] ='x' ;
    }
    else{
        arr[x][y]='-';
        y = 0 ;
        arr[x][y] = 'x' ;
    }
    }break;
}
}
    return 0;
}
