#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
void sort(int *s,int n){sort(s,s+n);}
int makeset(int *s1,int *u1,int *s2,int n2)
{
    int n1;
    sort(s2,n2);
    for(int i=0,n1=0;i<n2;i++)
        if(!i || s2[i]!=s2[i-1])
            s1[n1]=s2[i],u1[n1++]=1;
        else u1[n1-1]++;
    return n1;
}
int getseq(int *s)
{
    int n=0;
    char tmp[10000],*p;
    scanf("%s",tmp);
    p=strtok(tmp+1,",");
    while(p)
    {
        sscanf(p,"%d",&s[n++]);
        p=strtok(NULL,",");
    }
    return n;
}
main()
{
    char cmd[1000];
    int i,j,k;
    int n1,s1[1000];
    while(scanf("%s",cmd)==1)
    {
        if(!strcmp(cmd,"degrade"))
        {
            n1=getseq(s1);
            sort(s1,n1);
            printf("{%d",s1[0]);
            for(i=1;i<n1;i++)
                printf(",%d",s1[i]);
            puts("}");
        }
    }
}
