s[20001];
main()
{
    int i,j,w,v,n;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d %d",&w,&v);
        for(j=20000;j>=w;j--)
            if(s[j-w]+v>s[j])
                s[j]=s[j-w]+v;
    }
    scanf("%d",&i);
    if(i>20000)i=20000;
    printf("%d\n",s[i]);
}
