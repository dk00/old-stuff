#include<stdio.h>
main(){
int i,j,p,q,n,k,m,vic[25];
while(scanf("%d %d %d",&n,&k,&m) && n+k+m){
    for(p=n,i=0;i<n;i++)vic[i]=i+1;
    i=-1,j=0;
    while(p>0){
        q=k%p;
        if(q<=0)q+=p;
        while(q--)
            for(i++,i%=n;vic[i]<0;i++,i%=n);
        q=m%p;
        if(q<=0)q+=p;
        while(q--)
            for(j+=n-1,j%=n;vic[j]<0;j+=n-1,j%=n);
        if(i==j){
            printf("%3d%c",i+1,(p-1)?',':'\n');
            vic[i]=-1;
            p--;
        }
        else{
            printf("%3d%3d%c",i+1,j+1,(p-2)?',':'\n');
            vic[i]=vic[j]=-1;
            p--;p--;
        }
    }
}
}
