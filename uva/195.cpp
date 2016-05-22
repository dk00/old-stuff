#include<stdio.h>
#include<stdlib.h>
char line[1000],chr[256];
int s[1000],asc[256],len,untaken[52];
int numcmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}
void perm(int d){
    if(d>=len){
        printf("%s\n",line);
        return;
    }
    int i;
    for(i=0;i<52;i++){
        if(untaken[i]>0){
            untaken[i]--;
            line[d]=chr[i];
            perm(d+1);
            untaken[i]++;
        }
    }
    return;
}
main(){
int i,n,j;
for(i='A',j=0;i<='Z';i++){
    asc[i]=j;
    chr[j]=i;
    j+=2;
}
for(i='a',j=1;i<='z';i++){
    asc[i]=j;
    chr[j]=i;
    j+=2;
}
scanf("%d",&n);
gets(line);
for(;n>0;n--){
    scanf("%s",line);
    for(i=0;i<256;i++) untaken[i]=0;
    for(i=0;line[i]!='\0';i++){
        s[i]=asc[line[i]];
        untaken[s[i]]++;
    }
    len=i;
    qsort((void *)s,sizeof(s[0]),len,numcmp);
    perm(0);
}
}
