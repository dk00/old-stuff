#include<cstdio>
int n,s[300],c[300][300];
void inv(int st,int ed)
{
    int i;
    while(st<ed)
    {
        i=s[st];
        s[st++]=s[ed];
        s[ed--]=i;
    }
}
void spin(int k)
{
    int i,tmp[300];
    for(i=0;i<n;i++)
        tmp[i]=s[(i+k)%n];
    for(i=0;i<n;i++)
        s[i]=tmp[i];
}
main()
{
    int i,j;
    char tmp[1000];
    while(scanf("%d%c",&n,tmp)==2)
    {
        for(i=0;i<n;i++)
            for(j=0,s[i]=i;j<n;j++)
                c[i][j]=0;
        while(gets(tmp) && sscanf(tmp,"%d %d",&i,&j)==2)
            c[i-1][j-1]=c[j-1][i-1]=1;
        while(1)
        {
            for(i=0;c[s[i]][s[i+1]] && i<n-1;i++);
            if(i>=n-1)
                break;
            spin(i);
            for(j=2;!c[0][s[j]] && !c[1][s[j+1]];j++);
            inv(1,j);
        }
        for(i=0;i<n;i++)
            printf("%d ",s[i]+1);
        printf("%d\n",s[0]+1);
    }
}
