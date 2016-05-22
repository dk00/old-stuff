#include<cstdio>
#include<cstring>
char s[999999][20],res[999999][20];
char u[128];
char cmp(char a[],char b[])
{
    int i;
    for(i=0;a[i];i++)u[a[i]]=0;
    for(i=0;b[i];i++)u[b[i]]=0;
    for(i=0;a[i];i++)u[a[i]]++;
    for(i=0;b[i];i++)
        if(!u[b[i]]--)return 0;
    return 1;
}
main()
{
    int i,j,n=0,m;
    char tmp[999];
    for(j=0;j<9;j++)
    {
        sprintf(tmp,"%d",j);
        FILE *fp=fopen(tmp,"r");
        while(fscanf(fp,"%s",tmp)==1)
        {
            for(i=0;('A'<=tmp[i] && tmp[i]<='Z')||('a'<=tmp[i] && tmp[i]<='z');i++);
            if(tmp[i] || i>15 || i<4)continue;
            strcpy(s[n++],tmp);
        }
    }
    printf("%d\n",n);
    while(scanf("%s",tmp)==1){
        for(i=m=0;i<n;i++)
            if(cmp(tmp,s[i]))
                strcpy(res[m++],s[i]);
        int p=16,q=1;
        for(j=5;(q || p>0) && j>=4;j--)
            for(i=0;i<m;i++)
                if(strlen(res[i])==j && res[i][0]=='c'
                && res[i][2]=='r' && res[i][2]=='r' && res[i][4]=='s'*/)
                    puts(res[i]),p--,q=0;
    }
}
