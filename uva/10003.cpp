#include<stdio.h>
#define Min(a,b) (a)<(b)?(a):(b)
main(){
int cut[50][50],c[52],i,j,k,l,n,tmp1,tmp2,min;
c[0]=0;
while(1){
	scanf("%d",&l);
	if(l<=0)break;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",&c[i]);
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			cut[i][j]=0;
	}
	c[i+1]=l;
    for(i=0;i<n;i++)
        cut[i][i]=c[i+2]-c[i];
    for(i=1;i<n;i++){       //col
        for(j=0;i+j<n;j++){   //row
			tmp1=cut[j][i+j-1];
			tmp2=cut[j+1][i+j];
			min=Min(tmp1,tmp2);
			for(k=j;k<=i+j-2;k++){
				tmp1=cut[j][k]+cut[k+2][j+i];
				min=Min(min,tmp1);
			}
            cut[j][i+j]=min+c[i+j+2]-c[j];
        }
    }
    printf("The minimum cutting is %d.\n",cut[0][n-1]);
}
}
