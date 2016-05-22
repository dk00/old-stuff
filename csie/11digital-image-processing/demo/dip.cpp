#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define THREAD_NUM 16
#define W 5000
#define H 5000
#define L 3
char method_name[5][20]={"","input","normalization","gray","save"};

pthread_t tid[THREAD_NUM+5];
struct data{int st,ed,method;}table[THREAD_NUM+5];

double C=0.7;
int h,w;

IplImage *Image1;
double temp[H][W][L];
int min_b,max_b,min_r,max_r,min_g,max_g;

unsigned char Blue[H][W];
unsigned char Green[H][W];
unsigned char Red[H][W];
double Gray[H][W];
double c_map[H*W];

double ori_gra[H][W],aft_gra[H][W];

void local_normalization(int st,int ed,unsigned char ImageLayerEXT[H][W],int min_l,int max_l,int flag);
void *run_thread(void* ptr);

void input(int st,int ed);
void gray1(int st,int ed);
void muilt_thread(int m);
void gray2();
void save_image(int st,int ed);
void c_set();

int main(int argc,char *argv[])
{
	if(argc!=3)
	{   
		puts("usage: dip intputImage outputImage");  
		return 0;
	}   
	Image1 = cvLoadImage(argv[1],1);
	h=Image1->height;
	w=Image1->width;

	fprintf(stderr,"[imagesize]: hight%d width%d\n",h,w);
	
	muilt_thread(1);		//input
	muilt_thread(2);		//gray1
	muilt_thread(3);		//normalization
	gray2();
	c_set();

	muilt_thread(4);		//save_image
	cvSaveImage(argv[2],Image1);
}

void c_set(){
	double maxx=0;
	int i,j,k;
	for(i=k=1;i<Image1->height-1;i++)
		for(j=1;j<Image1->width-1;j++)
		{
			if(aft_gra[i][j]>maxx)
				maxx=aft_gra[i][j];
			k++;
		}
	for(i=k=0;i<Image1->height;i++)
		for(j=0;j<Image1->width;j++)
		{
			c_map[k]=(aft_gra[i][j]+(maxx-aft_gra[i][j])*C)/maxx;
			k++;
		}
}

void gray1(int st,int ed)
{
	int i,j,gr,gc;
	for(i=1;i<Image1->height-1;i++)
	{
		for(j=1;j<Image1->width-1;j++)
		{
			gc=((Gray[i-1][j+1]+Gray[i][j+1]+Gray[i+1][j+1])-(Gray[i-1][j-1]+Gray[i][j-1]+Gray[i+1][j-1]))/4.0;
			gr=((Gray[i-1][j-1]+Gray[i-1][j]+Gray[i-1][j+1])-(Gray[i+1][j-1]+Gray[i+1][j]+Gray[i+1][j+1]))/4.0;
			ori_gra[i][j]=sqrt(gc*gc+gr*gr);
		}
	}
}

void gray2()
{
	int i,j,gr,gc;
	for(i=0;i<Image1->height;i++)
		for(j=0;j<Image1->width;j++)
			Gray[i][j]=(temp[i][j][0]+temp[i][j][1]+temp[i][j][2])/3.0;

	for(i=1;i<Image1->height-1;i++)
	{
		for(j=1;j<Image1->width-1;j++)
		{
			gc=((Gray[i-1][j+1]+Gray[i][j+1]+Gray[i+1][j+1])-(Gray[i-1][j-1]+Gray[i][j-1]+Gray[i+1][j-1]))/4.0;
			gr=((Gray[i-1][j-1]+Gray[i-1][j]+Gray[i-1][j+1])-(Gray[i+1][j-1]+Gray[i+1][j]+Gray[i+1][j+1]))/4.0;
			aft_gra[i][j]=sqrt(gc*gc+gr*gr);
		}
	}
}


