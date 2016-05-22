#include<cmath>
#include<cstdio>
template<class num> class complex
{
public:
    num real,imag;
    complex();
    complex(num a,num b){real=a,imag=b;}

};
complex<double> exp(complex<double> a)
{
    complex<double> tmp;
    tmp=
}

using namespace std;

const int N=65536*2,D=100;
const double pi=3.14159265358979323846;
complex<double> root[N+1];

void initFFT(){
	for(int i=0;i<N;i++)
		root[i]=exp(complex<double>(0,2*pi*(i*1.0/N)));
	root[N]=complex<double>(1,0);
}

complex<double> tmpc[N];

void FFT(complex<double> *num, int dim, bool flag){ /*dim=2^k>=4*/
	int i;
	if(dim==4){
		complex<double> I=complex<double>(0,1);
		for(i=0;i<4;i++)
			tmpc[i]=num[2*i];
		if(flag==false)I=(0,-1);
		num[0]=tmpc[0]+tmpc[1]+tmpc[2]+tmpc[3];
		num[1]=tmpc[0]+tmpc[1]*I-tmpc[2]-tmpc[3]*I;
		num[2]=tmpc[0]-tmpc[1]+tmpc[2]-tmpc[3];
		num[3]=tmpc[0]-tmpc[1]*I-tmpc[2]+tmpc[3]*I;
		return;
	}
	for(i=0;i<dim/2;i++){
		tmpc[i]=num[2*i];
		tmpc[dim/2+i]=num[2*i+1];
	}
	memcpy(num,tmpc,dim*sizeof(complex<double>));
	FFT(num,dim/2,flag);
	FFT(num+dim/2,dim/2,flag);
	memcpy(tmpc,num,dim*sizeof(complex<double>));
	int div=N/dim;
	if(flag==true){
		for(i=0;i<dim/2;i++)
			tmpc[dim/2+i]*=root[i*div];
	}
	else{
		for(i=0;i<dim/2;i++)
			tmpc[dim/2+i]*=root[N-i*div]/2;
	}
	for(i=0;i<dim/2;i++){
		num[i]=tmpc[i]+tmpc[dim/2+i];
		num[dim/2+i]=tmpc[i]-tmpc[dim/2+i];
	}
}

struct big{
	int dim;
	complex<double> num[2*N];
	big operator *=(big b){
		int i,j;
		if(this->dim>b.dim)this->dim=b.dim;
		for(i=4;i<dim;i*=2);
		for(;dim<i;dim++)
			num[dim]=complex<double>(0,0);
		FFT(num,dim,true);
		FFT(b.num,dim,true);
		for(i=0;i<dim;i++)
			num[i]*=b.num[i];
		FFT(num,dim,false);
		num[dim]=0;
		for(i=0;i<dim;i++)
		{
			int tmp=num[i].real;
			if(tmp<0 || abs(num[i].imag)>1e-2)
			{
				puts("bug");
				scanf("%d",&i);
			}
			num[i+1]+=complex<double>(tmp/100,0);
			num[i]=complex<double>(tmp%100,0);
		}
		if(num[dim].real>.5)dim++;
		while(dim && num[dim-1].real<.5)
			dim--;
	}
	big print()
	{
		int tmp;
		for(int i=dim-1;i>=0;i--)
		{
			tmp=num[i].real;
			printf("%d",tmp);
		}
	}
	big operator=(const char a[])
	{
		int i;
		for(i=0;a[i];i++);
		i--;
		for(dim=0;i>=0;i-=2,dim--)
			num[dim].real=a[i]+(i?a[i-1]*10:0);
	}
};

big a,b;
char s1[100000],s2[100000];
int main()
{
	initFFT();
	while(scanf("%s %s",s1,s2)==2)
	{
		a=s1,b=s2;
		a*=b;
		a.print();
		puts("");
	}
}
