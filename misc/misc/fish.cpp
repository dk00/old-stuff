#include<queue>
#include<vector>
#include<cstdio>
using namespace std;
const int N=1001,MaxF=1000;
struct Pond{
	int f,d,h;
	int operator!()const{return (2*f-d*(h-1))*h/2;}
	int operator+()const{return f-d*h;}
	int operator-()const{return f-d*(h-1);}
	bool operator<(Pond& a)const{return +*this>+a;}
}s[N];
struct Heap{
    priority_queue<int,vector<int>,cmp> H;
    int i;
    void operator+=(int k){if(s[k].h>0)H.push(k);}
    int operator--(int){
        int k=c[i].back();
        c[i].pop_back();
        if(s[k].h)s[k].h--,*this+=k;
        for(;i<MaxF && !c[i].size();i++);
        print();
        return k;
    }
};
int T,sum,t[N];
int go(int n)
{
	int i,j,k,Max,now,end;
	Heap H;
	H.i=s[0].f;
	for(i=j=Max=now=sum=0,end=-1;i<n;i++){
		s[i].h=0;
		now+=t[i];
		if(now<T){
			s[i].h=s[i].d?(1+(s[i].f-1)/s[i].d):T-now;
			if(T-now<s[i].h)
				s[i].h=T-now;
			now+=s[i].h;
			sum+=!s[i];
			if(sum>Max)end=i,Max=now;
		}
		for(;now>T;now--)
			sum-=+s[H--];
		while(now>=T && +s[i]>H.i){
			sum+=+s[i];
            sum-=+s[H--];
            s[i].h++;
        }
		if(s[i].h>0)
			H+=i;
		if(sum>Max)end=i,Max=sum;
	}
	return end;
}
main()
{
	int i,j,n,end;
	while(scanf("%d %d",&n,&T)==2){
		for(i=1;i<n;i++)
			scanf("%d",t+i);
		for(i=0;i<n;i++)
			s[i].h=0,scanf("%d",&s[i].f);
		for(i=0;i<n;i++)
			scanf("%d",&s[i].d);
		end=go(n);
		go(end+1);
		for(i=0;i<=end;i++){
			if(i)
				printf("Drive %d hour(s) from pond %d to pond %d.\n",t[i],i,i+1);
			for(j=0;j<s[i].h;j++)
				printf("Fish  in pond %d for an hour and get %d pound(s) of fish.\n",i+1,s[i].f-s[i].d*j);
		}
		printf("Total: %d pounds\n",sum);
	}
}
