#include<stdio.h>
int num[100];
int msort(int st,int ed)
{
if(st>=ed)
    return 0;
int temp;
if(ed==st+1 && num[st]>num[ed])
    {
    temp=num[st];
    num[st]=num[ed];
    num[ed]=temp;
    return 0;
    }
int mid=(st+ed)/2;
msort(st,mid);
msort(mid+1,ed);
return 0;
}
main()
{
int i,n;
scanf("%d",&n);
for(i=1;i<=n;i++)
    scanf("%d",&num[i]);
msort(1,n);
for(i=1;i<=n;i++)
    printf("%d ",num[i]);

scanf(" ");
}
