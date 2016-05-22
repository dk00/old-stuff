#include<cstdio>
#include<cstring>
#include<algorithm>
const char end[]="Begin the Escape execution at the Break of Dawn";
char s[80];
struct ku
{
    char x,u;
    ku *ne,*ch;
}*root;
inline void ins(ku *&ptr,char s[])
{
    if(!ptr)
    {
        ptr=new ku;
        *ptr=(ku){s[0],!s[1],NULL,NULL};
    }
    if(ptr->x==s[0])
    {
        if(s[1])ins(ptr->ch,s+1);
        else ptr->u=1;
    }
    else ins(ptr->ne,s);
}
inline char find(ku*&ptr,char s[])
{
    if(!ptr)return 0;
    if(s[0]==ptr->x)
    {
        if(s[1])return find(ptr->ch,s+1);
        return ptr->u;
    }
    return find(ptr->ne,s);
}
inline void decode(char a,char b,char c,char from[],char to[])
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
inline char test1(char s[])
{
    int i,j,k,find=0;
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
            find=1;
            for(j=0;s[i+j] && s[i+j]!='C' && s[i+j]!='O' && s[i+j]!='W';j++)
                tmp[k+j]++;
        }
        if(!find)return 1;
        for(j=i;s[j]!='C' && s[j]!='O' && s[j]!='W' && s[j];j++);
    }
    for(i=0;end[i];i++)
        if(!tmp[i])return 1;
    return 0;
}
char a[10][80];
inline char good(char s[])
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
inline char go(int d)
{
    if(good(a[d])|| test1(a[d]) || find(root,a[d]))return 0;
    if(!d)return!strcmp(end,a[0]);
    ins(root,a[d]);
    char i,j,k,last=120;
    int s1[10],s2[10],s3[10],n1=0,n2=0,n3=0;
    for(i=0;a[d][i];i++)
        if(a[d][i]=='C')s1[n1++]=i;
        else if(a[d][i]=='O')s2[n2++]=i;
        else if(a[d][i]=='W')s3[n3++]=i;
  //  std::random_shuffle(s1,s1+n1);
  //  std::random_shuffle(s2,s2+n2);
  //  std::random_shuffle(s3,s3+n3);
    for(i=0;i<n1 && s1[i]<last;i++)
        for(j=0;j<n2;j++)
            if(s1[i]<s2[j])
                for(k=0;k<n3;k++)
                    if(s2[j]<s3[k])
                    {
                        if(last==120)last=s2[j];
                        decode(s1[i],s2[j],s3[k],a[d],a[d-1]);
                        if(go(d-1))return 1;
                    }
    return 0;
}
char map[128];
main()
{
    freopen("cryptcow.in","r",stdin);
    freopen("cryptcow.out","w",stdout);
    int i;
    char c[3];
    while(scanf("%[^\n]",s)!=EOF)
    {
        root=NULL;
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
