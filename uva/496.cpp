#include<cstdio>
#include<algorithm>
int s1[1000000],s2[1000000];
main()
{
    int i,j,n1,n2;
    char tmp[999];
    while(1)
    {
        if(scanf("%d%c",s1,tmp)==EOF)
            break;
        if(tmp[0]!='\n')
            for(n1=1;scanf("%d%c",s1+n1++,tmp) && tmp[0]!='\n';)
                tmp[0]=0;
        for(n2=0;scanf("%d%c",s2+n2++,tmp) && tmp[0]!='\n';)
            tmp[0]=0;
        std::sort(s1,s1+n1);
        std::sort(s2,s2+n2);
        if(n1==n2)
        {
            for(i=0;i<n1;i++)
                if(s1[i]!=s2[i])
                    break;
            if(i>=n1)
            {
                puts("A equals B");
                continue;
            }
        }
        if(n1<n2)
        {
            for(i=j=0;i<n1 && j<n2;i++,j++)
            {
                while(j<n2 && s1[i]>s2[j])j++;
                if(s1[i]!=s2[j])break;
            }
            if(i>=n1)
            {
                puts("A is a proper subset of B");
                continue;
            }
        }
        if(n2<n1)
        {
            for(i=j=0;i<n2 && j<n1;i++,j++)
            {
                while(j<n1 && s2[i]>s1[j])j++;
                if(s2[i]!=s1[j])break;
            }
            if(i>=n2)
            {
                puts("B is a proper subset of A");
                continue;
            }
        }
        for(i=j=0;i<n1 && j<n2;)
        {
            if(s1[i]==s2[j])break;
            if(s1[i]<s2[j])i++;
            else j++;
        }
        if(i>=n1 || j>=n2)
            puts("A and B are disjoint");
        else
            puts("I'm confused!");
    }
}
