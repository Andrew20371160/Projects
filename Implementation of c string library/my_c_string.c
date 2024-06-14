#include "my_string.h"

void * Memset(void * dest,int value,uint length)
{
    if(dest)
    {
        char * ptr =(char*)dest ;
        //Worst case senarion : if the user inputs a length >=string size
        //Make sure not to type into the NULL character 
        while((*ptr!='\0')&&ptr<=((char*)dest+length))
        {
            *ptr =  (char)value ;
            ptr++ ;
        }
    }
    return dest ;
}

void * Memchr(const void * str,int ch,uint n )
{
    char *ptr = (char*)str ;
//check if ptr is not equal to NULL
    while(ptr&&ptr<((char*)str+n))
    {
        if(*(ptr)==ch)
        {
            return ptr ;
        }
        ptr++;
    }
    return NULL ;
}

void *Memcpy(void *dest, const void *src,uint n)
{
    if(dest&&src)
    {
        char *ptr1 = (char*)dest ;
        char *ptr2 = (char*)src;
        //make sure the user doesn't Enter a size larger than size of src string
        while(*ptr2&&n--)
        {
            *ptr1 =*ptr2 ;
            ptr1++;
            ptr2++;
        }
        *(ptr2)='\0';
        return (char*)dest;
    }
    return NULL ;
}
//credits for Bing ai for teaching me about memory overlapping
void* Memmove(void *dest,const void*src,uint size)
{
    if(dest&&src)
    {
        if(dest<src)
        {
            while(size--)
            {
                *(char*)dest++= *(char*)(src++);
            }
        }
//if pointers that are pointing to same memory region
//for example a string the memcpy would have an unexpected behavior
        else
        {
            dest+=size;
            src+=size;
            while(size--)
            {
                *(char*)--dest= *(char*)--src;
            }
        }
        return dest ;
    }
    return NULL ;
}
int Memcmp (const void *s1, const void *s2, uint n)
{
    if(s1&&s2)
    {
        char * ptr1 =(char*)s1 ;
        char * ptr2 =(char*)s2 ;
        while(n--)
        {
            if(*ptr1!=*ptr2)
            {
                return (*ptr1>*ptr2)?1:-1 ;
            }
            ptr1++;
            ptr2++ ;
        }
        return 0 ;
    }
    printf("\nError : Passing NULL as argument");
    return 3 ;
}
void *Memset (void *ptr, int c, uint n)
{
    if(ptr)
    {
        while(n--)
        {
            *(char*)ptr=c;
            ptr=(char*)ptr+1;
        }
    }
    return ptr ;
}

char *Strcat (char *dest, const char *src)
{
    if(dest&&src)
    {
        uint i = 0 ;
        while(*(dest+i)!='\0')
        {
            i++;
        }
        while(*(src)!='\0')
        {
            *(dest+i) = *(src++) ;
            i++;
        }
        *(dest+i)='\0';
    }
    return dest ;
}
char *Strncat (char *dest, const char *src, uint n)
{
    if(dest&&src)
    {
        uint i=  0 ;
        while(*(dest+i)!='\0')
        {
            i++;
        }
        while(i<n-1)
        {
            *(dest+i) = *(src++) ;
            i++;
        }
        *(dest+i+1)='\0';
    }
    return dest ;
}

char *Strchr (const char *str, int c)
{
    if(str)
    {
        while(*str)
        {
            if(*(str)==c)
            {
                return str ;
            }
            str++;
        }
    }
    return NULL;
}

char *Strrchr (const char *str, int c)
{
    if(str)
    {
        char *ptr =NULL;
        while(*str!='\0')
        {
            if(*str==c)
            {
                ptr = str ;
            }
            str++;
        }
        return ptr;
    }
    return NULL ;
}
int Strcmp (const char *str1, const char *str2)
{
    if(str1&&str2)
    {
        while(*str1&&*str2)
        {
            if(*str1!=*str2)
            {
                return (*str1>*str2)?1:-1;
            }
            str1++;
            str2++;
        }
        if(*str1&&!(*str2))
        {
            return 1 ;
        }
        else if(*str2&&!(*str1))
        {
            return -1 ;
        }
        return 0;
    }
    printf("\nInvalid : NULL pointer passed as argument");
    return 3;
}
int Strncmp (const char *s1, const char *s2, uint n)
{
    if(s1&&s2)
    {
        while(n--)
        {
            if(*s1!=*s2)
            {
                return (*s1>*s2)?1:-1;
            }
            s1++;
            s2++;
        }
        return 0 ;
    }
    printf("\nInvalid : NULL pointer is passed as argument") ;
    return 3 ;
}
uint Strxfrm(char *dest, const char *src, uint n)
{
    if(dest&&src)
    {
        uint i = 0;
        while(*src&&n--)
        {
            *dest++=  *src++;
            i++;
        }
        return i ;
    }
    printf("\nInvalid : NULL pointer is passed as argument") ;
    return 0 ;
}
//Since strcspn & strspn have reversed functionality
//we can merge them into one function and just invert the parameters as shown below
uint sel_Strcspn(const char *str1, const char *str2,int is_strcspn)
{
    if(str1&&str2)
    {
        return (is_strcspn)?Strcspn(str1,str2):Strcspn(str2,str1);
    }
    else
    {
        printf("\nInvalid : NULL pointer is passed as argument") ;
        return -1 ;
    }
}
uint Strcspn(const char *str1, const char *control)
{
    char *p1 = str1 ;
    char *p2= control ;

    while(*(p1)!='\0')
    {
        p2=control ;
        while(*p2!='\0')
        {
            if(*(p1)==*(p2))
            {
                return p1-str1;
            }
            p2++;
        }
        p1++;
    }
    return p1-str1;
}

uint Strlen(const char* s)
{
    if(s)
    {
        uint counter = 0 ;
        while(*s)
        {
            s++;
            counter++ ;
        }
        return counter ;
    }
    return 0;
}
char *Strpbrk(const char *str1, const char *str2)
{
    if(str1&&str2)
    {
        char *p1 = str1 ;
        char *p2 = str2 ;
        while(*p1)
        {
            p2 = str2 ;
            while(*p2)
            {
                if(*(p1)==*(p2))
                {
                    return p1;
                }
                p2++;
            }
            p1++;
        }
    }
    return NULL;
}
//ndrew
//Andrewkaram
char *Strstr(const char *needle, const char *haystack)
{
    if(needle&&haystack)
    {
        for(char *p1 = haystack; *p1!='\0'; p1++)
        {
            if(*p1==*needle)
            {
                char *temp1= p1 ;
                char *temp2= needle ;
                while((*temp2!='\0')&&(*(temp1++)==*(temp2++)));
                if(*temp2=='\0')
                {
                    return p1 ;
                }
            }
        }
    }
    return NULL;
}

char *Strtok(char *str, const char *delim)
{
    static char *next_token;
    if (str)
    {
        next_token = str;
    }
    if (!next_token)
    {
        return NULL;
    }
    char *token = next_token;
    while (*next_token)
    {
        if (Strchr(delim, *next_token))
        {
            *next_token++ = '\0';
            break;
        }
        next_token++;
    }
    if (token == next_token)
    {
        return NULL;
    }
    return token;
}

