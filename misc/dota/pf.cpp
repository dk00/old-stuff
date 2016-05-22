#include<string>
#include<stdio.h>
#include<algorithm>
const int N=999;
char tmp[99999];
int n,m,s[N];
struct pt
{
	int x,y;
	bool operator<(pt a)const
	{
		if(x!=a.x)return x<a.x;
		return y<a.y;
	}
}ans[N];
void _print(int x,int y){
  printf("(");
  if(x>1||x<0)printf("%d",x);
  printf("X");
  if(y>=0)printf("+%d",y);
  else printf("%d",y);
  printf(")");
}
void print(int x,int y)
{
	ans[m++]=(pt){x,y};
}
long long abs(long long x){
	if(x<0)return -x;
	return x;
}
main(){
  int i,j,l,p,k,r;
  
  while(scanf("%s",tmp)>0 &&(tmp[0]!='0' || tmp[1]))
  {
    for(i=0;i<=100;i++)s[i]=0;
    for(i=0;tmp[i];)
    {
      p=0,r=k=1;
      if(tmp[i]=='+' || tmp[i]=='-')
      {
        if(tmp[i]=='-')r=-1;
        i++;
      }
      if(tmp[i]>='0' && tmp[i]<='9')
        for(k=0;tmp[i]>='0' && tmp[i]<='9';i++)
          k=k*10+tmp[i]-'0';
      if(tmp[i]=='X')p=1,i++;
      if(tmp[i]=='^')
        for(p=0,i++;tmp[i]>='0' && tmp[i]<='9';i++)
          p=p*10+tmp[i]-'0';
      s[p]=k*r;
    }
    for(n=100;!s[n];n--);
    /*for(i=0;i<=n;i++)printf(" %d",s[i]);
    puts("");*/
    long long d[N],e[N];;
    for(m=0;n>1;n--){
		
      r=0;
      for(j=1;j<=s[n];j++){
        if(s[n]%j!=0)continue;
        for(k=-abs(s[0]);k<=abs(s[0]);k++){
		  if(k==0){
			if(s[0]==0){
				print(j,0);
				for(i=0;i<n;i++)s[i]=s[i+1];
				r=1;
				break;
			}
			continue;
		  }
          if(s[0]%k!=0)continue;
          d[n]=s[n];
          for(l=n;l>0;l--){
            if(d[l]%j!=0)break;
            d[l-1]=s[l-1]-d[l]/j*k;
            e[l-1]=d[l]/j;
            if(abs(d[l-1])>1000000000)break;
          }
          if(l==0&&d[0]==0){
            for(l=0;l<=n-1;l++)s[l]=e[l];
            print(j,k);
            r=1;
            break;
          }
        }
        if(r==1)break;
      }      
    }
    print(s[1],s[0]);
    std::sort(ans,ans+m);
    for(int i=0;i<m;i++)
    	_print(ans[i].x,ans[i].y);
    puts("");
  }
}
