#include <stdio.h>
main(){
    int a[10000],b[10000],ans[10000],i;
    int lena,lenb,len;
    char c;
    while(1){
	if(scanf("%c",&c)==EOF) break;
	a[0]=c-'0';
	for(i=1;scanf("%c",&c) && c!='\n';i++)
	    a[i]=c-'0';
	lena=i;
	for(i=0;scanf("%c",&c) && c!='\n';i++)
	    b[i]=c-'0';
	lenb=i;
	len=(lena>lenb)?(lena):(lenb);
	for(i=len-1;i>=lena-lenb;i--)
	    b[i]=b[i-(lena-lenb)];
	for(b[i]=0;i>=0;i--)
	    b[i]=0;
	for(i=0;i<len;i++)
	    ans[i]=a[i]-b[i];
	for(i=len-1;i>0;i--)
	    if(ans[i]<0){
		ans[i]+=10;
		ans[i-1]--;
	    }
	for(i=0;i<len && ans[i]==0;i++);
	if(i==len) printf("0");
	for(;i<len;i++)
	    printf("%d",ans[i]);
	puts("");
    }
}
