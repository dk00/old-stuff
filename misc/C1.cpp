#include <stdio.h>

int vis[10010];
int prime[1300];
int dig[1010];
int m,n;
int rema[1300][1010];
int rev10[1300];

void makeprime(){
    int i,j;
    
    vis[1]=vis[0]=1;
    for(i=2;i<=10000;i++)
        if(!vis[i])
            for(j=i*2;j<=10000;j+=i)vis[j]=1;

    j=0;
    for(i=0;i<=10009;i++){
        if(!vis[i] && i!=2 && i!=5)prime[j++]=i;
        vis[i]=0;
    }
    return;
}

void clearvis(){
    for(int i=0;i<10010;i++)
        vis[i]=0;
    return;
}

void makerev(){
    int i,j,k;
    
    for(i=0;i<1236;i++){
        /*j=10%prime[i];
        k=1;
        while(j!=1){
            k=j;
            j*=10;
            j%=prime[i];
            //printf("%d",j);
        }
        rev10[i]=k;*/
        for(j=1;j<prime[i];j++)
            if((10*j)%prime[i]==1)break;
        rev10[i]=j;
    }
    return;
}
    

int main(){
    int i,j,k,d2,d5;

    makeprime();
    makerev();
    
    while(scanf("%d %d",&n,&m)==2){
        clearvis();
        for(i=0;i<n;i++)
            scanf("%d",dig[i]);
        d2=!(m%2);
        d5=!(m%5);
        if(d2 && d5){
            while(dig[n-1]==2 || dig[n-1]==5)
                n--;
        }else if(d2){
            while(dig[n-1]==2)n--;
        }else if(d5){
            while(dig[n-1]==5)n--;
        }
        for(i=0;i<1236;i++)
            if(!(m%prime[i])){
                vis[i]=1;
                rema[i]=0;
                k=10;
                rema[i][n-1]=dig[n-1]%prime[i];
                for(j=n-2;j>=0;j--){
                    rema[i][j]=(rema[i][j-1]+k*dig[j])%prime[i];
                    k=(k*10)%prime[i];
                }
            }
        
    
    return 0;
}
