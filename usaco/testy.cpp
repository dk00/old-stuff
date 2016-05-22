#include<cstdio>
#include<cstring>
const char end[]="Begin the Escape execution at the Break of Dawn";
char s[80];
struct ku
{
    char x,u;
    ku *ne,*ch;
}*root;
void ins(ku *&ptr,char s[])
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
char find(ku*&ptr,char s[])
{
    if(!ptr)return 0;
    if(s[0]==ptr->x)
    {
        if(s[1])return find(ptr->ch,s+1);
        return ptr->u;
    }
    return find(ptr->ne,s);
}
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
char a[10][80];
char go(int d)
{
    if(find(root,a[d]))return 0;
    if(!d)
    {
        puts(a[0]);
        return 1;
    }
    ins(root,a[d]);
    char i,j,k,last=120,f;
    for(i=0;i<last && a[d][i];i++)
        if(a[d][i]=='C')
            for(j=i+1;a[d][j];j++)
                if(a[d][j]=='O')
                    for(k=j+1;a[d][k];k++)
                        if(a[d][k]=='W')
                        {
                            if(last==120)last=k;
                            decode(i,j,k,a[d],a[d-1]);
                            if(go(d-1))f=1;
                        }
    if(f)printf(">%s\n",a[d]);
    return f;
}
main()
{
    int i;
    char c[3];
    while(scanf("%[^\n]",s)!=EOF)
    {

        root=NULL;
        c[0]=c[1]=c[2]=0;
        for(i=0;s[i];i++)
            if(s[i]=='C')c[0]++;
            else if(s[i]=='O')c[1]++;
            else if(s[i]=='W')c[2]++;
        strcpy(a[c[0]],s);
        scanf("%c",s);
        if(c[0]!=c[1] || c[1]!=c[2])continue;
        go(c[0]);
    }
}
//CWWdOCrOoObCaW
