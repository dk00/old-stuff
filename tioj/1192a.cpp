#include<ctime>
#include<cstdio>
#include<cstdlib>
char s[1000001],t[1000001];
int s1[1001],s2[1001];
main()
{
    srand(time(NULL));
    int i,j,l,n,n1,n2,T,no;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&l);
        for(no=0,i=1;i<=l;i++)s[i]=t[i]=0;
        while(n--)
        {
            for(n1=0;scanf("%d",s1+n1),s1[n1];n1++);
            for(n2=0;scanf("%d",s2+n2),s2[n2];n2++);
            if(no)continue;
            if(rand()%2)
            {
                for(i=0;i<n1 && s[s1[i]]!=2;i++);
                for(j=0;j<n2 && s[s2[j]]!=1;j++);
                if(i>=n1 && j>=n2)
                {
                    for(i=0;i<n1;i++)s[s1[i]]=1;
                    for(j=0;j<n2;j++)s[s2[j]]=2;
                    continue;
                }
                for(i=0;i<n1 && t[s1[i]]!=2;i++);
                for(j=0;j<n2 && t[s2[j]]!=1;j++);
                if(i>=n1 && j>=n2)
                {
                    for(i=0;i<n1;i++)t[s1[i]]=1;
                    for(j=0;j<n2;j++)t[s2[j]]=2;
                    continue;
                }
            }
            else
            {
                for(i=0;i<n1 && t[s1[i]]!=2;i++);
                for(j=0;j<n2 && t[s2[j]]!=1;j++);
                if(i>=n1 && j>=n2)
                {
                    for(i=0;i<n1;i++)t[s1[i]]=1;
                    for(j=0;j<n2;j++)t[s2[j]]=2;
                    continue;
                }
                for(i=0;i<n1 && s[s1[i]]!=2;i++);
                for(j=0;j<n2 && s[s2[j]]!=1;j++);
                if(i>=n1 && j>=n2)
                {
                    for(i=0;i<n1;i++)s[s1[i]]=1;
                    for(j=0;j<n2;j++)s[s2[j]]=2;
                    continue;
                }
            }
            no=1;
        }
        puts(no?"No":"Yes");
    }
}
