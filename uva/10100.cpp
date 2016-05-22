#include<cstdio>
#include<cstring>
char tt[256],s1[1001][21],s2[1001][21];
int s[1001][1001];
int max(int a,int b){return a>?b;}
main()
{
    int i,j,k,n1,n2,C=1;
    char *p,tmp1[2000],tmp2[2000];
    for(i=0;i<256;i++)
        tt[i]=' ';
    for(i='a';i<='z';i++)
        tt[i]=i;
    for(i='A';i<='Z';i++)
        tt[i]=i;
    for(i='0';i<='9';i++)
        tt[i]=i;
    while(gets(tmp1) && gets(tmp2))
    {
        for(i=0;tmp1[i];i++)
            tmp1[i]=tt[tmp1[i]];
        for(i=0;tmp2[i];i++)
            tmp2[i]=tt[tmp2[i]];
        p=strtok(tmp1," ");
        for(n1=1;p;n1++)
        {
            strcpy(s1[n1],p);
            p=strtok(NULL," ");
        }
        p=strtok(tmp2," ");
        for(n2=1;p;n2++)
        {
            strcpy(s2[n2],p);
            p=strtok(NULL," ");
        }
        for(i=1;i<n1;i++)
            for(j=1;j<n2;j++)
                if(!strcmp(s1[i],s2[j]))
                    s[i][j]=s[i-1][j-1]+1;
                else
                    s[i][j]=max(s[i-1][j],s[i][j-1]);
        printf("%2d. ",C++);
        k=s[n1-1][n2-1];
        if(k)
            printf("Length of longest match: %d\n",k);
        else
            puts("Blank!");
    }
}
