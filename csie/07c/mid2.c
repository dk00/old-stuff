swap(int *a,int *b){int t=*a;*a=*b;*b=t;}
in(a,b,c){return(a<=b && b<=c);}
find(int a1,int a2,int b1,int b2,int *c1,int *c2)
{
    if(in(a1,b1,a2)&&in(a1,b2,a2))
        *c1=b1,*c2=b2;
    else if(in(b1,a1,b2)&&in(b1,a2,b2))
        *c1=a1,*c2=a2;
    else if(in(a1,b1,a2))
        *c1=b1,*c2=a2;
    else if(in(a1,b2,a2))
        *c1=a1,*c2=b2;
    else *c1=1,*c2=0;
}
main()
{
    int i,j,sum,x1[9],x2[9],y1[9],y2[9],xa,xb,ya,yb;
    for(i=sum=0;i<3;i++)
    {
        scanf("%d %d %d %d",&x1[i],&y1[i],&x2[i],&y2[i]);
        if(x1[i]>x2[i])swap(&x1[i],&x2[i]);
        if(y1[i]>y2[i])swap(&y1[i],&y2[i]);
        sum+=(x2[i]-x1[i])*(y2[i]-y1[i]);
    }
    for(i=0;i<3;i++)
        for(j=0;j<i;j++)
        {
            find(x1[i],x2[i],x1[j],x2[j],&xa,&xb);
            find(y1[i],y2[i],y1[j],y2[j],&ya,&yb);
            if(xa<xb && ya<yb)
                sum-=(xb-xa)*(yb-ya);
        }
    find(x1[0],x2[0],x1[1],x2[1],x1+3,x2+3);
    find(y1[0],y2[0],y1[1],y2[1],y1+3,y2+3);
    if(x1[3]<x2[3] && y1[3]<y2[3])
    {
        i=2,j=3;
        find(x1[i],x2[i],x1[j],x2[j],&xa,&xb);
        find(y1[i],y2[i],y1[j],y2[j],&ya,&yb);
        if(xa<xb && ya<yb)
            sum+=(xb-xa)*(yb-ya);
    }
    printf("%d\n",sum);
}
