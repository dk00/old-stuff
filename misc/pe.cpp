#include<stdio.h>
#include<stdlib.h>
struct event{
    int x,y,t;
    bool operator<=(event s){
        return abs(x-s.x)+abs(y-s.y)<=s.t-t;
    }
    void get(){
        scanf("%d %d %d",&t,&x,&y);
    }
}e[1000],s1[1000],s2[1000];
int p[1000],q[1000],c[1000][1000];
int eventcmp(const void *a,const void *b){
    return ((event *)a)->t-((event *)b)->t;
}
main(){
freopen("pe.in","r",stdin);
freopen("pe.out","w",stdout);
int i,j,k,t,n,num,n1,n2;
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    for(i=0;i<n;i++){
        e[i].get();
        p[i]=-1;
        q[i]=0;
    }
    qsort(e,n,sizeof(e[0]),eventcmp);
    num=n,n1=0,n2=0;
    s1[n1++]=e[0];
    for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
            c[i][j]=e[i]<=e[j];
    for(i=1;i<n;i++)
        for(j=0;j<i;j++){
            if(!q[j] && c[j][i]){
                q[j]=1;
                p[i]=j;
                num--;
                break;
            }
        }
    printf("%d\n",num);
}
}
