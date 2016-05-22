#include<cstdio>
int m,n[3],b[3];
char s[3][99];
void print()
{
    static int count=0;
    s[0][n[0]]=s[1][n[1]]=s[2][n[2]]=0;
    printf("%3d: [%-*s] [%-*s] [%-*s]\n",count++,m,s[0],m,s[1],m,s[2]);
}
void go(int m,int tg)
{
    if(s[tg][b[tg]]!=m+'0')
    {
        int i,j;
        for(i=0;s[i][b[i]]!=m+'0';i++);
        if(m-1>0)
        {
            for(j=0;j==i || j==tg;j++);
            b[i]++;
            go(m-1,j);
            b[i]--;
        }
        s[tg][n[tg]++]=s[i][--n[i]];
        print();
    }
    b[tg]++;
    if(m-1>0)go(m-1,tg);
    b[tg]--;
}
main(int _m,char *a[])
{
    int i,j,k,tg;
    for(m=0;a[1][m];m++);
    n[0]=n[1]=n[2]=0;
    for(i=m;i--;)
    {
        k=a[1][i]-'A';
        s[k][n[k]++]=i+'1';
    }
    tg=a[2][0]-'A';
    print();
    go(m,tg);
}
