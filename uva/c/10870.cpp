#include<stdio.h>
int mod(int a,int b){
    if(a%b==0)return b;
    return a%b;
}
class martix{
public:
    int n,m,s[100][100];
    void clean(){
        int i,j;
        for(i=0;i<20;i++)
            for(j=0;j<20;j++)
                s[i][j]=0;
    }
    void geta(int d){
        n=d;
        int i;
        for(i=n-1;i>=0;i--){
            scanf("%d",&s[n-1][i]);
            s[n-1][i]=mod(s[n-1][i],m);
            s[i][n-1]=s[n-1][i];
        }
    }
    void getf(int d){
        n=d;
        int i;
        for(i=0;i<n;i++){
            scanf("%d",&s[n-1][i]);
            s[n-1][i]=mod(s[n-1][i],m);
            s[i][n-1]=s[n-1][i];
        }
    }
    void operator*=(martix &p){
        martix a,b;
        a=*this,b=p;
        int i,j,k;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++){
                s[i][j]=0;
                for(k=0;k<n;k++){
                    s[i][j]+=mod(mod(a.s[i][k],m)*mod(b.s[k][j],m),m);
                    s[i][j]=mod(s[i][j],m);
                }
            }
    }
}s,r;
main(){
int i,d,n,m;
freopen("10870.in","r",stdin);
freopen("10870a.out","w",stdout);
while(scanf("%d %d %d",&d,&n,&m) && d+n+m){
    s.m=r.m=m;
    r.clean(),s.clean();
    r.geta(d);
    s.getf(d);
    if(n<=d){
        printf("%d\n",s.s[d-1][n-1]);
        continue;
    }
    for(i=1,n-=d;i<=n && i>0;i<<=1,r*=r)
        if(n&i)s*=r;
    printf("%d\n",s.s[d-1][d-1]%m);
}
}
