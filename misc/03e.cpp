#include<stdio.h>
int n,t,u[100];
struct man{
int p,c[100],m[100];
    int cost(){
        if(p+1>=n)
            return -c[m[n-1]];
        return c[m[p+1]]-c[m[p]];
    }
    void set(){
        int i,j;
        for(i=0;i<n;i++)
            m[i]=i;
        for(i=0;i<n;i++)
            for(j=1;j<n;j++)
                if(c[m[j-1]]<c[m[j]])
                    t=m[j],m[j]=m[j-1],m[j-1]=t;
    }
    bool find(){
        return u[m[p]];
    }
}s[100];
main(){
int i,j,n,sum;
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++)
        for(u[i]=-1,j=0;j<n;j++)
            scanf("%d",&s[i].c[j]);
    for(i=0;i<n;i++)
        s[i].set(),u[i]=-1;
    for(sum=i=0;i<n;i++){
        while(s[i].find()<0 && s[i].p<n){
            if(s[i].cost()>s[s[i].find()].cost()){
                sum-=s[s[i].find()].cost();
                s[s[i].find()].p++;
                break;
            }
            s[i].p++;
        }
        if(s[i].p<n){
            sum+=s[i].c[s[i].m[s[i].p]];
            u[s[i].m[s[i].p]]=i;
        }
    }
    printf("%d\n",sum);
}
}
