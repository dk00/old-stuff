#include<stdio.h>

int n1,n2;
int change [8][4] ={ { +1 , +0 , +0 , +0 },
{ -1 , +0 , +0 , +0 },
{ +0 , +1 , +0 , +0 },
{ +0 , -1 , +0 , +0 },
{ +0 , +0 , +1 , +0 },
{ +0 , +0 , -1 , +0 },
{ +0 , +0 , +0 , +1 },
{ +0 , +0 , +0 , -1 } };
int q[10000];
int c[10000];
int f[10000];
int t=0,b=0;

int turn ( int num, int dir )
{
num = num + dir;
if( num > 9 ) num = 0;
if( num < 0 ) num = 9;
return num;
}


int push(int num, int cur)
{

int i ;

if(num== n2)
{

printf("%d\n",cur-1);
return 1;

}

for(i=0;i<t;i++)
if( q[i] == num )
return 0;

c[t]=cur;
q[t]=num;
t++;
return 0;
}

int add(int num,int cur)
{
int i;
int a1,a2 = (num /1000) % 10;
int b1,b2 = (num /100) % 10;
int c1,c2 = (num /10) % 10;
int d1,d2 = (num /1) % 10;

for(i = 0; i < 8; i++ )
{
a1 = turn ( a2 ,change[i][0] );
b1 = turn ( b2 ,change[i][1] );
c1 = turn ( c2 ,change[i][2] );
d1 = turn ( d2 ,change[i][3] );

if(f[a1*1000+b1*100+c1*10+d1] == 0)
if(push(a1*1000+b1*100+c1*10+d1, cur+1))
return 1;
}
return 0;
}


int main()
{
int ntest,i,j,done;
int temp,temp1,fb;

scanf("%d",&ntest);
while( ntest > 0)
{
ntest--;
n1=0;n2=0;
temp =0;
temp1 =0;
fb =0;
for(i=0;i<10000;i++)
{
q[i]=0;
f[i]=0;
c[i]=0;
}
for(i=0;i<4;i++)
{
scanf("%d",&temp);
n1 = n1*10 + temp;
}
for(i=0;i<4;i++)
{
scanf("%d",&temp);
n2 = n2*10 + temp;
}
scanf("%d",&fb);
for(i=0;i<fb;i++)
{
temp1 =0;
for(j=0;j<4;j++)
{
scanf("%d",&temp);
temp1 = temp1 * 10 + temp;
}
f[temp1]=1;
}

t = 0;
done = 0;

if( f[n2] )
{
printf("-1");
done = 1;
}

push(n1,1);
while(( b < t ) && ( done==0))
{
if(add( q[b], c[b]))
done = 1;
b++;
}
if(done == 0)
printf("-1\n");
}
return 0;
}
