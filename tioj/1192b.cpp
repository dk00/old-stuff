#include<stdio.h>
#include<string.h>
char a[1000000];
int x[500000],xx,y[500000],yy;
int main(){
   int C,n,l,i,cc,flag;
   scanf("%d",&C);
   while(C--){
      scanf("%d%d",&n,&l);
      memset(a,0,sizeof(a));
      for(cc=flag=0;cc<n;cc++){
         xx=yy=0;
         while(scanf("%d",&x[xx]),x[xx])xx++;
         while(scanf("%d",&y[yy]),y[yy])yy++;
         if(flag)continue;
         for(i=0;i<xx;i++)
            if(a[x[i]-1]==1)
               goto NEXT;
         for(i=0;i<yy;i++)
            if(a[y[i]-1]==2)
               goto NEXT;
         for(i=0;i<xx;i++)
            a[x[i]-1]=2;
         for(i=0;i<yy;i++)
            a[y[i]-1]=1;
         continue;
         NEXT:
         for(i=0;i<xx;i++)
            if(a[l-x[i]]==1)
               goto NEXT2;
         for(i=0;i<yy;i++)
            if(a[l-y[i]]==2)
               goto NEXT2;
         for(i=0;i<xx;i++)
            a[l-x[i]]=2;
         for(i=0;i<yy;i++)
            a[l-y[i]]=1;
         continue;
         NEXT2:flag=1;
      }
      if(flag==1)puts("No");
      else       puts("Yes");
   }
}
