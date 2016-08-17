#include<cstdio>
#include<cstring>
#include<algorithm>
struct E
{
    short v;
    char l;
    bool operator<(E x)const{return l<x.l;}
};
short c1[200][200],c2[200][200];
char v1[200],v2[200];
void go(int n,short c[200][200],char v[200],char *p)
{
    for
}
int go(char s[],short c[200][200],char v[200])
{
    int i,j,n;
    int num[200],tmp[200];
    for(i=j=n=0;s[i];i++)
    {
        if(s[i]=='(')
            tmp[j++]=s[i-1];
        else if(s[i]==')')j--;
        else
        {
            num[n]=0;
            c[n][num[n]++]=tmp[j-1];
            v[c[tmp[j-1]][num[tmp[j-1]]++]=n++]=s[i];
        }
    }
    for(i=0;i<n;i++)
        c[i][num[i]]=-1;
    return n;
}
main()
{
    int i,T;
    char s[1000],p1[250],p2[250];
    scanf("%d\n",&T);
    while(T--)
    {
        gets(s);
        n1=go(s,c1,v1);
        gets(s);
        n2=go(s,c2,v2);
        if(n1!=n2)goto diff;
        for(i=0;i<n1;i++)
        {
            memset(p1,0,sizeof(p1));
            go(n1,c1,v1,p1);
            for(j=0;j<n1;j++)
            {
                memset(p1,0,sizeof(p2));
                go(n2,c2,v2,p2);
                if(!strcmp(p1,p2))goto same;
            }
        }
        same:puts("same");
        continue;
        diff:puts("different");
    }
}
