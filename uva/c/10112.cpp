#include<stdio.h>
#include<stdlib.h>
int inline tri(int x1,int y1,int x2,int y2,int x3,int y3){
    return abs((y3-y1)*(x2-x1)-(y2-y1)*(x3-x1));
}
main(){
int i,j,k,l,n,r,mi,mj,mk,max,x[20],y[20];
char s[10];
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++)scanf("%s %d %d",s,&x[i],&y[i]);
    max=-1;
    for(i=0;i<n-2;i++)
        for(j=i+1;j<n-1;j++)
            for(k=j+1;k<n;k++){
                r=tri(x[i],y[i],x[j],y[j],x[k],y[k]);
                for(l=0;l<n;l++){
                    if(l==i || l==j || l==k)continue;
                    if(r==tri(x[i],y[i],x[j],y[j],x[l],y[l])+
                    tri(x[i],y[i],x[k],y[k],x[l],y[l])+
                    tri(x[k],y[k],x[j],y[j],x[l],y[l])){
                        r=0;
                        break;
                    }
                }
                if(!r)continue;
                if(r>max){
                    max=r;
                    mi=i,mj=j,mk=k;
                }
            }
    printf("%c%c%c\n",mi+'A',mj+'A',mk+'A');
}
}
