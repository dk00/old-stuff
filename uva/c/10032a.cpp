/* @JUDGE_ID: 14949NT 10032 C++ "Greedy" */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long i,j,k,t,tmp,tmpx,num,cnt,sum,a[50],b[50],suma,sumb,na,nb,dif;

long find()
{
	for(i=0;i<na;i++)
	{
		for(j=0;j<nb;j++)
		{
			if(abs(dif-2*a[i]+2*b[j])<dif)
			{
				dif=abs(dif-2*a[i]+2*b[j]);
				tmp=b[j];
				b[j]=a[i];
				a[i]=tmp;
				return 1;
			}
		}
	}
	return 0;
}
main()
{
	int cases;
	scanf("%d",&cases);
	for(k=0;k<cases;k++)
	{
		scanf("%ld",&num);
		suma=0;
		sumb=0;
		for(i=0;i<50;i++)
		{
			a[i]=0;
			b[i]=0;
		}
		if(num%2==0)
		{
			na=num/2;
			nb=na;
		}
		else
		{
			na=(num+1)/2;
			nb=na-1;
		}
		for(i=0;i<num;i++)
		{
			if(i%2==0)
			{
				scanf("%ld",&a[i/2]);
				suma+=a[i/2];
			}
			else
			{
				scanf("%ld",&b[(i-1)/2]);
				sumb+=b[(i-1)/2];
			}
		}
		dif=abs(suma-sumb);
		while(find())
			;
		printf("%ld %ld\n",(suma+sumb-dif)/2,(suma+sumb-dif)/2+dif);
		if(k!=cases-1)
			printf("\n");
	}
}
