#include<stdio.h>
int s[10001],lis[10001],lds[10001];
main(){
    int n,i,j,max;
    while(scanf("%d",&n)!=EOF){
        for(i=0;i<n;i++)
            scanf("%d",&s[i]);
        for(i=0;i<n;i++)
            lis[i]=lds[i]=1;
        for(i=0;i<n;i++)
            for(j=0;j<i;j++)
                if(s[i]>s[j])
                    lis[i]>?=lis[j]+1;
        for(i=n-1;i>=0;i--)
            for(j=n-1;j>i;j--)
                if(s[i]>s[j])
                    lds[i]>?=lds[j]+1;
        for(i=0;i<n;i++)
            printf("%d ",lis[i]);
        puts("");
        for(i=0;i<n;i++)
            printf("%d ",lds[i]);
        puts("");
        for(i=0,max=1;i<n;i++)
            if(lis[i]==lds[i])
                max>?=lis[i]+lds[i];
        printf("%d\n",max-1);
    }
}
