#include<cstdio>
main()
{
    freopen("preface.in","r",stdin);
    freopen("preface.out","w",stdout);
    int j,k,n,i,v,x,l,c,d,m;
    i=v=x=l=c=d=m=0;
    scanf("%d",&n);
    for(k=1;k<=n;k++)
    {
        j=k;
        m+=j/1000;
        j%=1000;
        if(j/100==9)m++,c++;
        else if(j/100>=5)d++,c+=j/100-5;
        else if(j/100==4)d++,c++;
        else c+=j/100;
        j%=100;
        if(j/10==9)c++,x++;
        else if(j/10>=5)l++,x+=j/10-5;
        else if(j/10==4)l++,x++;
        else x+=j/10;
        j%=10;
        if(j==9)x++,i++;
        else if(j>=5)v++,i+=j-5;
        else if(j==4)v++,i++;
        else i+=j;
    }
    if(i+v+x+l+c+d+m)
        printf("I %d\n",i);
    if(v+x+l+c+d+m)
        printf("V %d\n",v);
    if(x+l+c+d+m)
        printf("X %d\n",x);
    if(l+c+d+m)
        printf("L %d\n",l);
    if(c+d+m)
        printf("C %d\n",c);
    if(d+m)
        printf("D %d\n",d);
    if(m)
        printf("M %d\n",m);
}
/*
PROB:preface
LANG:C++
*/
