#include<stdio.h>
int used[13],path[13],left,min,max,n;
char s[13][31];
void dfs(int d){
    if(d==min){
        printf("%s",s[path[0]]);
        for(d=1;d<min;d++)printf(", %s",s[path[d]]);
        puts("");
    }
    for(int i=(d?path[d-1]+1:0);i<n;i++){
        if(!used[i]){
            used[i]=1;
            path[d]=i;
            dfs(d+1);
            used[i]=0;
        }
    }
}
main(){
int t;
char line[1000];
scanf("%d%c",&t,&line[0]);
gets(line);
while(t--){
    gets(line);
    if(line[min=0]=='*')max=13;
    else if(sscanf(line,"%d %d",&min,&max)==2);
    else max=min;
    for(n=0;gets(s[n])!=NULL && s[n][0]!='\0';n++);
    max<?=n;
    for(min>?=1;min<=max;min++){
        printf("Size %d\n",min);
        dfs(0);
        puts("");
    }
}
}
