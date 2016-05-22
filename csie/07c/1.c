dis(x1,y1,x2,y2){return(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);}
main()
{
    int x1,y1,x2,y2,x3,y3,x4,y4,a,b,c,d;
    scanf("%d %d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
    if(x1>1000 || x1<-1000 || x2>1000 || x2<-1000
    || x3>1000 || x3<-1000 || x4>1000 || x4<-1000
    || y1>1000 || y1<-1000 || y2>1000 || y2<-1000
    || y3>1000 || y3<-1000 || y4>1000 || y4<-1000)
    {
        puts("invalid");
        return;
    }
    a=(dis(x1,y1,x2,y2)==dis(x3,y3,x4,y4) && dis(x2,y2,x3,y3)==dis(x1,y1,x4,y4));
    b=(a && dis(x1,y1,x2,y2)==dis(x1,y1,x4,y4));
    c=!((x1-x2)*(x1-x4)+(y1-y2)*(y1-y4));
    if(b && c)puts("square");
    else if(a && c)puts("rectangle");
    else if(b)puts("diamond");
    else if(a)puts("parallelogram");
    else puts("others");
}
