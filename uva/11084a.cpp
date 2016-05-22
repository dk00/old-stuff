#include<cstdio>
#include<algorithm>
struct pair1
{
    int use,num;
    bool operator<(pair1 a)const
    {
        if(use<a.use)return 1;
        return(use==a.use && num<a.num);
    }
    bool operator==(pair1 a)const{return(use==a.use && num==a.num);}
}tmp[30240],s1[30240];
int n,cn,pn,d,use,num,r[11],s2[30240],st[30240];
char s[100];
void add(int i,int x)
{
    use|=(1<<i);
    num=(num+r[x]*s[i])%d;
}
void sub(int i,int x)
{
    use&=~(1<<i);
    num=(num+(d-s[i])*r[x])%d;
}
void go(int x)
{
    if(x<0)
    {
        tmp[cn++]=(pair1){use,num};
        return;
    }
    int last=-1;
    for(int i=n-1;i>=0;i--)
        if(s[i]!=last && !(use&(1<<i)))
        {
            add(i,n-x-1);
            last=s[i];
            go(x-1);
            sub(i,n-x-1);
        }
}
int find(int u1,int n1)
{
    int i,j,k;
    for(i=0,j=pn-1;i<=j;)
    {
        k=(i+j)/2;
        if(s1[st[k]].use==u1)break;
        if(s1[st[k]].use<u1)i=k+1;
        else j=k-1;
    }
    for(i=st[k],j=st[k+1]-1;i<=j;)
    {
        k=(i+j)/2;
        if(s1[k].num==n1)break;
        if(s1[k].num<n1)i=k+1;
        else j=k-1;
    }
    if(i<=j)return s2[k];
    return 0;
}
int calc(int x)
{
    if(x<0)
        return find(((1<<n)-1)^use,(d-num)%d);
    int i,sum,last=-1;
    for(i=sum=0;i<n;i++)
        if(s[i]!=last && !(use&(1<<i)))
        {
            add(i,x);
            last=s[i];
            sum+=calc(x-1);
            sub(i,x);
        }
    return sum;
}
main()
{
    int i,j,t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s %d",s,&d);
        for(n=0;s[n];n++);
        std::sort(s,s+n);
        for(i=0,r[0]=1;i<n;i++)
        {
            r[i+1]=(r[i]*10)%d;
            s[i]-='0';
        }
        cn=num=use=0;
        go(n-n/2-1);
        std::sort(tmp,tmp+cn);
        s1[0]=tmp[0],s2[0]=1;
        for(i=j=1;i<cn;i++)
        {
            if(s1[j-1]==tmp[i])
                s2[j-1]++;
            else
                s1[j]=tmp[i],s2[j++]=1;
        }
        for(cn=j,i=pn=j=0;i<cn;i++)
            if(s1[i].use!=j)
            {
                j=s1[i].use;
                st[pn++]=i;
            }
        st[pn]=cn;
        printf("%d\n",calc(n/2-1));
    }
}
