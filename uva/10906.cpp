#include<cstdio>
#include<cstring>
char s[50][5001],t[50][5001],op[50][2],s1[5001],s2[5001];
int find(int i,char *u)
{
    while(i--)
        if(strcmp(u,s[i])==0)
        {
            strcpy(u,t[i]);
            return i;
        }
}
main()
{
    int i,j,k,n,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
            scanf("%s = %s %s %s",s[i],s1,op[i],s2);
            j=k=-1;
            if(s1[0]<'0' || s1[0]>'9')j=find(i,s1);
            if(s2[0]<'0' || s2[0]>'9')k=find(i,s2);
            if(op[i][0]=='*')
            {
                if(j>=0 && op[j][0]=='+')
                {
                    if(k>=0)
                        sprintf(t[i],"(%s)*(%s)",s1,s2);
                    else
                        sprintf(t[i],"(%s)*%s",s1,s2);
                }
                else
                    if(k>=0)
                        sprintf(t[i],"%s*(%s)",s1,s2);
                    else
                        sprintf(t[i],"%s*%s",s1,s2);
            }
            else
                if(k>=0 && op[k][0]=='+')
                    sprintf(t[i],"%s+(%s)",s1,s2);
                else
                    sprintf(t[i],"%s+%s",s1,s2);
        }
        printf("Expression #%d: %s\n",C++,t[n-1]);
    }
}
