#include<cstdio>
char dx[128],dy[128],map[30][30],s1[30000],s2[30000],tmp[30000];
int num[128],cnt[128],s[30000],p[30000];
void go(int x,int y,char *path,char *s0)
{
    int i;
    for(i=0;path[i];i++)
    {
        s0[i]=map[x][y];
        x+=dx[path[i]];
        y+=dy[path[i]];
    }
    s0[i++]=map[x][y];
    s0[i]=0;
}
main()
{
    dx['N']=-1,dy['E']=1,dy['W']=-1,dx['S']=1;
    int i,j,k,l,n,m,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            scanf("%s",map[i]);
        scanf("%d %d %d",&m,&i,&j);
        if(m)scanf("%s",tmp);
        else tmp[0]=0;
        go(i-1,j-1,tmp,s1);
        for(j=0;j<128;j++)num[j]=cnt[j]=0;
        for(i=0;s1[i];i++)num[s1[i]]++;
        for(j=1;j<128;j++)num[j]+=num[j-1];
        for(i=0;s1[i];i++)p[num[s1[i]-1]+cnt[s1[i]]++]=i;
        scanf("%d %d %d",&m,&i,&j);
        if(m)scanf("%s",tmp);
        else tmp[0]=0;
        go(i-1,j-1,tmp,s2);

        for(j=0;j<128;j++)num[j]=0;
        for(i=n=0;s2[i];i++)
            if(num[s2[i]-1]+cnt[s2[i]]<num[s2[i]])
                s[n++]=p[num[s2[i]-1]+cnt[s2[i]]++];
        s[0]=-1;
        for(i=0;s2[i];i++)
            for(int x=num[s2[i]-1];x<num[s2[i]];x++)
            {
                int t;
                for(j=1,k=m;j<=k;)
                {
                    t=(j+k)/2;
                    if(s[t-1]<p[i] &&(t==m && p[i]<s[t]))
                        break;
                    if(s[t-1]<p[i])j=t+1;
                    else k=t-1;
                }
                s[t]=p[i];
                if(t==m)m++;
            }
        for(i=0;s1[i];i++);
        for(j=0;s2[j];j++);
        printf("Case %d: %d %d\n",C++,i-m+1,j-m+1);
    }
}
