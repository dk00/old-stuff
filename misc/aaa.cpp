#include<stdio.h>
#include<stdlib.h>
int n,m,get,u[51];
unsigned s[51];
int numcmp(const void *a,const void *b)
{
    return *(unsigned *)b-*(unsigned *)a;
}
bool inline bsearch(int num)
{
    int i,j,k;
    for(i=0,j=n-1;i<=j;)
    {
        k=(i+j)/2;
        if(s[k]==num)
            return 1;
        if(s[k]<num)
            j=k-1;
        else
            i=k+1;
    }
    return 0;
}
void dfs(int d,unsigned num,int i)
{
    if(d<=0)
        return;
    if((num>0 && bsearch(num)) || (num<0 && bsearch(-num)))
    {
        get=1;
        return;
    }
    for(;i<n;i++)
    {
        if(u[i]==0)
        {
            u[i]=1;
            dfs(d-1,num-s[i],i);
            u[i]=-1;
            dfs(d-1,num+s[i],i);
            u[i]=0;
        }
        else if(u[i]>0)
            dfs(d-1,num-s[i],i);
        else
            dfs(d-1,num+s[i],i);
    }
}
main()
{
    int i;
    unsigned m,max;
    scanf("%d",&m);
    for(n=get=max=0;scanf("%d",&s[n])!=EOF;n++)
        if(s[n]>max)
            max=s[n];
    qsort(s,n,sizeof(s[0]),numcmp);
    for(i=m/max;;i++)
    {
        dfs(i,m,0);
        if(get)
            break;
    }
    printf("%d\n",i);
    scanf(" ");
}
