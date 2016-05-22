#include<stdio.h>
#include<stdlib.h>
int s[9],d[36],u[36];
int numcmp(const void *a,const void *b){return *(int *)a-*(int *)b;}
main(){
int i,j,k,p,a,b,c,n,m,find;
while(scanf("%d",&n)!=EOF){
    m=n*(n-1)/2;
    for(i=m-1,p=0;i>=0;i--)
        scanf("%d",&d[i]),u[i]=1;
    if(n==2){
        printf("%d %d\n",d[0]>>1,(d[0]>>1)|1);
        continue;
    }
    if(n==3){
        i=d[0]+d[1]-d[2];
        j=d[0]-d[1]+d[2];
        k=d[1]-d[0]+d[2];
        if(i&1 || j&1 || k&1)
            puts("Impossible");
        else
            printf("%d %d %d\n",i>>1,j>>1,k>>1);
    }
    qsort(d,m,sizeof(d[0]),numcmp);
    for(i=1;i<m && !find;i++)
        for(j=i+1;j<m && !find;j++){
            a=d[0]+d[i]-d[j];
            b=d[0]-d[i]+d[j];
            c=d[i]-d[0]+d[j];
            if(a&1 || b&1 || c&1)
                continue;
            a>>=1,b>>=1,c>>=1;
            if(a+b==d[0] && b+c==d[j] && a+c==d[i]){
                find=1;
                break;
            }
        }
    if(!find){
        puts("Impossible");
        continue;
    }
    s[p++]=a;
    s[p++]=b;
    s[p++]=c;
    u[0]=u[i]=u[j]=0;
    for(i=1;i<m && !find;i++){
        if(!u[i])continue;
        for(j=i+1;j<m && !find;j++){
            if(!u[j])continue;
            a=d[m-1]+d[i]-d[j];
            b=d[m-1]-d[i]+d[j];
            c=d[i]-d[m-1]+d[j];
            if(a&1 || b&1 || c&1)
                continue;
            a>>=1,b>>=1,c>>=1;
            if(a+b==d[m-1] && b+c==d[j] && a+c==d[i]){
                find=1;
                break;
            }
        }
    }
    if(!find){
        puts("Impossible");
        continue;
    }
    for(i=0;i<m;i++)u[i]=1;
    s[p++]=a;
    s[p++]=b;
    s[p++]=c;
    for(i=0;i<p;i++)
        for(j=i+1;j<p;j++)
            for(k=0;k<m;k++)
                if(u[k] && d[k]==s[i]+s[j]){
                    u[k]=0;
                    break;
                }
    n-=6;
    while(n--){
        for(i=0;i<m;i++){
            if(!u[i])continue;
            for(j=i+1;j<m;j++){
                if(!u[j])continue;
                for(k=j+1;k<m;k++){
                    if(!u[k])continue;
                    a=d[i]+d[j]-d[k];
                    b=d[i]-d[j]+d[k];
                    c=d[j]-d[i]+d[k];
                    if(a&1 || b&1 || j&1)
                        continue;
                    a>>=1,b>>=1,c>>=1;
                    if(
                }
            }
        }
    }
}
}
