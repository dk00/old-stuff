#include<stdio.h>

const int dim[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

struct date{
	int d,m,y;
};

int spy(int y){
	if(y%4!=0)
		return 0;
	else if(y%100!=0)
		return 1;
	else if(y%400!=0)
		return 0;
	return 1;
}

int time(date d){
	int tmp;
	if(d.d>1){
		tmp=d.d-1;
		d.d=1;
		return time(d)+tmp;
	}
	else if(d.m>1){
		if(d.m!=3){
			d.m--;
			return time(d)+dim[d.m];
		}
		else{
			d.m--;
			return time(d)+dim[d.m]+spy(d.y);
		}
	}
	else if(d.y>1700){
		d.y--;
		return time(d)+365+spy(d.y);
	}
	return 1;
}

date dot(int t){
	date d;
	d.y=1700;
	d.m=1;
	d.d=1;
	while(time(d)<=t)
		d.y++;
	d.y--;
	while(time(d)<=t)
		d.m++;
	d.m--;
	d.d=t-time(d)+1;
	return d;
}

char timeline[200000];

int main(){
	int a,b,in1,in2,i,t1,t2,T=0,flag;
	for(a=1;a!=0;a++);
	date d1,d2;
	while(++T){
		for(i=1;i<150000;i++)
			timeline[i]=0;
		scanf("%d %d",&a,&b);
		if(a+b<=0)
			break;
		flag=0;
		while(a--){
			scanf("%d %d",&in1,&in2);
			d1.y=in1/10000;
			d2.y=in2/10000;
			d1.m=(in1/100)%100;
			d2.m=(in2/100)%100;
			d1.d=in1%100;
			d2.d=in2%100;
			t1=time(d1);
			t2=time(d2);
			for(i=t1;i<=t2;i++)
				timeline[i]=1;
		}
		while(b--){
			scanf("%d %d",&in1,&in2);
			d1.y=in1/10000;
			d2.y=in2/10000;
			d1.m=(in1/100)%100;
			d2.m=(in2/100)%100;
			d1.d=in1%100;
			d2.d=in2%100;
			t1=time(d1);
			t2=time(d2);
			for(i=t1;i<=t2;i++){
				if(timeline[i]==0)
					timeline[i]=2;
			}
		}
		t1=-1;
		t2=-1;
		printf("Case %d:\n",T);
		while(t2<150000){
			t1=t2+2;
			for(t2=t1;timeline[t2]==2;t2++);
			t2--;
			if(t1<=t2){
				d1=dot(t1);
				d2=dot(t2);
				flag=1;
			}
			if(t1<t2)
				printf("    %d/%d/%d to %d/%d/%d\n",d1.m,d1.d,d1.y,d2.m,d2.d,d2.y);
			else if(t1==t2)
				printf("    %d/%d/%d",d1.m,d1.d,d1.y);
		}
		if(flag==0)
			puts("    No additional quotes are required.");
		puts("");
	}
}