void input(int st,int ed)
{
	int i,j,subj;
	min_b=500,min_g=500,min_r=500,max_b=0,max_g=0,max_r=0;
	for(i=st;i<=ed;i++)
	{
		for(j=0;j<Image1->widthStep;j=j+3)
		{
			subj=j/3;
			Blue[i][subj]=Image1->imageData[i*Image1->widthStep+j];
			Green[i][subj]=Image1->imageData[i*Image1->widthStep+j+1];
			Red[i][subj]=Image1->imageData[i*Image1->widthStep+j+2];
			Gray[i][subj]=(((double)Blue[i][subj]+(double)Green[i][subj]+(double)Red[i][subj])/3.0);

			if((int)Blue[i][subj]<min_b)  min_b=(int)Blue[i][subj];
			if((int)Green[i][subj]<min_g) min_g=(int)Green[i][subj];
			if((int)Red[i][subj]<min_r)   min_r=(int)Red[i][subj];

			if((int)Blue[i][subj]>max_b)  max_b=(int)Blue[i][subj];
			if((int)Green[i][subj]>max_g) max_g=(int)Green[i][subj];
			if((int)Red[i][subj]>max_r)   max_r=(int)Red[i][subj];

		}
	}
}

void save_image(int st,int ed)
{
	int i,j,k;
	for(i=st;i<=ed;i++)
		for(j=0;j<w;j++)
		{ 
			k=i*w+j;
			Image1->imageData[i*Image1->width*3+j*3]=(unsigned char)(pow(temp[i][j][0],c_map[k])*(double)Blue[i][j]);
			Image1->imageData[i*Image1->width*3+j*3+1]=(unsigned char)(pow(temp[i][j][1],c_map[k])*(double)Green[i][j]);
			Image1->imageData[i*Image1->width*3+j*3+2]=(unsigned char)(pow(temp[i][j][2],c_map[k])*(double)Red[i][j]);
		} 
}

void local_normalization(int st,int ed,unsigned char ImageLayerEXT[H][W],int min_l,int max_l,int flag)
{
	int i,j,p,q;

	double d,k,v_bimg,v_R;
	double min,max;
	double tmp;

	for(i=st;i<=ed;i++)
	{
		for(j=1;j<Image1->width-1;j++)
		{
			d=((double)ImageLayerEXT[i][j]-min_l)*255/(max_l-min_l);
			v_bimg = (temp[i][j][flag]/(double)max_l);
			k=0.03096*v_bimg + 5.737;
			v_R=pow(2,k);
			min=500,max=-2.3;

			for(p=-1;p<2;p++)
			{
				for(q=-1;q<2;q++)
				{
					tmp= ((double)ImageLayerEXT[i+p][j+q]-min_l)*255/(max_l-min_l);
					if(tmp<min)
						min=tmp;
					if(tmp>max)
						max=tmp; 
				}        
			}
			double tttt= 1/(d+1);
			double img_new=255*(d-0.5*min)/(max-0.5*min+v_R*(tttt-(1/(double)max_l))+0.1/v_R);
			double r=img_new/(d+0.001);

			if(r>255)   
				temp[i][j][flag]=255;
			else if(r<0) 
				temp[i][j][flag]=0;
			else
				temp[i][j][flag]=r; 
		}
	} 
}

void *run_thread(void* ptr)
{
	data *v = (data*) ptr;
	if(v->method==1){
		input(v->st,v->ed);	
	}
	else if(v->method==2){
		local_normalization(v->st,v->ed,Blue,min_b,max_b,0);
		local_normalization(v->st,v->ed,Green,min_g,max_g,1);
		local_normalization(v->st,v->ed,Red,min_r,max_r,2);
	}
	else if(v->method==3){
		gray1(v->st,v->ed);
	}
	else if(v->method==4){
		save_image(v->st,v->ed);
	}
	pthread_exit(0);
}

void muilt_thread(int m)
{
	fprintf(stderr,"method[%s] run\n",method_name[m]);
	int i, split=h/THREAD_NUM, index=0, cnt=0;
	for(i=0;i<THREAD_NUM; i++, index+=split )
	{   
		table[cnt] = (data){index,index+split,m}; 
		pthread_create( &tid[cnt] , NULL , run_thread , table + cnt );
		cnt++;
	}
	table[cnt] = (data){index,h-1,m}; 
	pthread_create( &tid[cnt] , NULL , run_thread , table + cnt );
	cnt++;

	for(i=0;i<cnt;i++)
		pthread_join(tid[i],NULL);

	fprintf(stderr,"method[%s] done\n",method_name[m]);
}
