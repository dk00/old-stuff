#include<stdio.h>
class stat{
public:
	int a,b,pou;
	void operator=(stat s){a=s.a;b=s.b;pou=s.pou;}
}h[41000],now,tmp;
int size,done[201][201];
void adjup(int p){
	if(((p-1)>>1)>0 && h[(p-1)>>1].pou>h[p].pou){
		tmp=h[p];
		h[p]=h[(p-1)>>1];
		h[(p-1)>>1]=tmp;
		adjup((p-1)>>1);
	}
}
void insert(stat s){
	if(!s.a && !s.b)return;
	h[size]=s;
	adjup(size++);
}
void adjdown(int p){
	if((p<<1)+1<size && h[p].pou>h[(p<<1)+1].pou){
		tmp=h[p];
		h[p]=h[(p<<1)+1];
		h[(p<<1)+1]=tmp;
		adjdown((p<<1)+1);
	}
	else if((p<<1)+2<size && h[p].pou>h[(p<<1)+2].pou){
		tmp=h[p];
		h[p]=h[(p<<1)+2];
		h[(p<<1)+2]=tmp;
		adjdown((p<<1)+2);
	}
}
void popmin(){
	h[0]=h[--size];
	adjdown(0);
}
main(){
int i,j,t,a,b,c,d,pou,max,minp;
scanf("%d",&t);
freopen("10603.out","w",stdout);
while(t--){
	scanf("%d %d %d %d",&a,&b,&c,&d);
	for(i=0;i<=a;i++)
	    for(j=0;j<=b;j++)done[i][j]=2147483647;
	max=h[0].a=h[0].b=0;
	done[0][0]=0;
	minp=2147483647;
	size=1;
	while(size){
		/*printf(" * ");
		for(i=0;i<size;i++)printf("%d ",h[i].pou);
		puts("");*/
        pou=done[h[0].a][h[0].b];
		//printf("%d %d %d\n",h[0].a,h[0].b,done[h[0].a][h[0].b]);
		if(h[0].a==d || h[0].b==d || c-h[0].a-h[0].b==d){
			max=d;
			minp=pou;
			break;
		}
		if(h[0].a>max && h[0].a<=d){
			max=h[0].a;
			minp=pou;
		}
 		if(h[0].b>max && h[0].b<=d){
			max=h[0].b;
			minp=pou;
		}
		if(c-h[0].a-h[0].b>max && c-h[0].a-h[0].b<=d){
			max=c-h[0].a-h[0].b;
			minp=pou;
		}
		if((h[0].a==max || h[0].b==max) && pou<minp)
		    minp=pou;
		// -> a
		now.b=h[0].b;
		now.a=(a<?(c-h[0].b));
		now.pou=now.a-h[0].a;
		if(now.pou>0 && now.pou+pou<done[now.a][now.b]){
		    insert(now);
		    done[now.a][now.b]=now.pou+pou;
		    //printf("->a: %d %d(%d)\n",now.a,now.b,now.pou);
		}
		// -> b
		now.a=h[0].a;
		now.b=(b<?(c-h[0].a));
		now.pou=now.b-h[0].b;
		if(now.pou>0 && now.pou+pou<done[now.a][now.b]){
			insert(now);
			done[now.a][now.b]=now.pou+pou;
		    //printf("->b: %d %d(%d)\n",now.a,now.b,now.pou);
		}
		// a -> b
		now.b=(h[0].a+h[0].b)<?b;
        now.a=(h[0].a-b+h[0].b)>?0;
		now.pou=h[0].a-now.a;
		if(now.pou>0 && now.pou+pou<done[now.a][now.b]){
			insert(now);
			done[now.a][now.b]=now.pou+pou;
			//printf("a -> b: %d %d(%d)\n",now.a,now.b,now.pou);
		}
		// b -> a
		now.a=(h[0].a+h[0].b)<?a;
        now.b=(h[0].b-a+h[0].a)>?0;
		now.pou=h[0].b-now.b;
		if(now.pou>0 && now.pou+pou<done[now.a][now.b]){
			insert(now);
			done[now.a][now.b]=now.pou+pou;
			//printf("b -> a: %d %d(%d)\n",now.a,now.b,now.pou);
		}
		// a ->
		now.a=0;
		now.b=h[0].b;
		now.pou=h[0].a;
		if(now.pou>0 && now.pou+pou<done[now.a][now.b]){
			insert(now);
			done[now.a][now.b]=now.pou+pou;
			//printf("a ->: %d %d(%d)\n",now.a,now.b,now.pou);
		}
		// b ->
		now.a=h[0].a;
		now.b=0;
		now.pou=h[0].b;
 		if(now.pou>0 && now.pou+pou<done[now.a][now.b]){
			insert(now);
			done[now.a][now.b]=now.pou+pou;
			//printf("b ->: %d %d(%d)\n",now.a,now.b,now.pou);
		}
		popmin();
	}
	printf("%d %d\n",minp,max);
}
}
