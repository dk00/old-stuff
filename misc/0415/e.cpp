#include<map>
#include<cstdio>
#include<string>
using namespace std;
char color[][9]={"black","brown","red","orange","yellow",
"green","blue","violet","gray","white"};
char c0[][9]={"red","gold","silver"};
char c1[][9]={"2%","5%","10%"};
char a[99],b[99];
main()
{
    freopen("pe.in","r",stdin);
    map<string,int> val;
    map<string,string> tr;
    int i,j,T,C=1;
    long long k;
    for(i=0;i<10;i++)
	val[color[i]]=i;
    for(i=0;i<3;i++)
	tr[c0[i]]=c1[i];
    scanf("%d",&T);
    while(T--){
	scanf("%s %s",a,b);
	k=val[a]*10+val[b];
	scanf("%s %s",a,b);
	i=val[a];
	while(i--)k*=10;
	printf("%d ",C++);
	if(k>=1000000)
	    printf("%lld.%lldM ohms",k/1000000,k%1000000/100000);
	else if(k>=1000)
	    printf("%lld.%lldK ohms",k/1000,k%1000/100);	
	else
	    printf("%lld.0 ohms",k);
	printf(" %s\n",tr[b].c_str());

    }

}
