#include<cstdio>
#include<cstring>
int n,m;
int s[100],d[100],c[100][100];
main()
{
    int i,j,k,t;
    char *ptr,tmp[1000];
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&m,&n);
        for(i=0;i<n;i++)
        {
            d[i]=0;
            for(j=0;j<n;j++)
                c[j][i]=0;
            scanf("%s",tmp);
            ptr=strtok(tmp," ");
            sscanf(ptr,"%d",&s[i]);
            while(ptr=strtok(NULL," "))
            {
                sscanf(ptr,"%d",&j);
                c[j][i]=1;
            }
        }
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(c[i][j])
                    d[j]+=s[i];
    }
}
