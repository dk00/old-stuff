#include<cstdio>
char t1[31]="AHOVBIPWCJQXDKRYELSZFMTGNU_.,?",t2[30][5]={
".-","....","---","...-","-...","..",".--.",".--","-.-.",".---","--.-","-..-","-..",
"-.-",".-.","-.--",".",".-..","...","--..","..-.","--","-","--.","-.","..-","..--",
"---.",".-.-","----"};
char s[105],t[999];
int findcode(char x)
{
    for(int i=0;t1[i];i++)
        if(x==t1[i])return i;
    t1[30]/=t1[30];
}
char findch(char key[],int n)
{
    int i,j;
    for(i=0;i<30;i++)
    {
        for(j=0;j<n;j++)
            if(key[j]!=t2[i][j])break;
        if(j==n && !t2[i][j])
            return t1[i];
    }
    t1[30]/=t1[30];
}
int l[100];
main()
{
    int i,j,k,n,m,C=1,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",s);
        for(n=0;s[n];n++);
        for(i=m=0;s[i];i++)
        {
            j=findcode(s[i]);
            sprintf(t+m,"%s",t2[j]);
            for(l[i]=0;t2[j][l[i]];l[i]++);
            m+=l[i];
        }
        for(i=0;i<n/2;i++)
        {
            l[i]+=l[n-i-1];
            l[n-i-1]=l[i]-l[n-i-1];
            l[i]-=l[n-i-1];
        }
        for(i=j=0;i<m;i+=l[j++])
            s[j]=findch(t+i,l[j]);
        printf("%d: %s\n",C++,s);
    }
}
