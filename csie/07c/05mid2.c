f(a,b,d,e){return 2*(a*b+2*(a-2*e)*d+2*(b-2*e)*d);}
main()
{
    int a,b,c,d,e;
    scanf("%d %d %d %d %d",&a,&b,&c,&d,&e);
    printf("%d\n",f(a,b,d,e)+f(a,c,d,e)+f(b,c,d,e));
}
