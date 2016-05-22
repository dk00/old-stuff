#include<cstdio>
int go(int);
void orz(char a[],char b[])
{
    //printf("(%s%s)",a,b);
    printf("((%s|%s)|(%s|%s))",a,b,a,b);
}
void andy(char a[],char b[])
{
    //printf("(%s+%s)",a,b);
    printf("((%s|%s)|(%s|%s))",a,a,b,b);
}
int orz(char a[],char b[],int n)
{
    int sum=9;
    /*printf("(");
    andy(a,b);
    go(n);
    printf(")");
    */printf("((");
    andy(a,b);
    printf("|");
    sum+=go(n);
    printf(")|(");
    andy(a,b);
    printf("|");
    sum+=go(n);
    printf("))");
    return sum;
}
int andy(char a[],char b[],int n)
{
    int sum=9;
    /*printf("(");
    orz(a,b);
    printf("+");
    orz(a,b,n);
    printf(")");*/
    printf("((");
    orz(a,b);
    printf("|");
    orz(a,b);
    printf(")|(");
    sum+=orz(a,b,n);
    printf("|");
    sum+=orz(a,b,n);
    printf("))");
    return sum;
}
int go(int n)
{
    if(n==0)
    {
        orz("A0","B0");
        return 3;
    }
    char a[3],b[3];
    sprintf(a,"A%d",n);
    sprintf(b,"B%d",n);
    return andy(a,b,n-1);
}
int test(int n)
{
    if(n==0)return go(0);
    int sum=6;
    char a[3],b[3];
    sprintf(a,"A%d",n);
    sprintf(b,"B%d",n);
    printf("((A%d|B%d)|(",n,n);
    sum+=test(n-1);
    printf("|");
    andy(a,b);
    printf("))");
    return sum;
}
main()
{
    int n;
    while(scanf("%d",&n)==1)
    {
        printf("ans1:\n");
        printf("\n%d NAND(s) used.\n",go(n));
        printf("ans2:\n");
        printf("\n%d NAND(s) used.\n",test(n));
    }
}
