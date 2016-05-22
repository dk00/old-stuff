#include<cstdio>
#include<cstring>
const char end[]="Begin the Escape execution at the Break of Dawn";
char s[80];
void decode(char a,char b,char c,char from[],char to[])
{
    int i,j=0;
    for(i=0;i<a;i++)
        to[j++]=from[i];
    for(i=b+1;i<c;i++)
        to[j++]=from[i];
    for(i=a+1;i<b;i++)
        to[j++]=from[i];
    for(i=c+1;s[i];i++)
        to[j++]=from[i];
    to[j]=0;
}
char test1(char s[])
{
    int i,j,k;
    char tmp[50];
    for(i=0;i<50;i++)tmp[i]=0;
    for(i=j=0;s[i];i=j++)
    {
        if(s[i]=='C' || s[i]=='O' || s[i]=='W')continue;
        for(k=0;end[k];k++)
        {
            for(j=0;s[i+j] && s[i+j]!='C' && s[i+j]!='O' &&
            s[i+j]!='W' && end[k+j];j++)
                if(s[i+j]!=end[k+j])break;
            if(s[i+j] && s[i+j]!='C' && s[i+j]!='O' && s[i+j]!='W')
                continue;
            for(j=0;s[i+j] && s[i+j]!='C' && s[i+j]!='O' && s[i+j]!='W';j++)
                tmp[k+j]++;
        }
        for(j=i;s[j]!='C' && s[j]!='O' && s[j]!='W' && s[j];j++);
    }
    for(i=0;end[i];i++)
        if(!tmp[i])return 1;
    return 0;
}
char test2(char a,char b,char c,char s[])
{
    int i,j,k;
    for(i=0;i<a;i++)
        if(s[i]=='C')break;
    if(i>=a)return 0;
    for(;i<a;i++)
        if(s[i]=='O')break;
    if(s[i]!='O')
    {
        i=c+1;
        for(;s[i];i++)
            if(s[i]=='O')break;
    }
    else i=c+1;
    if(!s[i])return 0;
    for(;s[i];i++)
        if(s[i]=='W')break;
    if(!s[i])return 0;
    return 1;
}
char a[10][80];
char good(char s[])
{
    char i,j;
    for(i=0;s[i]!='C' && s[i]!='O' && s[i]!='W' && s[i];i++)
        if(s[i]!=end[i])return 1;
    if(s[i]=='O' || s[i]=='W')return 1;
    while(s[i])i++;
    for(j=46,i--;i>=0 && s[i]!='C' && s[i]!='O' && s[i]!='W';i--,j--)
        if(s[i]!=end[j])return 1;
    if(i>=0 &&(s[i]=='C' || s[i]=='O'))return 1;
    return 0;
}
char go(int d)
{
    if(good(a[d])|| test1(a[d]))return 0;
    if(!d)return!strcmp(end,a[0]);
    char i,j,k,last=120;
    for(i=0;i<last && a[d][i];i++)
        if(a[d][i]=='C')
            for(j=i+1;a[d][j];j++)
                if(a[d][j]=='O')
                    for(k=j+1;a[d][k];k++)
                        if(a[d][k]=='W')
                        {
                            if(last==120)last=j;
                            if(test2(i,j,k,a[d]))continue;
                            decode(i,j,k,a[d],a[d-1]);
                            if(go(d-1))return 1;
                        }
    return 0;
}
char map[128];
main()
{
   // freopen("cryptcow.in","r",stdin);
   // freopen("cryptcow.out","w",stdout);
    int i;
    char c[3];
    while(scanf("%[^\n]",s)!=EOF)
    {
        c[0]=c[1]=c[2]=0;
        for(i=0;i<128;i++)map[i]=0;
        for(i=0;end[i];i++)
            map[end[i]]++;
        for(i=0;s[i];i++)
            if(s[i]=='C')c[0]++;
            else if(s[i]=='O')c[1]++;
            else if(s[i]=='W')c[2]++;
            else map[s[i]]--;
        for(i=0;i<128;i++)
            if(map[i])goto x;
        if(c[0]!=c[1] || c[1]!=c[2])goto x;
        if(good(s))goto x;
        if(test1(s))goto x;
        strcpy(a[c[0]],s);
        scanf("%c",s);
        if(go(c[0]))
        {
            printf("1 %d\n",c[0]);
            continue;
        }
    x:  puts("0 0");
        scanf("%[\n]",s);
    }
}
/*
TASK:cryptcow
LANG:C++
*/
