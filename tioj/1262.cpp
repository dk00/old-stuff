#include<1262_word.h>
int guess(const char a[],int m)
{
    int last=-1,now;
    while(1)
    {
        now=Guess(a,m);
        if(now==last)return last;
        last=now;
    }
}
int max;
char s[105],ans[105];
void go(int d)
{
    char i;
    for(i='a';i<='z';i++)
    {
        s[d]=i;
        if(guess(s,d+1))
            go(d+1);
    }
    s[d]=0;
    if(d>max)
        max=d,strcpy(ans,s);
}
main()
{
    Initialize();
    max=0;
    go(0);
    Report(ans);
}
