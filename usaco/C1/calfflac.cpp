/*
PROB:calfflac
LANG:C++
*/
#include<cstdio>
#include<cctype>
char tmp[20001],s[20001],ch[2];
int pos[20000];
main()
{
    freopen("calfflac.in","r",stdin);
    freopen("calfflac.out","w",stdout);
    int i,j,k,n,st,max;
    for(i=0;scanf("%[^\n]",tmp+i)>0;i=j)
    {
        for(j=i;tmp[j];j++);
        scanf("%[\n]",tmp+j++);
    }
    for(i=n=0;tmp[i];i++)
    {
        if(('a'<=tmp[i]&& tmp[i]<='z')||('A'<=tmp[i]&& tmp[i]<='Z'))
            s[n]=tolower(tmp[i]),pos[n++]=i;
    }
    pos[n]=i,s[n]=s[n+1]=max=0;
    for(i=0;i<n;i++)
    {
        j=1000<?i<?(n-i-1);
        for(k=0;j>0 && (j+k)*2+1>max;j--)
        {
            if(s[i-j]==s[i+j])k++;
            else k=0;
        }
        if((j+k)*2+1>max)max=(j+k)*2+1,st=i-k;
        if(!i || s[i]!=s[i-1])continue;
        j=1000<?(i-1)<?(n-i-1);
        for(k=0;j>0 && (j+k)*2+2>max;j--)
        {
            if(s[i-j-1]==s[i+j])k++;
            else k=0;
        }
        if((j+k)*2+2>max)max=(j+k)*2+2,st=i-k-1;
    }
    printf("%d\n",max);
    tmp[pos[st+max-1]+1]=0;
    puts(tmp+pos[st]);
    scanf(" ");
}
