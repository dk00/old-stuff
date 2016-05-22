#include<cstdio>
int gcd(int a,int b,int a1,int a2,int b1,int b2)
{
    if(a%b==0)return n1;
    return gcd(b,a%b,b1,b2,a1-a/b*b1,a2-a/b*b2);
}
char go(int a1,int a2,int b1,int b2)
{
    int a3,b3;
    a3=gcd(a2,b2,1,0,0,1);
    b3=a2*a3/b2;
    
}
main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d %d",&m,&n,&a,&b);
        for(i=0;i<n;i++)
            scanf("%d %d",s2+i,s1+i);
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=go(s1[i],s2[i],s1[j],s2[j]);
    }
    
    
}
