#include<stdio.h>
int sub(char s[],char r[],int l,int j){
int i;
    r[l]+=j*2-1;
	for(i=l;i>0;i--)
        if(r[i]>'9'){
            r[i-1]+=(r[i]-'0')/10;
            r[i]=(r[i]-'0')%10+'0';
        }
    for(i=0;i<=l && s[i]==r[i];i++);
    if(s[i]<r[i])return 0;
    for(i=l;i>=0;i--){
        s[i]-=(r[i]-'0');
        if(s[i]<'0'){
            s[i-1]--;
            s[i]+=10;
        }
	}
    r[l]-=j*2-1;
    for(i=l;i>0;i--)
        while(r[i]<'0'){
            r[i-1]--;
            r[i]+=10;
        }
    return 1;
}
main(){
int i,j,n,tt;
char s[1020],t[520],r[520];
char _s[1001],_t[1001],_r[1001],_j;
scanf("%d",&tt);
while(tt--){
    scanf("%s",s);
    for(n=0;s[n];n++);//s[n]-='0';
    if(n%2){
		for(i=n-1;i>=0;i--)s[i+1]=s[i];
		s[0]='0';
		n++;
	}
	else{
	   for(i=n++-1;i>=0;i--)s[i+1]=s[i];
	   s[0]='0';
	   for(i=n++-1;i>=0;i--)s[i+1]=s[i];
	   s[0]='0';
    }
	for(j=0;j<=n/2;j++)t[j]='0';
	t[j]=0;
	for(i=1;i<n;i+=2){
		for(r[0]='0',j=i/2;j>=0;j--)
			r[j+1]=((t[j]-'0')<<1);
		for(r[0]='0',j=i/2;j>=0;j--)
			if(r[j+1]>9){
				r[j]+=r[j+1]/10;
				r[j+1]=r[j+1]%10;
			}
		for(r[0]='0',j=i/2+1;j>0;j--)r[j]+='0';
		r[i/2+2]=0;
		for(j=1;sub(&s[i/2],r,i/2+1,j);j++){
			/*s[]-t[]*2-2*j-1>0*/
		}
        t[i/2]=j-1+'0';
    }
    t[n/2]=0;
    puts(t[0]=='0'?&t[1<?(n/2-1)]:t);
    if(tt)puts("");
}
}
