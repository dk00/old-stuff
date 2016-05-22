#include<cstdio>
main()
{
    int i,j,p[1001]={0,0};
    char s1[1001],s2[1001];
    while(scanf("%s %s",s1,s2)>0)
    {
        for(i=0;s1[i];i++);
        s1[i++]='$',s1[i]=0;
        for(i=1,j=0;s1[i];i++)
        {
            while(j && s1[i]!=s1[j])j=p[j];
            if(s1[i]==s1[j])j++;
            p[i+1]=j;
        }
        for(i=j=0;s2[i];i++)
        {
            while(j && s1[j]!=s2[i])j=p[j];
            if(s1[j]==s2[i])j++;
        }
        printf("%d\n",j);
    }
}
