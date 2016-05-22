class qsort
{
    int *s,n;
    void sort()
    {
        int i,j,t;
        for(i=1,j=n-1;i<j;)
        {
            for(;i<n && s[i]<s[0];i++);
            for(;j>0 && s[j]>s[0];j--);
            if(i<j)
                t=s[i],s[i]=s[j],s[j]=t;
        }
        t=s[0],s[0]=s[i],s[i]=t;
        qsort a,b;
        if(i>0)
            (a=(qsort){s,i-1}).sort();
        if(i<n-1)
            (b=(qsort){s+i+1,n-i}).sort();
    }
}
