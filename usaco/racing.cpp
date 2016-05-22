/*
PROB:racing
LANG:C++
*/
#include<cstdio>
main()
{
    freopen("racing.in","r",stdin);
    freopen("racing.out","w",stdout);
    int i,j,n,m,u,f,d;
    char tmp[9];
    scanf("%d %d %d %d %d",&m,&n,&u,&f,&d);
    for(i=0;n--;)
    {
        scanf("%s",tmp);
        if(tmp[0]=='f')j=2*f;
        else j=u+d;
        if(m<j)m=0;
        else m-=j,i++;
    }
    printf("%d\n",i);
}
