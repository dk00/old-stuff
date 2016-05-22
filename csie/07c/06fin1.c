main()
{
    int i,j,k,n,s[50];
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",s+i);
    for(i=0;i<n;i++)
        for(j=1;j<n;j++)
            if(s[j]<s[j-1])
                k=s[j],s[j]=s[j-1],s[j-1]=k;
    for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
            for(k=j+1;k<n;k++)
                if(s[i]+s[j]>s[k])
                    printf("%d %d %d\n",s[i],s[j],s[k]);
}
