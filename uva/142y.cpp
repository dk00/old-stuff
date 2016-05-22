#include<stdio.h>
#include<stdlib.h>
int in,sn,sx[99],sy[99],ex[99],ey[99],px[99],py[99],mark[99];
int dis(int x1,int y1,int x2,int y2){
   return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
int main(){
int i,x1,y1,x2,y2,min;
char s[100],c;
	while(gets(s) && *s!='#'){
		sscanf(s,"%c",&c);
		if(s[0]=='I'){
			sscanf(s,"%c %d %d",&c,&x1,&y1);
			px[in]=x1,py[in]=y1;
			for(i=0;i<sn;i++)
				if(sx[i]<=x1 && x1<=ex[i] && sy[i]<=y1 && y1<=ey[i])
					mark[in]=1;
			in++;
		}
		else if(s[0]=='R'){
			sscanf(s,"%c %d %d %d %d",&c,&x1,&y1,&x2,&y2);
			sx[sn]=x1,sy[sn]=y1,ex[sn]=x2,ey[sn]=y2;
			for(i=0;i<in;i++)
				if(x1<=px[i] && px[i]<=x2 && y1<=py[i] && py[i]<=y2)
					mark[i]=1;
			sn++;
		}
		else if(s[0]=='M'){
			sscanf(s,"%c %d %d",&c,&x1,&y1);
			for(i=sn-1;i>=0;i--)
				if(sx[i]<=x1 && x1<=ex[i] && sy[i]<=y1 && y1<=ey[i])
					break;
			if(i>=0){
				printf("%c\n",i+'A');
				continue;
			}
			min=2147483647;
			for(i=0;i<in;i++){
					if(mark[i])continue;
				if(dis(x1,y1,px[i],py[i])<min)min=dis(x1,y1,px[i],py[i]);
				}
			for(i=0;i<in;i++)
				if(!mark[i] && dis(x1,y1,px[i],py[i])==min)
					printf("%3d",i+1);
			puts("");
		}
    }
    if(gets(s)!=NULL)abort();
}
