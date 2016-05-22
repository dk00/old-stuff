#include<cstdio>
#include<string>
using namespace std;
char tmp[999];
char go(int v)
{
    if(u[v])return 0;
    u[v]=1;
    if(s[v].a==v)return 1;
    if(s[v].a<0)return 0;
    if(go(s[v].a))
        return 1;
    else if(go(s[v].b))
    {
        s[v].a=s[v].b;
        return 1;
    }
    return 0;
}
main()
{
    int i,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
            u[i]=0;
            scanf("%s",tmp);
            if(tmp[0]=='C')
            {
                scanf("%[\"]",tmp);
                scanf("%[^\"]",tmp);
                s[i].text=tmp;
                scanf("%[\"]",tmp);
                scanf("%d %d",&s[i].a,&s[i].b);
            }
            else
            {
                scanf("%[\"]",tmp);
                scanf("%[^\"]",tmp);
                s[i].text=tmp;
                scanf("%[\"]",tmp);
                scanf("%s",tmp);
                if(tmp[0]=='H')
                    s[i].a=i;
                else
                    s[i].a=-1;
            }
        }
        printf("STORY %d\n",C++);
        go(0);
        for(i=0;s[i].a!=i;i=s[i].a)
            puts(s[i].text);
    }
}
