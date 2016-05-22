/*
PROB:crypt1
LANG:C++
*/
#include<cstdio>
char u[10];
int val(int n){return(u[n%10] &&(n<10 || val(n/10)));}
main()
{
    freopen("crypt1.in","r",stdin);
    freopen("crypt1.out","w",stdout);
    int i,j,k;
    scanf("%d",&k);
    while(k--)
        scanf("%d",&i),u[i]=1;
    for(i=111,k=0;i<1000;i++)
        if(val(i))
            for(j=11;j<100;j++)
                if(val(j) && val(j%10*i) && j%10*i<1000 &&
                j/10*i<1000 && val(j/10*i) && val(i*j))k++;
    printf("%d\n",k);
}
