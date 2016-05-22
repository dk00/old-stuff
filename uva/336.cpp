#include<stdio.h>
int main(){
int n,i,j,net[30][30],k1,k2,nnum,node[10000],
ttl,Case=1,s[10000],reach[30],top,nreached;
while(1){
	scanf("%d",&n);
	if(n<=0)
	   break;
	for(i=0;i<30;i++){
		for(j=0;j<30;j++)
			net[i][j]=0;
	}
	for(i=0;i<10000;i++)
		node[i]=-1;
	nnum=0;
	for(i=0;i<n;i++){
		scanf("%d %d",&k1,&k2);
		if(node[k1]<0)
			node[k1]=nnum++;
		if(node[k2]<0)
			node[k2]=nnum++;
		net[node[k1]][node[k2]]=1;
		net[node[k2]][node[k1]]=1;
	}
	for(;;Case++){
		for(i=0;i<nnum;i++){
			 reach[i]=-1;
		}
		for(i=0;i<10000;i++){
			s[i]=-1;
		}
		scanf("%d %d",&j,&ttl);
		s[0]=node[j];
		top=0;
		nreached=0;
		reach[s[0]]=ttl;
		if(j==0 && ttl==0)
			break;
		k1=j;
		for(i=0;;i++){
			if(reach[s[i]]<=0)
				break;
			for(j=0;j<nnum;j++){
				if(net[s[i]][j]==1 && reach[j]<reach[s[i]]-1){
                    reach[j]=reach[s[i]]-1;
                    s[++top]=j;
                }
            }
        }
		for(i=1;i<nnum;i++){
            if(reach[i]<0)
                nreached++;
        }
        printf("Case %d: %d nodes not reachable from node %d with TTL = %d.\n"
        ,Case,nreached,k1,ttl);

    }
}
return 0;
}
