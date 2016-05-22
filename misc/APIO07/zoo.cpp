#include<cstdio>
int c[10001][32],s[10001][16];
main()
{
    int i,j,k,l,n,m,st,m1,m2;
    //freopen("zoo.in","r",stdin);
    //freopen("zoo.out","w",stdout);
    scanf("%d %d",&n,&m);
    {
        while(m--)
        {
            scanf("%d %d %d",&st,&m1,&m2);
            st--,j=k=0;
            while(m1--)
            {
                scanf("%d",&i),i--;
                for(l=0;l<5;l++)
                    if(i==(st+l)%n)
                        j|=(1<<(4-l));
            }
            while(m2--)
            {
                scanf("%d",&i),i--;
                for(l=0;l<5;l++)
                    if(i==(st+l)%n)
                        k|=(1<<(4-l));
            }
            for(i=0;i<32;i++)
            {
                if((i&j)!=j)c[st][i]++;
                else if(i&k)c[st][i]++;
            }
        }
        for(i=l=0;i<32;i++)
        {
            for(k=0;k<16;k++)
                s[4][k]=0;
            s[4][i%16]=c[0][i];
            for(j=5;j<n;j++)
            {
                for(k=0;k<16;k++)
                    s[j][k]=0;
                for(k=0;k<32;k++)
                    s[j][k%16]>?=(s[j-1][k/2]+c[j-4][k]);
            }
            for(j=1;j<5;j++)
                for(k=0;k<16;k++)
                {
                    s[n-1][k]+=c[n-5+j][((k<<j)+(i>>(5-j)))%32];
                    l>?=s[n-1][k];
                }
        }
        printf("%d\n",l);
    }
}
