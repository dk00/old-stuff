int cmp(const void *a,const void *b){return *(int *)a<*(int *)b?-1:1;}
int n,s[10],u[10],p[10];
int go(int d)
{
    if(d==n)
    {
        for(d=0;d<n;d++)
        {
            if(d)putchar(' ');
            printf("%d",p[d]);
        }
        puts("");
        return;
    }
    int i;
    for(i=0;i<n;i++)
        if(!u[i])
        {
            u[i]=1;
            p[d]=s[i];
            go(d+1);
            u[i]=0;
        }
}
main()
{
    int i=1>?2;
    while(scanf("%d",&n)>0){
    for(i=0;i<n;i++)
        scanf("%d",s+i);
    qsort(s,n,sizeof(s[0]),cmp);
    go(0);}
}
