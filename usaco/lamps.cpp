#include<cstdio>
int i,n,c,p,s[101],s1[101],s2[101];
void b0(){for(i=1;i<=n;i++)s[i]=1;}
void b1(){for(i=1;i<=n;i++)s[i]^=1;}
void b2(){for(i=1;i<=n;i++,i++)s[i]^=1;}
void b3(){for(i=2;i<=n;i++,i++)s[i]^=1;}
void b4(){for(i=1;i<=n;i++,i++,i++)s[i]^=1;}
void b5()
{
    for(i=0;s1[i]>=0;i++)
        if(s[s1[i]]==0)return;
    for(i=0;s2[i]>=0;i++)
        if(s[s2[i]]==1)return;
    for(p++,i=1;i<=n;i++)printf("%d",s[i]);puts("");
}
main()
{
    freopen("lamps.in","r",stdin);
    freopen("lamps.out","w",stdout);
    scanf("%d %d",&n,&c);
    for(i=0;scanf("%d",s1+i) && s1[i]>=0;i++);
    for(i=0;scanf("%d",s2+i) && s2[i]>=0;i++);
    if(c)b0(),b1(),b5();
    if(c>1)b0(),b3(),b4(),b5();
    if(c)b0(),b2(),b5(),b0(),b4(),b5();
    if(c>1)b0(),b1(),b4(),b5();
    if(c)b0(),b3(),b5();
    if(c>1)b0(),b2(),b4(),b5();
    if(c%2==0)b0(),b5();
    if(!p)puts("IMPOSSIBLE");
    scanf(" ");
}
/*
PROB:lamps
LANG:C++
*/
