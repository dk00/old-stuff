/*
ID: s0000151
PROG: char
LANG: C++
*/
#include<cstdio>
class lchar
{
    int cmp(char *a,char *b)
    {
        int i,j;
        for(i=j=0;i<20;i++)
            j+=(a[i]!=b[i]);
        return j;
    }
public:
    int d[21];
    char s[20][21];
    void get(FILE *fp)
    {
        for(int i=0;i<20;i++)
            fscanf(fp,"%s",s[i]);
    }
    int cmp19(char t[][21])
    {
        int i,now,min;
        for(i=now=0;i<19;i++)
            now+=(d[i]=cmp(s[i],t[i]));
        for(i=18,min=now;i>=0;i--)
        {
            now+=cmp(s[i+1],t[i])-d[i];
            min<?=now;
        }
        return min;
    }
    int cmp20(char t[][21])
    {
        int i,j;
        for(i=j=0;i<20;i++)
            j+=cmp(s[i],t[i]);
        return j;
    }
    int cmp21(char t[][21])
    {
        int i,now,min;
        for(i=now=0;i<20;i++)
            now+=(d[i]=cmp(s[i],t[i]));
        for(i=19,min=now;i>=0;i--)
        {
            now+=cmp(t[i+1],s[i])-d[i];
            min<?=now;
        }
        return min;
    }
}font[27];
const char table[]=" abcdefghijklmnopqrstuvwxyz";
char c[1201];
int d[1201],p[1201];
void print(int n)
{
    if(p[n]>0)
        print(p[n]);
    putchar(c[n]);
}
main()
{
    const int inf=2147483647;
    int i,j,k,n;
    char s[1201][21];
    FILE *fp=fopen("font.in","r");
    fscanf(fp,"%s",font[0].s[0]);
    for(i=0;i<27;i++)
        font[i].get(fp);
    fclose(fp);
    freopen("char.in","r",stdin);
    freopen("char.out","w",stdout);
    scanf("%d",&n);
    for(i=d[0]=0;i<n;i++)
    {
        d[i+1]=inf;
        scanf("%s",s[i]);
    }
    for(i=0;i+19<=n;i++)
    {
        if(d[i]>=inf)continue;
        for(j=0;j<27;j++)
        {
            k=font[j].cmp19(s+i);
            if(k<=114 && d[i]+k<d[i+19])
            {
                p[i+19]=i,c[i+19]=table[j];
                d[i+19]=(d[i]+k);
            }
        }
        if(i+20<=n)
            for(j=0;j<27;j++)
            {
                k=font[j].cmp20(s+i);
                if(k<=120 && d[i]+k<d[i+20])
                {
                    p[i+20]=i,c[i+20]=table[j];
                    d[i+20]=(d[i]+k);
                }
            }
        if(i+21<=n)
            for(j=0;j<27;j++)
            {
                k=font[j].cmp21(s+i);
                if(k<=120 && d[i]+k<d[i+21])
                {
                    p[i+21]=i,c[i+21]=table[j];
                    d[i+21]=(d[i]+k);
                }
            }
    }
    print(n),puts("");
}
