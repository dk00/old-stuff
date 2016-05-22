#include<cstdio>
int st,ed,s[100000],path[10000][2];
int calc()
{
    int i,j,k;
    j=k=0;
    for(i=st;i<=ed;i++)
    {
        if(s[i] && j!=s[i])
            j=s[i],k++;
    }
    return (k-1)/2;
}
void move(int i,int j)
{
    s[j]=s[i],s[i]=0;
    s[j+1]=s[i+1],s[i+1]=0;
    if(i<j)
    {
        if(i==st)
            while(s[st]==0)st++;
        if(j+1>ed)
            ed=j+1;
    }
    else
    {
        if(j<st)
            st=j;
        if(i+1==ed)
            while(s[ed]==0)ed--;
    }
}
void show()
{
    char stone[]="  \0¡³\0¡´\0";
    for(int i=st;i<=ed;i++)
        printf("%s",stone+s[i]*3);
    puts("");
}
int next,bound;
int go(int d)
{
    int i,j;
    i=d+calc();
    if(i>bound)
    {
        if(i<next || next==bound)
            next=i;
        return 0;
    }
    if(i==d)
        return 1;
    for(i=st;i<ed;i++)
    {
        if(s[i] && s[i+1])
            for(j=st-2;j<=ed+1;j++)
            {
                if(s[j] || s[j+1])
                    continue;
                move(i,j);
                path[d][0]=i;
                path[d][1]=j;
                int yn=go(d+1);
                move(j,i);
                if(yn)
                    return 1;
            }
    }
    return 0;
}
main()
{
    char tmp[1000];
    while(scanf("%s",tmp)==1)
    {
        for(int i=0;i<100000;i++)
            s[i]=0;
        st=50000;
        for(ed=0;tmp[ed];ed++)
            if(tmp[ed]=='b')
                s[st+ed]=1;
            else
                s[st+ed]=2;
        ed+=st;
        next=calc();
        do bound=next;while(!go(0));
        printf("%d\n",bound);
        show();
        for(int i=0;i<bound;i++)
            move(path[i][0],path[i][1]),show();
    }
}
