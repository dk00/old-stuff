/*
ID: s0000151
PROG: namenum
LANG: C++
*/

#include<stdio.h>
#define DEBUG 0
#define NS 29
char dic[NS][13]={"ABE","ACE","ADEM","ADEN","AUBRIANNA","CONSTANTINE","GREG","HAM","HAO","IAN","INDEPENDENCE","JEB","JENNA","JILLIAN","JIM","JIN","KEB","KENNA","KILLIAN","KIM","KIN","KRISTOPHER","LANG","LANI","LEA","LEOMA","LEONA","LILLIAN","LIN"};
main(){
if(!DEBUG){freopen("namenum.in","r",stdin);
freopen("namenum.out","w",stdout);}
int i,j,asc[256];
long long num[NS],n;
char line[10];
asc['A']=asc['B']=asc['C']=2;
asc['D']=asc['E']=asc['F']=3;
asc['G']=asc['H']=asc['I']=4;
asc['J']=asc['K']=asc['L']=5;
asc['M']=asc['N']=asc['O']=6;
asc['P']=asc['R']=asc['S']=7;
asc['T']=asc['U']=asc['V']=8;
asc['W']=asc['X']=asc['Y']=9;
for(i=0;i<NS;i++){
    for(num[i]=j=0;dic[i][j]!='\0';j++)
        num[i]=num[i]*10+asc[dic[i][j]];
}
scanf("%lld",&n);
for(i=0;i<NS && num[i]!=n;i++);
if(i>=NS)puts("NONE");
else puts(dic[i]);
for(i++;i<NS;i++)if(num[i]==n)puts(dic[i]);
if(DEBUG)scanf(" ");
}
