#include<cstdio>
int n,eq,s[20],r[20],t[2],p[2][20];
char op[20][3],tmp[20];
char go(int j,int num)
{
    if(j>=n && num==0)
    {
        for(int i=0;i<n;i++)
        {
            if(i)printf(" %s ",op[i]);
            printf("%d",p[r[i]<0][t[r[i]<0]++]);
        }
        puts("");
        return 1;
    }
    for(int i=-1;i<2;i+=2)
        if(t[i<0])
        {
            p[i<0][--t[i<0]]=s[j];
            if(go(j+1,num+s[j]*i))return 1;
            t[i<0]++;
        }
    return 0;
}
main()
{
    int sum;
    while(scanf("%d",s)==1)
    {
        eq=20,t[0]=r[0]=1,t[1]=0,sum=s[0];
        for(n=tmp[0]=1;tmp[0]!='\n';n++)
        {
            scanf("%s %d%c",op+n,s+n,tmp);
            if(op[n][0]=='+')r[n]=1;
            else if(op[n][0]=='-')r[n]=-1;
            else eq=n,r[n]=1;
            if(n>=eq)r[n]*=-1;
            t[r[n]<0]++,sum+=s[n];
        }
        if(sum%2 || !go(0,0))
            puts("no solution");
    }
}
