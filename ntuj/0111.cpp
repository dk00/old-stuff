#include<stdio.h>
class martix{
public:
    int n,m,s[120][120];
    void clean(int d){
        int i,j;
        for(i=0;i<d;i++)
            for(j=0;j<d;j++)
                s[i][j]=0;
    }
    void operator*=(martix b){
        martix a=*this;
        int i,j,k;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++){
                s[i][j]=0;
                for(k=0;k<n;k++){
                    s[i][j]+=(a.s[i][k]*b.s[k][j])%m;
                    s[i][j]%=m;
                }
            }
    }
    void print(){
        int i,j;
        for(i=0;i<n;i++){
            printf("%d",s[i][0]);
            for(j=1;j<n;j++)
                printf(" %d",s[i][j]);
            puts("");
        }
    }
}s,r;
main(){
    int i,j,d,n,m,a[120],f[120];
    while(scanf("%d",&d) && d){
        m=10000;
        for(i=0;i<d;i++){
            scanf("%d",&f[i]);
            f[i]%=m;
        }
        for(i=0;i<d;i++){
            scanf("%d",&a[i]);
            a[i]%=m;
        }
        scanf("%d",&n);
        n++;
        if(n<=d){
            printf("%d\n",f[n-1]);
            continue;
        }
        s.clean(d),r.clean(d);
        s.m=r.m=m;
        s.n=r.n=d;
        for(i=0;i<d;i++){
            s.s[i][i]=1;
            if(i)r.s[i-1][i]=1;
            r.s[d-1][d-i-1]=a[i];
        }
        for(i=1,n-=d;i<=n && i>0;i<<=1,r*=r)
            if(i&n)s*=r;
        for(i=n=0;i<d;i++)
            n=(n+s.s[d-1][i]*f[i])%m;
        printf("%d\n",n);
    }
}
