#include<cstdio>
int s[1001][1001];
char s0[1002],a[2004];
int max(int a,int b){return a>?b;}
main()
{
    int i,j,k;
    while(gets(s0+1))
    {
        for(i=1;s0[i];i++);
        for(j=0;j<=i;j++)
            s[i][j]=0;
        for(i--;i>0;i--)
            for(j=1;s0[j];j++)
            {
                if(s0[i]==s0[j])
                    s[i][j]=s[i+1][j-1]+1;
                else
                    s[i][j]=max(s[i+1][j],s[i][j-1]);
            }
        i++,j--,k=0;
        printf("%d ",j-s[i][j]);
        while(s0[i] || j>0)
        {
            if(s0[i]==s0[j])
                a[k++]=s0[i++],j--;
            else if(s0[i] && s[i+1][j]>=s[i][j-1])
                a[k++]=s0[i++];
            else
                a[k++]=s0[j--];
        }
        a[k]=0;
        puts(a);
    }
}
