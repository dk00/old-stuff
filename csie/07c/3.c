gcd(a,b,c)
{
    while((a%=b)&&(b%=a));
    a+=b,b=c;
    while((a%=b)&&(b%=a));
    return (a+b)*(a+b)*(a+b);
}
value(a,b,c,d)
{
    if(a!=79 && a!=47 && a!=29 && a!=82 && a!=26 && a!=22)
        return -1;
    if(b<=0 || c<=0 || d<=0)return -2;
    if(a==79)return 30*b*c*d*gcd(b,c,d);
    if(a==47)return 10*b*c*d*gcd(b,c,d);
    if(a==29)return 4*b*c*d*gcd(b,c,d);
    if(a==82)return 5*b*c*d*gcd(b,c,d);
    if(a==26)return 3*b*c*d*gcd(b,c,d);
    if(a==22)return 9*b*c*d*gcd(b,c,d);
}
