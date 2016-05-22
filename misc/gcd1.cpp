#include<stdio.h>
#include<windows.h>
struct pair
{
    int p,q;
}test[100];
int x=0;
void gcd(int a,int b)
{
    int c=0,d;
    while((a%=b)&&(b%=a)){c++;for(d=0;d<10000000;d++);}
    printf("%d(%d)\n",a+b,c);
}
DWORD WINAPI thproc(LPVOID a)
{
    int i,j;
    pair *foo;
    foo=(pair *)a;
    i=foo->p,j=foo->q;
    gcd(i,j);
    return 0;
}
main()
{
    HANDLE p1[100];
    DWORD p2[100];
    int i,j,k,n;
    while(scanf("%d",&n) && n)
    {
        for(k=0;k<n;k++)
        {
            scanf("%d %d",&i,&j);
            test[k].p=i,test[k].q=j;
            p1[k]=CreateThread(NULL,0,thproc,&test[k],0,&p2[k]);
        }
        WaitForMultipleObjects(n,p1,TRUE,INFINITE);
        for(k=0;k<n;k++)
            CloseHandle(p1[k]);
    }
}
