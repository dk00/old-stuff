#include<cstdio>
struct pt
{
    int x,y;
    pt operator-(pt a)const{return(pt){x-a.x,y-a.y};}
    long long operator*(pt a)const{return x*a.y-y*a.x;}
}s1[101],s2[101];
char ins(pt a1,pt a2,pt b1,pt b2)
{
    if((a1.x>?a2.x)<(b1.x<?b2.x)
    || (a1.x<?a2.x)>(b1.x>?b2.x)
    || (a1.y>?a2.y)<(b1.y<?b2.y)
    || (a1.y<?a2.y)>(b1.y>?b2.y))return 0;
    char a=((a2-a1)*(b1-a1))*((a2-a1)*(b2-a1))<=0,
    b=((b2-b1)*(a1-b1))*((b2-b1)*(a2-b1))<=0;
    return (a && b);
}
char u[1010];
main()
{
    int i,j,n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
            scanf("%d %d %d %d",&s1[i].x,&s1[i].y,&s2[i].x,&s2[i].y),
            u[i]=1;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(i!=j && ins(s1[i],s2[i],s1[j],s2[j]))
                    u[i]=u[j]=0;
        for(i=j=0;i<n;i++)
            j+=u[i];
        printf("%d\n",j);
    }
}

