#include<cstdio>
int pn,min,p[1000],flag[1000],s[1000001];
long long path[1000],tmp[1000001];
bool notp[1500];
void go(int d,int num,int i)
{
    if(num>1000000 || num>=2000000/min)return;
    for(;i<pn;i++)
    {
        if(d==0)min=p[i];
        path[d]=p[i];
        go(d+1,num*p[i],i+1);
    }
    if(d==0)return;
    int j,k;
    long long u;
    tmp[0]=num;
    for(k=0;k<d;k++)
        flag[k]=0;
    for(j=1;tmp[j-1]<1000000;)
    {
        for(k=0,u=-1;k<d;k++)
        {
            while(tmp[flag[k]]*path[k]<=tmp[j-1])flag[k]++;
            u<?=(tmp[flag[k]]*path[k]);
            if(u<0)u=tmp[flag[k]]*path[k];
        }
        tmp[j++]=u;
        s[tmp[j-2]]=tmp[j-1];
    }
}
main()
{
    int i,j;
    p[0]=2;
    for(i=3,pn=1;i<1414;i++,i++)
    {
        if(notp[i])continue;
        for(j=i*3;j<1414;j+=i*2)notp[j]=1;
        p[pn++]=i;
    }
    for(i=0,min=1;i<=1000000;i++)
        s[i]=0;
    go(0,1,0);
    while(scanf("%d",&i)==1)
        if(s[i])printf("%d\n",s[i]);
        else puts("Not Exist!");
}
