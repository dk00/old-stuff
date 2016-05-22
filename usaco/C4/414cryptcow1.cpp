/*
PROB: cryptcow
ID: s0000151
LANG: C++
*/
#include<stdio.h>
#include<string.h>
char target[80]="0912160086";
int n1,n2,find,crypt,num1[256],num2[256];
int check(char *s){
    int i,j;
    for(i=0;s[i]!='C' && i<n1;i++)
        if(s[i]!=target[i])
            return 0;
    for(i=n2-1,j=n1-1;j>0 && s[i]!='W';i--,j--)
        if(s[i]!=target[j])
            return 0;
    for(i=0;s[i] && s[i]!='C';i++)
        if(s[i]=='O' || s[i]=='W')
            return 1;
    for(;s[i];i++);
    while(i-- && s[i]!='W')
        if(s[i]=='O' || s[i]=='C')
            return 1;
    return 0;
}
void dfs(char *s,int n){
    int i,j,k,l;
    for(i=0;s[i];i++)
        if(s[i]=='C' || s[i]=='O' || s[i]=='W')
            break;
    if(!s[i])
    {
        puts(s);
        find=1;
        return;
    }
    if(check(s))return;
    char tmp[100],*ptr;
    i=n;
    while(i-->0){
        while(i>=0 && s[i]!='C')i--;
        if(i<0)break;
        for(j=i+1;j<n;j++){
            while(j<n && s[j]!='O')j++;
            if(j>=n)break;
            for(k=j+1;k<n;k++){
                while(k<n && s[k]!='W')k++;
                if(k>=n)break;
                s[i]=s[j]=s[k]=0;
                for(ptr=tmp,l=0;l<i;l++)*(ptr++)=s[l];
                for(l=j+1;l<k;l++)*(ptr++)=s[l];
                for(l=i+1;l<j;l++)*(ptr++)=s[l];
                for(l=k+1;l<n;l++)*(ptr++)=s[l];
                *ptr=0;
                crypt++;
                dfs(tmp,ptr-tmp);
                if(find)return;
                crypt--;
                s[i]='C',s[j]='O',s[k]='W';
            }
        }
    }
}
main(){
    int i,j,c,o,w;
    /*freopen("cryptcow.in","r",stdin);
    freopen("cryptcow.out","w",stdout);*/
    char s[100];
    for(i=0;scanf("%c",s+i)!=EOF && *(s+i)!='\n';i++);
    *(s+i)=0;
    n1=strlen(target),n2=strlen(s);
    find=crypt=0;
    for(i=0;i<n1;i++)num1[target[i]]++;
    for(i=0;i<n2;i++)num2[s[i]]++;
    if(num2['C']!=num2['O'] || num2['C']!=num2['W'] ||
    num2['O']!=num2['W']){
        puts("0 0");
        return 0;
    }
    num2['C']=num2['O']=num2['W']=0;
    for(i=0;i<256;i++)
        if(num1[i]!=num2[i]){
            puts("0 0");
            return 0;
        }
    dfs(s,strlen(s));
    printf("%d %d\n",find,crypt);
    scanf(" ");
}
