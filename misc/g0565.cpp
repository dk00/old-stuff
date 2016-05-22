#include<ctime>
#include<cstdio>
#include<cstdlib>
char path[99];
void go(int d,int n)
{
    if(n<2){
        path[d]=0;
        puts(path);
        return;
    }
    int a=1+rand()%(n-1),b=n-a;
    path[d]='0';
    go(d+1,a);
    path[d]='1';
    go(d+1,b);
}
main()
{
    srand(time(NULL));
    int n;
    while(scanf("%d",&n)==1)
    go(0,n);
}
