#include<stdio.h>
#include<stdlib.h>
int numcmp(const void *a,const void *b)
{
    return *(int *)a-*(int *)b;
}
main()
{
    scanf("%d",&n);
    for(i=bsum=0;i<n;i++)
    {
        scanf("%d",&board[i]);
        bsum+=board[i];
    }
    scanf("%d",&r);
    for(i=rsum=0;i<r;i++)
    {
        scanf("%d",&j);
        if(rmin>j)
            rmin=j;
        if(rmax<j)
            rmax=j;
        rail[j]++;
        rsum+=j;
    }
    qsort(board,n,sizeof(board[0]),numcmp);
    if(board[n-1]>=rsum)
    {
        printf("%d\n",r);
        return 0;
    }
    for(j=0;board[j]<rmin;j++)
        bsum-=board[j];
    for(i=0;j<n;i++,j++)
        board[i]=board[j];
    n=i;
    for(;rsum>bsum;rmax--)
        while(rail[rmax]>0 && rsum>bsum)
            rsum-=rmax;
    test(0);
    printf("%d\n",best);
}
void test(int bi)
{
    if(board[n-1]>=rrem)
    {
        best=r;
        return;
    }
    if(bi>=n)
    {
        if(cut>=best)
            best=cut;
        return;
    }
    if(best>=r)
        return;
    for(i=rmin,rsum=maxcut=0;i<=rmax && rsum<=bsum;i++)
        for(j=0;j<rail[i] && rsum<=bsum;j++,maxcut++)
            rsum+=i;
    if(cut+maxcut<=best)
        return;
    for(i=maxcut;i+cut>best;i--)
        dfs(bi,i,0);
}
void dfs(int bi,int n,int len)
{
    if(n<=0)
    {
        calc(bi+1);
        return;
    }
    if(n==1 && len<rmax && s[len]>0)
    {
        s[len]--;
        cut++;
        calc(bi+1);
        cut--;
        s[len]++;
        return;
    }
    for(i=rmax;s[i]==0 && i>len;i--);
    for(;i>=rmin;i--)
        if(s[i]>0)
        {
            s[i]--;
            cut++;
            dfs(bi,n-1,len-i);
            cut--;
            s[i]++;
        }
}
