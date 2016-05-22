#include<stdio.h>
#include<string.h>
int v[27],c[27][27];
void go(int j){
    v[j]=0;
    for(int i=0;i<26;i++)
        if(v[i] && c[j][i])go(i);
}
main(){
int i,j,n,t,stt,end,ind[27],otd[27];
char s[20000];
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    for(i=0;i<26;i++){
        v[i]=ind[i]=otd[i]=0;
        for(j=0;j<26;j++)c[i][j]=0;
    }
    while(n--){
        scanf("%s",s);
        i=s[0]-'a';
        j=s[strlen(s)-1]-'a';
        otd[i]++;
        ind[j]++;
        c[i][j]=1;
        v[i]=v[j]=1;
    }
    for(j=0;!otd[j];j++);
    for(stt=end=i=0;i<26;i++){
        if(ind[i]-otd[i]==1)stt++;
        else if(otd[i]-ind[i]==1)end++;
        else if(otd[i]!=ind[i])stt+=151;
    }
    go(j);
    for(n=j=0;j<26;j++)n+=v[j];
    if(!n && ((!stt && !end) || (stt==1 && end==1)))
        puts("Ordering is possible.");
    else puts("The door cannot be opened.");
}
}
