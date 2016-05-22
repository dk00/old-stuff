#include<stdio.h>
int *msort2(int data[],int temp[],int n)
{
int *s[2]={data,temp};
int i,j,r,f,p1,p2;
    for(f=0,r=1;r<=n;r*=2,f=!f)
        for(i=r;i-r<n;i+=2*r)
            for(j=i-r,p1=i-r,p2=i;j<i+r && j<n;)
            {
                if(p1>=i)s[!f][j++]=s[f][p2++];
                else if(p2>=i+r || p2>=n)s[!f][j++]=s[f][p1++];
                else if(s[f][p1]<s[f][p2])s[!f][j++]=s[f][p1++];
                else s[!f][j++]=s[f][p2++];
            }
    return s[!f];
}

int s[10000],tmp[10000];
void msort(int st,int ed)
{
    if(st>=ed)return;
int mid=(st+ed)/2,p=st,p1=st,p2=mid+1;
    msort(st,mid);
    msort(mid+1,ed);
    while(p<=ed)
    {
        if(p1>mid)
            tmp[p++]=s[p2++];
        else if(p2>ed)
            tmp[p++]=s[p1++];
        else if(s[p1]<s[p2])
            tmp[p++]=s[p1++];
        else
            tmp[p++]=s[p2++];
    }
    for(p=st;p<=ed;p++)
        s[p]=tmp[p];
}

void qsort(int st,int ed)
{
    if(st>=ed)return;
int mid=(st+ed)/2,p1,p2,tmp;
    while(1)
    {
        for(p1=st+1;p1<ed && s[p1]<s[st];p1++);
        for(p2=ed;p2>st && s[p2]>s[st];p2--);
        if(p1>=p2)break;
        tmp=s[p1],s[p1]=s[p2],s[p2]=tmp;
    }
    tmp=s[st],s[st]=s[p2],s[p2]=tmp;
    qsort(st,p2-1);
    qsort(p2+1,ed);
}

main()
{
int i,n,*p;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            scanf("%d",&s[i]);
        //p=msort2(s,tmp,n);
        msort(0,n-1);
        //qsort(0,n-1);
        for(i=0;i<n;i++)
            printf("%d ",s[i]);
        puts("");
    }
}
