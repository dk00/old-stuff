#include<stdio.h>
#include<stdlib.h>
struct DNA{
    int uns,oid;
}data[1000];
int dnacmp(const void *a,const void *b){
    if(((DNA *)a)->uns==((DNA *)b)->uns)
        return ((DNA *)a)->oid-((DNA *)b)->oid;
    return ((DNA *)a)->uns-((DNA *)b)->uns;
}
char dna[100][100];
main(){
int i,j,k,n,m,t;
char c;
scanf("%d",&t);
while(t--){
    scanf("%d %d%c",&n,&m,&c);
    for(i=0;i<m;i++){
        gets(dna[i]);
        data[i].oid=i;
        for(data[i].uns=j=0;j<n;j++)
            for(k=j+1;k<n;k++)
                if(dna[i][j]>dna[i][k])
                    data[i].uns++;
    }
    qsort(data,m,sizeof(data[0]),dnacmp);
    for(i=0;i<m;i++)puts(dna[data[i].oid]);
    if(t)puts("");
}
}
