p(const void *a,const void *b){return **(int **)a-**(int **)b;}
sort(int **s[],int *t[])
{
    int i,j,n;
    for(i=n=0;s[i];i++)
        for(j=0;s[i][j];j++)
			t[n++]=s[i][j];
    qsort(t,n,sizeof(t[0]),p);
}
