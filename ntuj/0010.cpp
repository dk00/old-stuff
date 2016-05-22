#include<cstdio>
template<class x>inline void swap(x& a,x& b){x t=a;a=b;b=t;}
void rev(char a[])
{
    int i,j;
    for(i=0;a[i];i++);
    for(j=0;j<i/2;j++)
        swap(a[j],a[i-j-1]);
}
main()
{
    int i,j,T,C=1;
    char s1[99],s2[99],s3[99];
    scanf("%d",&T);
    while(T--)
    {
        for(i=0;i<99;i++)
            s1[i]=s2[i]=0;
        scanf("%s %s",s1,s2);
        rev(s1),rev(s2);
        for(i=0;s1[i];i++);
        while(i>1 && s1[i-1]=='0')s1[--i]=0;
        for(i=0;s2[i];i++);
        while(i>1 && s2[i-1]=='0')s2[--i]=0;
        for(i=0;s1[i] || s2[i];i++)
        {
            if(!s1[i])s1[i]='0';
            if(!s2[i])s2[i]='0';
        }
        for(i=j=0;s1[i];i++)
        {
            s3[i]='0'+(j+s1[i]+s2[i]-'0'-'0')%2;
            j=(j+s1[i]+s2[i]-'0'-'0')/2;
        }
        if(j)s3[i++]='1';
        s3[i]=0;
        rev(s3);
        printf("%d %s\n",C++,s3);
    }
}
