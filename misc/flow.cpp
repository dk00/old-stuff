/*
PROB: ditch
ID: s0000151
LANG: C++
*/
#include<stdio.h>
int n,s,t,p[300],q[300],c[300][300];
int flow(){
int i,j,k,f,sum=0;
    while(1){
        q[0]=s;
        for(i=0;i<n;i++)
            p[i]=-1;
        p[s]=-2;
        for(i=0,j=1;i<j;i++){
            if(q[i]==t)break;
            for(k=0;k<n;k++)
                if(p[k]==-1 && c[q[i]][k]>0){
                    p[k]=q[i];
                    q[j++]=k;
                }
        }
        if(q[i]!=t || i>=j)break;
        f=c[p[q[i]]][q[i]];
        for(j=p[q[i]];p[j]!=-2;j=p[j])
            f<?=c[p[j]][j];
        sum+=f;
        for(j=q[i];p[j]!=-2;j=p[j]){
            c[p[j]][j]-=f;
            c[j][p[j]]+=f;
        }
    }
    return sum;
}
main(){
int i,j,k,m;
freopen("ditch.in","r",stdin);
freopen("ditch.out","w",stdout);
scanf("%d %d",&m,&n);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c[i][j]=0;
    while(m--){
        scanf("%d %d %d",&i,&j,&k);
        i--,j--;
        c[i][j]+=k;
    }
    s=0,t=n-1;
    printf("%d\n",flow());

}
