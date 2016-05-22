void clear(int a[],int n){while(n--)a[n]=0;}
int *assign(int a[],int b[],int n)
{
    while(n--)a[n]=b[n];
    return a;
}
int *mul(int a[],int b[],int n)
{
    if(n==1)
    {
        a[0]*=b[0];
        a[1]+=a[0]/D;
        a[0]/=D;
        return a;
    }
    int s1=a,s2=s1+n/2,s3=s2+n/2,s4=s3+n/2,
        t1=b,t2=s1+n/2,t3=s2+n/2,t4=s3+n/2;
    assign(t1,s1,n),clear(s3,n/2),
    assign(s2,t4,n/2),mul(s3,s1,n/2);
    assign(s2,t1,n/2),sub(t1,t2,n/2),
    assign(t2,t4,n/2),sub(t2,t3,n/2);
    assign(t4,t3,n/2),clear(t3,n/2);
    mul(s1,t4,n/2),assign(t4,t1,n/2),clear(t1,n/2);
    mul(t1,t4),add(t1,s1,n/2),add(t1,s3,n/2),add(s2,t1,n/2);
    return a;
}
