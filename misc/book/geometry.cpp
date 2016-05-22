typedef int num;
const int inf=2000000000;
struct pt
{
    num x,y;
    pt operator+(pt a)const{return(pt){x+a.x,y+a.y};}
    pt operator-(pt a)const{return(pt){x-a.x,y-a.y};}
    num operator*(pt a)const{return x*a.y-y*a.x;}
    bool operator==(pt a)const{return x==a.x && y==a.y;}
};
num area2(int n,pt s[])
{
    s[n]=s[0];
    int i,sum;
    for(i=sum=0;i<n;i++)
        sum+=s[i]*s[i+1];
    if(sum<0)sum*=-1;
    return sum;
}
num disq(pt a,pt b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
char in(pt a,pt b,pt t)
{
    return ((t.x<a.x)^(t.x<b.x))&((t.y<a.y)^(t.y<b.y));
}
char ins(pt a0,pt a1,pt b0,pt b1)
{
    num d[]={(a1-a0)*(b0-a0),(a1-a0)*(b1-a0),
        (b1-b0)*(a0-b0),(b1-b0)*(a1-b0)};
    if(!d[0] && in(a0,a1,b0))
        return 1;
    if(!d[1] && in(a0,a1,b1))
        return 1;
    if(!d[2] && in(b0,b1,a0))
        return 1;
    if(!d[3] && in(b0,b1,a1))
        return 1;
    return ((d[0]<0)^(d[1]<0))&((d[2]<0)^(d[3]<0));
}
main()
{
}
