#include <stdio.h>
#include <stdlib.h>

int main()
{
char * str = NULL ;
str = (char*)malloc(2*sizeof(char)) ;
*(str+1) = '\0' ;
int i = 0 ;
while(*(str+i-1)!='x'){
scanf("%c",str+i) ;

i++ ;
str = (char*)realloc(str,2+i);

}
printf("\n%s",str);
free(str) ;
str = NULL ;
    return 0;
}
