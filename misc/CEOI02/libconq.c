#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "libconq.h"

//#define __DEBUG__

static int game_N=0;
static int st[MAX_N+1];

static int lib_usage = 0;
static char lib_txt[1024];

static void lib_error(int code, char *s)
{
    FILE *f;
    printf("%s\n",s);
    exit(code);
}

void start(int *N, int *stairs)
{
    FILE *f;
    int i;

    if (lib_usage!=0) lib_error(1,"start() called too many times");
    lib_usage++;

    if ((f=fopen("libconq.dat","r"))==NULL)
    {
	scanf("%d",N);
	for (i=1;i<=(*N);i++) scanf("%d",&stairs[i]);
    }
    else
    {
	fscanf(f,"%d ",N);
	for (i=1;i<=(*N);i++) fscanf(f,"%d ",&stairs[i]);
	fclose(f);
    }
  
    game_N=(*N);
    for (i=1;i<=(*N);i++) st[i]=stairs[i];
}

static int decide(int *a)
{
    int i,diff,n,ret=1;
    int va[MAX_N+1],vb[MAX_N+1];
    
    for (i=1;i<=game_N;i++) va[i]=a[i];
    for (i=1;i<=game_N;i++) vb[i]=st[i]-a[i];

    /* normalize va and vb */
    for (i=game_N;i>1;i--)
    {
	n=va[i]/2;
	va[i]-=2*n;
	va[i-1]+=n;

	n=vb[i]/2;
	vb[i]-=2*n;
	vb[i-1]+=n;
    }

#ifdef __DEBUG__
    printf("va: "); for (i=game_N;i>0;i--) printf("%d ",va[i]); printf("\n");
    printf("vb: "); for (i=game_N;i>0;i--) printf("%d ",vb[i]); printf("  --> choosing");
#endif

    /* choose va or vb -- whichever has larger value */
    diff=0;
    for (i=1;i<=game_N;i++)
    {
	if (va[i]!=vb[i]) { diff=i; break; }
    }

    /* if both va and vb >= 1/2, choose the one which left first soldier
       farther from stair No. 1  */
    if ( (va[2]+va[1]>=1) && (vb[2]+vb[1]>=1))
    {
	for (i=1;i<=game_N;i++)
	  if (st[i]) {
	    if (a[i]) ret=2; else ret=1;
	    break;
	  }
    } 
    else
    {
	if (diff)
	{
	    if (va[diff]==0) ret=1;  /* i.e. vb has bigger value */
	    else ret=2;
	} else ret=1;
    }

#ifdef __DEBUG__
    printf(" %d\n",ret);
#endif
    
    return ret;
}

int step(int *subset)
{
    int choice,i,wrong,cnt;

    if (lib_usage==0) lib_error(1,"call start() first!");
    lib_usage++;

    /* check if a is a valid subset */
    wrong=0;
    for (i=1;i<=game_N;i++)
    {
	if ((subset[i]<0) || (subset[i]>st[i])) wrong=i;
	if (wrong) break;
    }
  
    if (wrong!=0)
    {
	sprintf(lib_txt,"wrong number of soldiers on stair %d: %d requested, %d available",wrong,subset[i],st[i]);
	lib_error(1,lib_txt);
    }
  
    /* decide */
    choice=decide(subset);
    
    /* choice 1: move subset one stair up, discard the rest */
    if (choice==1)
    {
	for (i=1;i<=game_N;i++) st[i]=subset[i];
	for (i=1;i<=game_N;i++) st[i-1]=st[i];
	st[game_N]=0;
    }
    else  /* choice 2: discard subset, move complement one stair up */
    {
	for (i=1;i<=game_N;i++) st[i]-=subset[i];
	for (i=1;i<=game_N;i++) st[i-1]=st[i];
	st[game_N]=0;
    }
  
    /* check if there are any soldiers left */
    /* check if there is any soldier at position 1 */
    cnt=0;
    for (i=1;i<=game_N;i++) cnt+=(!!st[i]);
  
    if (cnt==0)
    {
#ifdef __DEBUG__
        sprintf(lib_txt,"You lost! (last choice=%d)",choice);
#else
        sprintf(lib_txt,"You lost!");
#endif
	lib_error(0,lib_txt);
    }
  
    if (st[1])
    {
#ifdef __DEBUG__
	sprintf(lib_txt,"You won! (choice=%d)",choice);
#else
	sprintf(lib_txt,"You won!");
#endif
	lib_error(0,lib_txt);
    }

    return choice;
}

