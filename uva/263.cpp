#include<set>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
void sub(char a[],char b[])
{
    int i;
    for(i=0;a[i];i++);
    while(i--)
    {
        a[i]-=b[i]-'0';
        if(a[i]<'0')a[i-1]--,a[i]+=10;
    }
}
main()
{
    int i,j,len;
    char s1[100],s2[100];
    std::set<std::string> last;
    std::string tmp;
    while(scanf("%s",s1) && s1[0]!='0')
    {
        last.clear();
        printf("Original number was %s\n",s1);
        strcpy(s2,s1);
        len=0;
        while(1)
        {
            for(i=0;s1[i];i++);
            std::sort(s1,s1+i);
            for(j=0;i--;j++)s2[j]=s1[i];
            s2[j]=0;
            for(i=0;s1[i]=='0';i++);
            if(s1[i]==0)i--;
            printf("%s - %s =",s2,s1+i);
            sub(s2,s1);
            for(i=0;s2[i]=='0';i++);
            if(s2[i]==0)i--;
            printf(" %s\n",s2+i);
            len++;
            tmp=s2+i;
            if(last.count(tmp))break;
            last.insert(tmp);
            strcpy(s1,tmp.c_str());
        }
        printf("Chain length %d\n\n",len);
    }
    if(s1[1])*(char *)NULL=0;
}
