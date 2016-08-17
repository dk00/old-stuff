#include<cstdio>
#include<algorithm>
struct X
{
    int l,n;
    bool operator<(X a)const{return l<a.l;}
}s[50];
int n,len,sum,c[30][30];
char go(int m,int l,int i)
{
    if(!sum)return 1;
    if(m<=0)return(sum<=len);
    if(len==l)
    {
        while(!s[i].n)i--;
        s[i].n--,sum-=s[i].l;
        char z=go(m,l-s[i].l,i);
        s[i].n++,sum+=s[i].l;
        return z;
    }
    while(i>=0 && s[i].l>l)i--;
    if(i<0)return go(m-1,len,n);
    if(s[i].l==l)
    {
        s[i].n--,sum-=s[i].l;
        char z=go(m-1,len,n);
        s[i].n++,sum+=s[i].l;
        return z;
    }
    for(;i>=0;i--)
        if(s[i].n)
        {
            s[i].n--,sum-=s[i].l;
            char z=go(m,l-s[i].l,i);
            s[i].n++,sum+=s[i].l;
            if(z)return z;
        }
    return 0;
}
main()
{
    int i,j,k,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=200000000;
        for(i=1;i<n;i++)
            scanf("%d",&s[i].n);
        while(scanf("%d %d %d",&i,&j,&k) && i--+j--+k)
            c[i][j]<?=k,c[j][i]<?=k;
        for(k=0;k<n;k++)
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                    c[i][j]<?=c[i][k]+c[k][j];
        for(i=1,sum=j=0;i<n;i++)
        {
            s[i].l=c[0][i];
            sum+=s[i].l*s[i].n;
            j>?=s[i].l;
        }
        s[0].l=10000;
        std::sort(s,s+n--);
        j>?=sum/3+(sum%3>0);
        for(i=1200,k=600<?sum;j<=k;)
        {
            len=(j+k)/2;
            if(go(2,len,n))i<?=len,k=len-1;
            else j=len+1;
        }
        printf("Test Case #: %d\n",C++);
        if(i<=600)printf("%d mins\n",i*2);
        else puts("Too few trucks");
    }
}
