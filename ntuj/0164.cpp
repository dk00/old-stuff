#include<cstdio>
#include<cstring>
char g[][19]={"Rock","Fire","Scissors","Snake","Human","Tree","Wolf","Sponge","Paper",
"Air","Water","Dragon","Devil","Lightning","Gun","Draw"};
int find(char s[])
{
    for(int i=0;i<15;i++)
        if(!strcmp(s,g[i]))return i;
}
main()
{
    int i,j,n,s[99],win[99],lose[99];
    char tmp[99];
    while(scanf("%d",&n)==1 && n)
    {
        for(j=0;j<15;j++)
            s[j]=win[j]=lose[j]=0;
        for(i=0;i<n;i++)
        {
            scanf("%s",tmp);
            s[find(tmp)]++;
        }
        for(j=0;j<15;j++)
            if(s[j])for(i=1;i<=7;i++)
            {
                if(s[(j+i)%15])win[j]=1;
                lose[(j+i)%15]=1;
            }
        for(i=0;i<15;i++)
            if(win[i] && !lose[i])
                break;
        puts(g[i]);
    }
}
