#include<time.h>
#include<stdio.h>
#include<stdlib.h>
int test(int a,int b)
{
	int p=rand()&31,q=rand()&31,r=rand()&31;
	return ((((p+q+r)*b)>>a)==(p+q+r)/9);
}
main()
{
	srand(time(NULL));
    int i,j,k=1000000,x,s[9],y;
    y=0;
    while(k--)
    {
        for(i=0;i<9;i++)s[i]=rand()&31;
        j=(s[0]+s[1]+s[2]+1)/3;
        j+=(s[3]+s[4]+s[5]+1)/3;
        j+=(s[6]+s[7]+s[8]+1)/3;
        for(i=x=0;i<9;i++)
            x+=s[i];
        if(j/3!=x/9)
        {
            y++;
        }
    }
    printf("%d\n",y);
	/*for(i=2;i<10;i++)
	{
	 	j=(1<<i)/9;
		k=1000000;
		while(k-- && test(i,j));
		if(k<0)printf("%d/%d\n",j,1<<i);
		j++;
		k=1000000;
		while(k-- && test(i,j));
		if(k<0)printf("%d/%d\n",j,1<<i);
	}*/
}
