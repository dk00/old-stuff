#include<stdio.h>
main(){
long c[7491],i,n;
for(i=0;i<=7490;i++) c[i]=1;
for(i=0;i<=7485;i++) c[i+5]+=c[i];
for(i=0;i<=7480;i++) c[i+10]+=c[i];
for(i=0;i<=7465;i++) c[i+25]+=c[i];
for(i=0;i<=7440;i++) c[i+50]+=c[i];
while(scanf("%ld",&n)!=EOF) printf("%ld\n",c[n]);
}
