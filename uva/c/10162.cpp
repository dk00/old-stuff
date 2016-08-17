#include<cstdio>
#include<cstring>
int pow(int n,int k)
{
    if(!k)return 1;
    if(k%2)
        return(n*pow(n,k-1))%10;
    int tmp=pow(n,k/2);
    return(tmp*tmp)%10;
}
main()
{
    int i,n,s[100];
    char tmp[1000];
    for(s[0]=0,i=1;i<=100;i++)
        s[i%100]=(s[i-1]+pow(i,i))%10;
    while(scanf("%s",&tmp) && strcmp(tmp,"0"))
    {
        n=strlen(tmp);
        n=((n>1)?tmp[n-2]-'0':0)*10+(tmp[n-1]-'0');
        printf("%d\n",s[n]);
    }
}
