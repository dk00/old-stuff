#include<stdio.h>
#define NO {puts("no");continue;}
int used,take,stk[20],sq[1000000],sn,m,ed;
void dfs(int i,int len){
    if(len==ed)sq[sn++]=used;
    if(take>=m-3)return;
    for(;i<m && len+stk[i]<=ed;i++)
        if((used&(1<<i))==0){
            take++;
            used&=(1<<i);
            dfs(i,len+stk[i]);
            used^=(1<<i);
            take--;
        }
}
main(){
int t,i,j,k,r,sum,max,find;
scanf("%d",&t);
while(t--){
    scanf("%d",&m);
    for(max=i=sum=0;i<m;i++){
        scanf("%d",&stk[i]);
        sum+=stk[i];
        if(stk[i]>max)max=stk[i];
    }
    if(sum%4 || (max<<2)>sum)NO
    ed=sum>>2;
    for(i=0;i<m;i++)
        for(k=1;k<m;k++)
            if(stk[k-1]>stk[k]){
                stk[k-1]+=stk[k];
                stk[k]=stk[k-1]-stk[k];
                stk[k-1]-=stk[k];
            }
    dfs(0,0);
    for(find=i=0;i<sn;i++){
        for(j=i;j<sn;j++){
            if(sq[i]&sq[j])continue;
            for(k=j;k<sn;k++){
                if(sq[i]&sq[k] || sq[j]&sq[k])continue;
                find=1;
                break;
            }
            if(find)break;
        }
        if(find)break;
    }
    if(find)puts("yes");
    else puts("no");
    used=0;
    used|=sq[i];
    used|=sq[j];
    used|=sq[k];
    used=~used;
    printf("%d %d %d\n",sq[i],sq[j],sq[k]);
    printf("side 0:");
    for(r=0;r<m;r++)
        if(sq[i]&(1<<r))printf(" %d",stk[r]);
    printf("\nside 1:");
    for(r=0;r<m;r++)
        if(sq[j]&(1<<r))printf(" %d",stk[r]);
    printf("\nside 2:");
    for(r=0;r<m;r++)
        if(sq[k]&(1<<r))printf(" %d",stk[r]);
    printf("\nside 3:");
    for(r=0;r<m;r++)
        if(used&(1<<r))printf(" %d",stk[r]);
    puts("");
}
}
