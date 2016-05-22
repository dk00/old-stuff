#include<cstdio>
#include<cstring>
long long an,len,s[25][30][30],s1[25][30],sum[25];
char al[99],u[128],c1[30][30],c2[30][30][30],f[1000][30];
bool valid(int a,int b,int c){return c1[a][b] && c2[a][b][c];}
void count(int x)
{
    int i,j,l1=0,l2=0;
    char tmp[99];
    for(j=0;j<len;j++)
    {
        for(i=1;i<an;i++)
        {
            if(!c1[l2][i] || !c2[l1][l2][i])continue;
            if(x<=s1[len-j][i])break;
            x-=s1[len-j][i];
        }
        l1=l2;
        tmp[j]=al[l2=i];
    }
    tmp[j]=0;
    puts(tmp);
}
long long find(char tmp[])
{
    int i,j,l1=0,l2=0;
    long long sum=0;
    for(j=0;tmp[j];j++)
    {
        for(i=1;al[i]<tmp[j];i++)
            if(c1[l2][i] && c2[l1][l2][i])
                sum+=s1[len-j][i];
        l1=l2,l2=u[tmp[j]];
    }
    return sum;
}
main()
{
    int i,j,k,l,n,m,T;
    char tmp[99];
    scanf("%d",&T);
    while(T--)
    {
        for(i=0;i<128;i++)u[i]=1;
        for(i=0;i<25;i++)
            for(j=0;j<900;j++)
                s[i][j/30][j%30]=0;
        for(i=0;i<30;i++)
            for(j=0;j<30;j++)
                c1[i][j]=1;
        for(i=0;i<30;i++)
            for(j=0;j<30;j++)
                for(k=0;k<30;k++)
                    c2[i][j][k]=1;
        scanf("%d %d",&n,&m);
        for(i=j=0;i<n;i++)
        {
            scanf("%s",tmp);
            if(tmp[1])strcpy(f[j++],tmp);
            else u[tmp[0]]=0;
        }

        al[0]='$';
        for(i='a',an=1;i<='z';i++)
            if(u[i])al[u[i]=an++]=i;
        while(j--)
            if(f[j][2])
                c2[u[f[j][0]]][u[f[j][1]]][u[f[j][2]]]=0;
            else
                c1[u[f[j][0]]][u[f[j][1]]]=0;
        s[0][0][0]=1;
        for(i=1;i<=20;i++)
        {
            sum[i]=0;
            for(j=1;j<an;j++)
            {
                s1[i][j]=0;
                for(k=0;k<an;k++)
                {
                    if(!c1[j][k])continue;
                    for(l=0;l<an;l++)
                        if(c2[j][k][l])
                            s[i][j][k]+=s[i-1][k][l];
                    s1[i][j]+=s[i][j][k];
                }
                sum[i]+=s1[i][j];
            }
        }
        while(m--)
        {
            scanf("%s",tmp);
            if(tmp[0]>='0' && tmp[0]<='9')
            {
                sscanf(tmp,"%d",&i);
                for(len=0;i>sum[len];len++)
                    i-=sum[len];
                count(i);
            }
            else
            {
                for(i=j=1;tmp[i];i++)
                    j+=sum[i];
                len=i;
                printf("%d\n",j+find(tmp));
            }
        }
    }
}
