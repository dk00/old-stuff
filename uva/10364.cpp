#include<stdio.h>
#include<stdlib.h>
int numcmp(const void *a,const void *b){
    return *(int *)b-*(int *)a;
}
bool _p;
int m,stick[20],used,len;
void dfs(int d,int ll,int i){
    if(d==3){
        _p=1;
        return;
    }
    if(!ll){
        while(used&(1<<i))i++;
        used|=(1<<i);
        if(stick[i]==len)dfs(d+1,0,0);
        else if(stick[i]+stick[m-1]<=len)dfs(d,stick[i],i+1);
        used&=~(1<<i);
        return;
    }
    for(;i<m && !_p;i++)
        if(!(used&(1<<i))&& ll+stick[i]<=len){
            used|=(1<<i);
            if(stick[i]+ll==len)dfs(d+1,0,0);
            else if(stick[i]+stick[m-1]<=len)dfs(d,ll+stick[i],i+1);
            used&=~(1<<i);
        }
}
main(){
int t,i,sum;
scanf("%d",&t);
while(t--){
    scanf("%d",&m);
    for(sum=i=0;i<m;i++){
        scanf("%d",&stick[i]);
        sum+=stick[i];
    }
    qsort(stick,m,sizeof(stick[0]),numcmp);
    if(sum%4 || stick[0]*4>sum){
        puts("no");
        continue;
    }
    len=sum/4;
    used=_p=0;
    dfs(0,0,0);
    if(_p)puts("yes");
    else puts("no");
}
}
