#include <stdio.h>
main(){
   int i,j,k,t,m,s[10000];
       for(i=0;scanf("%d",&k)!=EOF;i++){
           for(j=i-1;j>=0;j--)
               if(k>s[j])
                   break;
           t=j+1;
           for(j=i;j>t;j--)
               s[j]=s[j-1];
           s[t]=k;
           if((i+1)%2==0)
               m=(s[(i+1)/2-1]+s[(i+1)/2])/2;
           else
               m=s[(i+1)/2];
           printf("%d\n",m);
       }
}
