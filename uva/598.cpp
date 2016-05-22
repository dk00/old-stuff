#include<stdio.h>
int used[1000],path[1000],out[1000],max,min,n;
char s[1000][31];
void dfs(int d){
    if(d>max)return;
    int i;
    if(d==min){
        for(i=0;i<d;i++){
            if(i)printf(", ");
            printf("%s",s[path[i]]);
        }
        puts("");
    }
    for(i=0;i<n;i++){
        if(!used[i] && !d || i>path[d-1]){
            used[i]=1;
            path[d]=i;
            dfs(d+1);
            used[i]=0;
        }
    }
}
main(){
int t,j,k,i;
char line[1000];
scanf("%d%c",&t,&line[0]);
gets(line);
while(t--){
    gets(line);
    if(line[0]=='*')min=1,max=1000;
    else if(sscanf(line,"%d %d",&j,&k)==1){
        max=min=j;
    }
    else{
        min=j;
        max=k;
    }
    for(n=0;gets(s[n])!=NULL && s[n][0];n++);
    max<?=n;
    for(i=0;i<n;i++)used[i]=0;
    for(;min<=max;min++){
        printf("Size %d\n",min);
        dfs(0);
        puts("");
    }
    if(t)puts("");
}
}
