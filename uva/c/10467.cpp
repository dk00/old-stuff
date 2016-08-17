#include<cstdio>
struct node
{
    char s;
    int l,r,h;
}s[1000];
void printspc(int n)
{
    while(n--)putchar(' ');
}
int go(int d,int st,int ed)
{
    if(st>=ed)
    {
        s[st].h=d;
        return st;
    }
    int i,cnt=0;
    for(i=ed;i>=st;i--)
    {
        if(s[i].s=='(')
            cnt++;
        if(s[i].s==')')
            cnt--;
        if(cnt)continue;
        if(s[i].s=='+' || s[i].s=='-')
            break;
    }
    if(i<st)
    for(i=ed;i>=st;i--)
    {
        if(s[i].s=='(')
            cnt++;
        if(s[i].s==')')
            cnt--;
        if(cnt)continue;
        if(s[i].s=='*' || s[i].s=='/')
            break;
    }
    if(i<st)
    {
        s[st].h=d;
        s[st].l=go(d+1,st+1,ed-1);
        s[st].r=ed;
        return st;
    }
    s[i].h=d;
    s[i].l=go(d+1,st,i-1);
    s[i].r=go(d+1,i+1,ed);
    return i;
}
const char exp[]="E|T|F|i";
int q[300];
main()
{
    int i,j,k,n,max,root;
    char tmp[1000];
    while(scanf("%s",tmp)==1)
    {
        for(n=0;tmp[n];n++)
            q[n]=-1,s[n].s=tmp[n];
        root=go(0,0,n-1);
        max=root;
        for(i=0;;i++)
        {
            tmp[0]=' ';
            for(max=n-1;max>=0;max--)
            {
                if(q[max]>=0 && q[max]<=6)
                    break;
                if(q[max]>9)
                    break;
                if(i/2==s[max].h || i/2-1==s[max].h)
                    break;
            }
            if(max<0)break;
            for(k=0;k<=max;k++)
            {
                if(q[k]>9)
                {
                    printf("=");
                    if(k<max)printf("==");
                    q[k]-=19;
                    continue;
                }
                else if(q[k]>=0 && q[k]<=6)
                {
                    putchar(exp[q[k]++]);
                    if(k<max)printf("  ");
                    continue;
                }
                else if(i/2==s[k].h)
                {
                    if(s[k].s=='+' || s[k].s=='-')
                    {
                        if(i%2==0)
                        {
                            putchar('E');
                            for(j=s[k].l;j<=s[k].r;j++)
                                if(j!=k)
                                    q[j]+=19;
                        }
                        else
                        {
                            putchar('|'),tmp[0]='=';
                            if(s[s[k].l].s=='i' || s[s[k].l].s=='(')
                                q[s[k].l]+=1;
                            if(s[s[k].r].s=='i' || s[s[k].r].s==')')
                                q[s[k].r]+=3;
                        }
                    }
                    if(s[k].s=='*' || s[k].s=='/')
                    {
                        if(i%2==0)
                        {
                            putchar('T'),tmp[0]='=';
                            for(j=s[k].l;j<=s[k].r;j++)
                                if(j!=i)
                                    q[j]+=19;
                        }
                        else
                        {
                            putchar('|'),tmp[0]='=';
                            if(s[s[k].l].s=='i' || s[s[k].l].s=='(')
                                q[s[k].l]+=3;
                            if(s[s[k].r].s=='i' || s[s[k].r].s==')')
                                q[s[k].r]+=5;
                        }
                    }
                    if(s[k].s=='(')
                    {
                        if(i%2==0)
                            for(j=k;j<=s[k].r;j++)
                                q[j]+=19;
                        else putchar('|'),tmp[0]='=';
                    }
                }
                else if(i/2+1==s[k].h
                    && (s[k].s=='+' || s[k].s=='-' ||
                       s[k].s=='*' || s[k].s=='/' ||
                       s[k].s=='(' || s[k].s==')'))
                        putchar(s[k].s);
                else putchar(' ');
                if(k<max)printf("%c%c",tmp[0],tmp[0]);
                tmp[0]=' ';
            }
            puts("");
        }
        puts("");
    }
}
