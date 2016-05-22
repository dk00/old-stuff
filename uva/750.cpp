#include<stdio.h>
int row[8],col[8],rc[15],cr[15],soln;
void dfs(int c){
   if(c>=8){
       printf(" %-7d",soln++);
       for(c=0;c<8;c++)
           printf(" %d",col[c]+1);
       printf("\n");
       return;
   }
   if(col[c]!=-1){
       dfs(c+1);
       return;
   }
   int r=0;
   for(;r<8;r++){
       for(;r<8 && (row[r]+rc[7+r-c]+cr[r+c])<3;r++);
       if(r>=8)break;
       rc[7+r-c]=0;cr[r+c]=0;
       row[r]=0;col[c]=r;
       dfs(c+1);
       rc[7+r-c]=1;cr[r+c]=1;
       row[r]=1;col[c]=-1;
   }
}
main(){
int x,y,n;
scanf("%d",&n);
for(;n>0;n--){
   for(x=0;x<8;x++){
       row[x]=1;col[x]=-1;rc[x]=1;cr[x]=1;
   }
   for(;x<15;x++){
       rc[x]=1;cr[x]=1;
   }
   scanf("%d %d",&x,&y);
   x--;y--;col[y]=x;row[x]=0;
   rc[7+x-y]=0;cr[x+y]=0;
   printf("SOLN        COLUMN\n");
   printf(" #       1 2 3 4 5 6 7 8\n\n");
   soln=1;
   dfs(0);
}
}
