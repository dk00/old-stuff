#include<cstdio>
int n,m;
char path[100];
bool go(int d)
{
    if(d>m)return 1;
    int i,j;
    if(d<n)
    {
        for(i=(d==1);i<10;i++)
        {
            path[d-1]=i+'0';
            if(go(d+1))return 1;
        }
        return 0;
    }
    for(i=1,j=0;i<d;i++)
        j=(j+path[i-1]-'0')*10%d;
    if((d-j)%d>=10)return 0;
    path[d-1]=(d-j)%d+'0';
    if(d==1)path[0]='1';
    while(path[d-1]<='9')
    {
        if(go(d+1))return 1;
        path[d-1]+=d;
    }
    return 0;
}
main()
{
    int i,j;
    printf("s[30][30][30]={");
    printf("{\"\"");
    for(j=1;j<30;j++)
        printf(",\"\"");
    printf("}");
    for(i=1;i<30;i++)
    {
        printf(",\n{\"\"");
        for(j=1;j<i;j++)
        {
            m=i,n=j;
            if(go(1))
                printf(",\"%s\"",path);
            else
                printf(",\"-1\"");
        }
        for(;j<30;j++)
            printf(",\"\"");
        printf("}");
    }
    printf("}");
}
