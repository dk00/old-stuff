#include <cstdio>
#include <algorithm>
using namespace std;
int stick[20],m,sum,tp;
bool u[20],complete;
inline bool cmp(int a,int b){
    return a>b;
}
void dfs(int i,int s,int a){
    if(i==4){
        complete=1;
        return;
    }
    if(s==0){
        while(u[a])
            a++;
        u[a]=1;
        if(stick[a]==tp)
            dfs(i+1,0,0);
        else if(stick[a]+stick[m-1]<=tp)
            dfs(i,stick[a],a+1);
        u[a]=0;
        return;
    }
    for(;a<m&&!complete;a++)
        if(!u[a]&&stick[a]+s<=tp){
            u[a]=1;
            if(s+stick[a]==tp)
                dfs(i+1,0,0);
            else if(stick[a]+stick[m-1]<=tp)
                dfs(i,s+stick[a],a+1);
            u[a]=0;
        }
}
int main(){
int c,i;
scanf("%d",&c);
while(c-->0){
    sum=0;
    scanf("%d",&m);
    for(i=0;i<m;i++) {
        u[i]=0;
        scanf("%d",&stick[i]);
        sum+=stick[i];
    }
    sort(stick,stick+m,cmp);
    if(sum%4||stick[0]*4>sum) {
        printf("no\n");
        continue;
    }
    tp=sum/4;
    complete=0;
    dfs(1,0,0);
    if(complete)
        printf("yes\n");
    else
        printf("no\n");
}
return 0;
}
