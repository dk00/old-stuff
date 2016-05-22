/*
TASK:gift1
LANG:C++
*/
#include<cstdio>
#include<cstring>
int n,s[99];
char name[99][99];
int find(char tmp[])
{
    for(int j=0;j<n;j++)
        if(!strcmp(tmp,name[j]))return j;
}
main()
{
    freopen("gift1.in","r",stdin);
    freopen("gift1.out","w",stdout);
    int i,j,k,l;
    char tmp[99];
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%s",name[i]);
    for(i=0;i<n;i++)
    {
        scanf("%s",tmp);
        j=find(tmp);
        scanf("%d %d",&k,&l);
        if(l==0)continue;
        s[j]-=k/l*l;
        k/=l;
        while(l--)
        {
            scanf("%s",tmp);
            j=find(tmp);
            s[j]+=k;
        }
    }
    for(i=0;i<n;i++)
        printf("%s %d\n",name[i],s[i]);
    scanf(" ");
}
