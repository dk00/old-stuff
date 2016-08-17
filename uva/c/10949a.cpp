#include<cstdio>
char t[25000],u[25000],map[40][40];
int num[128],cnt[128],s[25000],p[25000];
main()
{
    int i,j,k,n,m,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            scanf("%s",map[i]);
        for(i=1;i<128;i++)num[i]=0;
        scanf("%d %d %d",&m,&i,&j);
        if(m)scanf("%s",t+1);
        else t[1]=0;
        num[t[0]=map[--i][--j]]++;
        for(k=1;t[k];k++)
        {
            if(t[k]=='N')i--;
            if(t[k]=='S')i++;
            if(t[k]=='W')j--;
            if(t[k]=='E')j++;
            num[t[k]=map[i][j]]++;
        }t[k]=0;
        for(i=0;s[i];i++)u[i]=t[i];
        for(i=1;i<128;i++)cnt[i]=0,num[i]+=num[i-1];
        for(i=0,cnt[0]=k;t[i];i++)
            p[num[t[i]-1]+cnt[t[i]]++]=i;
        scanf("%d %d %d",&m,&i,&j);
        if(m)scanf("%s",t+1);
        else t[1]=0;
        t[0]=map[--i][--j];
        for(k=1;t[k];k++)
        {
            if(t[k]=='N')i--;
            if(t[k]=='S')i++;
            if(t[k]=='W')j--;
            if(t[k]=='E')j++;
            t[k]=map[i][j];
        }
        t[k]=0,s[0]=-1;
        for(cnt[1]=0;t[cnt[1]];cnt[1]++);
        for(k=0,n=1;t[k] && cnt[0]-n+1>0 && cnt[1]-n+1>0;k++)
        {
            for(int x=num[t[k]]-1,m=n;x>=num[t[k]-1];x--)
            {
                /*for(i=1,j=m;i<=j;)
                {
                    m=(i+j)/2;
                    if(s[m-1]<p[x] &&(m==n || p[x]<=s[m]))
                        break;
                    if(s[m-1]<p[x])i=m+1;
                    else j=m-1;
                }*/
                for(;m>=1;m--)
                    if(s[m-1]<p[x] &&(m==n || p[x]<=s[m]))
                        break;
                s[m]=p[x];
                if(m==n)n++;
            }
        }
        printf("Case %d: %d %d\n",C++,cnt[0]-n+1,cnt[1]-n+1);
    }
}
