#include<cstdio>
const int N=999;
int n,sum,s[N];
char go(int d)
{
    if(!sum)return 1;
    int i,j,k,l,t[3];
    for(i=j=k=l=0;i<n;i++)
        if(s[i])
        {
            if(s[i]>1)k++;
            else j++;
        }
    if(!k)return 1-j%2;
    if(j+k==1)return !j;
    if(j==1 && k==1)return 1;
    if(k==2)
    {
        for(i=0;!s[i];i++);
        for(l=i+1;l<n;l++)
            if(s[l]==s[i])return 0;
        
    }
    /*if(k>1  && j+k==3)
    {
        for(i=j=0;i<n;i++)
            if(s[i])t[j++]=s[i];
        if(t[0]==t[1] || t[0]==t[2] || t[1]==t[2])return 1;
        if(j==1)return 0;
        return 1;
    }*/
    //take all
    /*for(i=0;i<n;i++)
        for(j=s[i];j>=s[i]-1 && j>=1;j--)
        {
            s[i]-=j,sum-=j;
            if(!go(d+1))
            {
                s[i]+=j,sum+=j;
                return 1;
            }
            s[i]+=j,sum+=j;
        }*/
    //make one
    
    for(i=0;i<n;i++)
        for(j=s[i];j>=1;j--)
        {
            s[i]-=j,sum-=j;
            if(!go(d+1))
            {
                /*for(i=0;i<n;i++)
                    printf("%d ",s[i]);
                puts("");*/
                //printf("%d %d\n",i,j);
                s[i]+=j,sum+=j;
                return 1;
            }
            s[i]+=j,sum+=j;
        }
    return 0;
}
main()
{
    int i,j,T;
    n=3;
    for(s[0]=1;s[0]<5;s[0]++)
        for(s[1]=1;s[1]<5;s[1]++)
            for(s[2]=1;s[2]<5;s[2]++)
            {
                sum=s[0]+s[1]+s[2];
                printf("%d %d %d %s\n",s[0],s[1],s[2],go(0)?"John":"Brother");
            }
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=sum=0;i<n;i++)
        {
            scanf("%d",s+i);
            sum+=s[i];
        }
        
        puts(go(0)?"John":"Brother");
    }
}
