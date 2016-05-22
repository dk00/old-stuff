#include<cstdio>
#include<algorithm>
using namespace std;
main()
{
    int i,j,k,n,T;
    char tmp[99];
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(i=0;i<n;i++){
            scanf("%s",tmp);
            for(j=0;tmp[j];j++);
            while(tmp[--j]=='0');
            s[i]=j;
        }
        for(i=k=0;i<n;i++)
            for(j=1;j<n;j++)
                if(s[j-1]>j-1)
                    k++,swap(s[j-1],s[j]);
        printf("Case #%d: %d\n",C++,k);
    }
}
