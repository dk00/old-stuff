#include<stdio.h>
class stat{
public:
	int a,b,pou;
	void operator=(stat s){a=s.a;b=s.b;pou=s.pou;}
}h[41000],now,tmp;
int size,done[201][201];
main(){
int i,j,t,a,b,c,d,pou,max,minp;
scanf("%d",&t);
while(t--){
	scanf("%d %d %d %d",&a,&b,&c,&d);
	for(i=0;i<=a;i++)
	    for(j=0;j<=b;j++)done[i][j]=2147483647;
	max=h[0].a=h[0].b=0;
	done[0][0]=0;
	minp=2147483647;
	size=1;
	for(i=0,j=1;i<j;i++){
        pou=done[h[i].a][h[i].b];
		if(h[i].a==d || h[i].b==d || c-h[i].a-h[i].b==d){
			max=d;
			minp=pou;
			break;
		}
		if(h[i].a>max && h[i].a<=d){
			max=h[i].a;
			minp=pou;
		}
 		if(h[i].b>max && h[i].b<=d){
			max=h[i].b;
			minp=pou;
		}
		if(c-h[i].a-h[i].b>max && c-h[i].a-h[i].b<=d){
			max=c-h[i].a-h[i].b;
			minp=pou;
		}
		if((h[i].a==max || h[i].b==max) && pou<minp)
		    minp=pou;
		// -> a
		now.b=h[i].b;
		now.a=(a<?(c-h[i].b));
		now.pou=now.a-h[i].a;
		if(now.pou>0 && now.pou+pou<done[now.a][now.b]){
		    h[j++]=now;
		    done[now.a][now.b]=now.pou+pou;
		}
		// -> b
		now.a=h[i].a;
		now.b=(b<?(c-h[i].a));
		now.pou=now.b-h[i].b;
		if(now.pou>0 && now.pou+pou<done[now.a][now.b]){
			h[j++]=now;
			done[now.a][now.b]=now.pou+pou;
		    //printf("->b: %d %d(%d)\n",now.a,now.b,now.pou);
		}
		// a -> b
		now.b=(h[i].a+h[i].b)<?b;
        now.a=(h[i].a-b+h[i].b)>?0;
		now.pou=h[i].a-now.a;
		if(now.pou>0 && now.pou+pou<done[now.a][now.b]){
			h[j++]=now;
			done[now.a][now.b]=now.pou+pou;
		}
		// b -> a
		now.a=(h[i].a+h[i].b)<?a;
        now.b=(h[i].b-a+h[i].a)>?0;
		now.pou=h[i].b-now.b;
		if(now.pou>0 && now.pou+pou<done[now.a][now.b]){
			h[j++]=now;
			done[now.a][now.b]=now.pou+pou;
		}
		// a ->
		now.a=0;
		now.b=h[i].b;
		now.pou=h[i].a;
		if(now.pou>0 && now.pou+pou<done[now.a][now.b]){
			h[j++]=now;
			done[now.a][now.b]=now.pou+pou;
		}
		// b ->
		now.a=h[i].a;
		now.b=0;
		now.pou=h[i].b;
 		if(now.pou>0 && now.pou+pou<done[now.a][now.b]){
			h[j++]=now;
			done[now.a][now.b]=now.pou+pou;
		}
	}
	printf("%d %d\n",minp,max);
}
}
