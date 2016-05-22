#include<cstdio>
#include"bst2.h"
const int max=2147483647;
main()
{
    bst s1,s2;
    bst::node tmp1,tmp2;
    int i,j,k,l,n,t,C=0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        s1.clear(),s2.clear();
        s1.insert(0,max),s1.insert(max,0);
        s2.insert(0,max),s2.insert(max,0);
        s1.n-=2,s2.n-=2;
        while(n--)
        {
            scanf("%d %d",&i,&k),i++,k++;
            tmp1=*s1.find(i),tmp2=*s2.find(k);
            j=tmp2.b,l=tmp1.b;
            if(j>=max)j=max-1;
            if(k>=max)k=max-1;
            if(i!=tmp1.a || k!=tmp1.b)
                s1.remove(i,j),s2.remove(k,l);
            if(i<=j || i<=s1.find(j+1)->a)
                s1.insert(i,k),s2.insert(k,i);
            printf("%d--------------\n",s1.n);
            tmp1=*s1.find(0);
            tmp1=*s1.find(tmp1.a+1);
            while(tmp1.a<2147483647)
            {
                printf("%d %d\n",tmp1.a-1,tmp1.b-1);
                tmp1=*s1.find(tmp1.a+1);
            }
            puts("--------------------------");
            tmp1=*s2.find(0);
            tmp1=*s2.find(tmp1.a+1);
            while(tmp1.a<2147483647)
            {
                printf("%d %d\n",tmp1.a-1,tmp1.b-1);
                tmp1=*s2.find(tmp1.a+1);
            }
        }
        printf("-%d-\n",t);
    }
}
