#include<cstdio>
char s[1000]={0,2};
char go(int v)
{
    if(v<=729 && s[v])
        return s[v]-1;
    if(v<=729)s[v]=1;
    int i,j;
    for(i=v,j=0;i>0;i/=10)
        j+=(i%10)*(i%10);
    if(v<=729)s[v]=go(j)+1;
    else return go(j);
    return s[v]-1;
}
main()
{
    int i,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&i);
        if(go(i))
            printf("Case #%d: %d is a Happy number.\n",C++,i);
        else
            printf("Case #%d: %d is an Unhappy number.\n",C++,i);
    }
}
