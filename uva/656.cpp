#include<cstdio>
const char cmd[][4]={"ADD","SUB","MUL","DIV","DUP"};
int n,h,min,s[10][110],a[10],b[10],p[110];
bool check()
{
    for(int i=0;i<n;i++)
        if(s[i][0]!=b[i])return 0;
    return 1;
}
bool go(int d)
{
    int i,t1[10],t2[10];
    if(d>=min)
        return check();
    if(h>1)
    {
        for(i=0;i<n;i++)
            if(s[i][h-1]+s[i][h-2]>30000 || s[i][h-1]+s[i][h-2]<-30000)
                break;
        if(i>=n)
        {
            p[d]=0;
            for(i=0;i<n;i++)
                t1[i]=s[i][h-1],t2[i]=s[i][h-2],s[i][h-2]+=s[i][h-1];
            h--;
            if(go(d+1))return 1;
            for(i=0,h++;i<n;i++)s[i][h-1]=t1[i],s[i][h-2]=t2[i];
        }
        for(i=0;i<n;i++)
            if(!s[i][h-1])
                break;
        if(i>=n)
        {
            p[d]=3;
            for(i=0;i<n;i++)
                t1[i]=s[i][h-1],t2[i]=s[i][h-2],s[i][h-2]/=s[i][h-1];
            h--;
            if(go(d+1))return 1;
            for(i=0,h++;i<n;i++)s[i][h-1]=t1[i],s[i][h-2]=t2[i];
        }
    }
    if(h!=min-d)
    {
        p[d]=4;
        for(i=0;i<n;i++)
            s[i][h]=s[i][h-1];
        h++;
        if(go(d+1))return 1;
        h--;
    }
    if(h>1)
    {
        for(i=0;i<n;i++)
            if(s[i][h-1]*s[i][h-2]>30000 || s[i][h-1]*s[i][h-2]<-30000)
                break;
        if(i>=n)
        {
            p[d]=2;
            for(i=0;i<n;i++)
                t1[i]=s[i][h-1],t2[i]=s[i][h-2],s[i][h-2]*=s[i][h-1];
            h--;
            if(go(d+1))return 1;
            for(i=0,h++;i<n;i++)s[i][h-1]=t1[i],s[i][h-2]=t2[i];
        }
        for(i=0;i<n;i++)
            if(s[i][h-1]-s[i][h-2]>30000 || s[i][h-1]-s[i][h-2]<-30000)
                break;
        if(i>=n)
        {
            p[d]=1;
            for(i=0;i<n;i++)
                t1[i]=s[i][h-1],t2[i]=s[i][h-2],s[i][h-2]-=s[i][h-1];
            h--;
            if(go(d+1))return 1;
            for(i=0,h++;i<n;i++)s[i][h-1]=t1[i],s[i][h-2]=t2[i];
        }
    }
    return 0;
}
main()
{
    int i,C=1;h=1;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)scanf("%d",&a[i]),s[i][0]=a[i];
        for(i=0;i<n;i++)scanf("%d",&b[i]);
        for(min=0;min<=10;min++,min++)
            if(go(0))break;
        printf("Program %d\n",C++);
        if(min==0)
            puts("Empty sequence");
        else if(min<=10)
        {
            printf("%s",cmd[p[0]]);
            for(i=1;i<min;i++)
                printf(" %s",cmd[p[i]]);
            puts("");
        }
        else puts("Impossible");
        puts("");
    }
}
