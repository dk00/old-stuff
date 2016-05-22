#include<stdio.h>
char string[100],reversed[256];
main(){
reversed['A']='A',reversed['E']='3',reversed['3']='E',reversed['H']='H',
reversed['I']='I',reversed['J']='L',reversed['L']='J',reversed['M']='M',
reversed['O']='O',reversed['S']='2',reversed['2']='S',reversed['T']='T',
reversed['U']='U',reversed['V']='V',reversed['W']='W',reversed['X']='X',
reversed['Y']='Y',reversed['Z']='5',reversed['5']='Z',reversed['1']='1',
reversed['8']='8',reversed['0']='0';
int i,j,palindrome,mirrored;
    while(gets(string)!=NULL)
    {
        palindrome=1;
        mirrored=1;
        for(j=0;string[j]!=' ' && string[j];j++);
        string[j--]=0;
        for(i=0;string[i];i++,j--)
        {
            if(string[i]!=string[j])
                palindrome=0;
            if(reversed[string[i]]!=string[j])
                mirrored=0;
        }
        printf("%s",string);
        if(palindrome && mirrored)
            puts(" -- is a mirrored palindrome.");
        else if(palindrome && !mirrored)
            puts(" -- is a regular palindrome.");
        else if(!palindrome && mirrored)
            puts(" -- is a mirrored string.");
        else
            puts(" -- is not a palindrome.");
        puts("");
    }
}
