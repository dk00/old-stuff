#include<cstdio>
int n,s[10],tmp[12][10];
int h()
{
    int i,j;
    for(i=j=1;i<n;i++)
        if(s[i]!=s[i-1]+1)j++;
    j--;
    return (j+2)/3;
}
void copy(int d)
{
    for(int i=0;i<n;i++)
        tmp[d][i]=s[i];
}
void undo(int d)
{
    for(int i=0;i<n;i++)
        s[i]=tmp[d][i];
}
void move(int st,int len,int pos)
{
    int i,j,k,x[10];
    for(i=0;i<len;i++)
        x[pos+i]=s[st+i];
    for(i=j=0;i<n;)
    {
        if(j==pos)j+=len;
        if(i==st)i+=len;
        x[j++]=s[i++];
    }
    for(i=0;i<n;i++)
        s[i]=x[i];
}
int max,next,_n=0;
char go(int d=0)
{
    _n++;
    int tmp=h();
    if(d+tmp>max)
    {
        next<?=d+tmp;
        return 0;
    }
    if(tmp==0)return 1;
    int i,j,k;
    for(i=0;i<n;i++)
        for(j=n-i-1;j>=0;j--)
            for(k=0;k<n-j;k++)
            {
                copy(d);
                move(i,j+1,k);
                if(go(d+1))
                    return 1;
                undo(d);
            }
    return 0;
}
main()
{
    int i,C=1;
    while(scanf("%d",&n) && n)
    {
        _n=0;
        for(i=0;i<n;i++)
            scanf("%d",s+i);
        next=h();
        while(1)
        {
            max=next,next=100;
            if(max>=n/2+1)break;
            if(go())break;
        }
        printf("Case %d: %d\n",C++,max,_n);
    }
}
