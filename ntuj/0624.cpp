#include<cstdio>
#include<cstring>
const int N=999;
char s0[N],s1[N],t0[N],t1[N];
bool go()
{
    strcpy(t0,s0);
    strcpy(t1,s1);
    int i,j,k,a,b,n0=strlen(t0),n1=strlen(t1),max=0;
    for(i=1-n0;i<n0;i++)
        for(k=0,j=0>-i?0:-i;t0[j] && t1[j+i];j++){
            if(t0[j]!=t1[j+i])k=0;
            else k++;
            if(k>max)max=k,a=j,b=i+j;
            if(k==max && (j>a ||  (j==a && i+j>b)))
                a=j,b=i+j;
        }
    if(max<2)return 0;
    for(i=j=0;t0[i];i++)
        if(i>a || i<=a-max)
            s0[j++]=t0[i];
    s0[j]=0;
    for(i=j=0;t1[i];i++)
        if(i>b || i<=b-max)
            s1[j++]=t1[i];
    s1[j]=0;
    return max;
}
main()
{
    while(scanf("%s %s",s0,s1)==2 && (s0[1] || s1[0]!='#')){
        int i;
        for(i=0;go();i++);
        printf("%d %s_%s\n",i,s0,s1);
    }
}
