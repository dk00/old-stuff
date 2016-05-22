#include<cstdio>
inline int count(int n)
{
    int j;
    for(j=0;n>0;n>>=1)
        j+=n&1;
    return j;
}
int un,u[9999];
main()
{
    int i,j,k,n,m,s[999];
    char tmp[99];
    while(scanf("%d %d",&m,&n)==2 && n+m){
        for(i=0;i<n;i++){
            scanf("%s",tmp);
            for(j=s[i]=0;tmp[j];j++)
                s[i]=s[i]*2+tmp[j]-'0';
        }
        for(k=m,j=(1<<m)-1;j>=0;j--){
            for(un++,i=0;i<n;i++){
                if(u[s[i]&j]==un)break;
                u[s[i]&j]=un;
            }
            if(i>=n && count(j)<k)
                k=count(j);
        }
        printf("%d\n",k);
    }
}
