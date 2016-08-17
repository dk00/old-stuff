#include<cstdio>
#include<cstring>
const int d=100000,N=200000;
int s[d+1],rv[d+1],lv[d+1],h[22][N+1],num[N+1];
inline int go(int k,int x){return k|((1<<x)-1);}
main()
{
    int i,j,k,n,m,a,b,c;
    while(scanf("%d %d",&n,&m)==2 && n)
    {
        memset(num,0,sizeof(num));
        for(i=0;i<n;i++)
        {
            scanf("%d",s+i);
            s[i]+=d;
            num[s[i]]++;
        }
        for(i=0;i<n;i++)
            if(i && s[i]==s[i-1])
                lv[i]=lv[i-1]+1;
            else lv[i]=1;
        for(i=n-1;i>=0;i--)
            if(i<n-1 && s[i]==s[i+1])
                rv[i]=rv[i+1]+1;
            else rv[i]=1;
        for(i=0;i<=N;i++)
            h[0][i]=num[i];
        for(j=1;j<=21;j++)
            for(i=0;i<=N;i+=(1<<j))
            {
                a=i;
                b=i+(1<<j)-1;
                b<?=N;
                h[j][b]=h[0][b];
                for(k=b-1;k>=i;k--)
                    h[j][k]=h[0][k]>?h[j][k+1];
            }
        while(m--)
        {
            scanf("%d %d",&i,&j);
            i--,j--,k=0;
            if(s[j]-s[i]>=2)
            {
                a=s[i]+1;
                b=s[j]-1;
                for(c=21;a<b+1;c--)
                    if(go(a,c)<b+1)
                    {
                        k>?=h[c][a];
                        a=go(a,c)+1;
                    }
            }
            if(s[i]!=s[j])
                k>?=rv[i]>?lv[j];
            else
                k>?=(j-i+1);
            printf("%d\n",k);
        }
    }
}
