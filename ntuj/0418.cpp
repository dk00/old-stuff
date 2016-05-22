#include<cstdio>
char x[99999],tmp[99999];
main()
{
    int i,j,n,m;
    while(~scanf("%d",&n))
    {
        for(i=j=0;i<n;i++)
        {
            scanf("%s",tmp);
            if(!i)for(m=0;tmp[m];m++);
            for(j=0;tmp[j];j++)
                x[n*j+i]=tmp[j];
        }
        x[n*m]=0;
        //puts(x);
        for(i=0;x[i]=='_';i++);
        for(j=n*m-1;j>=i;j--)
        {
            if(x[j]=='_')putchar(' ');
            else if(x[j]=='\\')putchar('\n');
            else putchar(x[j]);
        }
        puts("\n");
    }
}
