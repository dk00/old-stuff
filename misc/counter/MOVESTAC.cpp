#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct stack
{
	char index;
	long double value;
	struct stack *next;
	struct stack *last;
};

struct stackmodel{
	struct stack *start,*q;
	int empty;
};

stack *out(stackmodel *hp)
{
        stack *tempx=(stack*)malloc(sizeof(stack));
	if(hp->empty!=1)
	{
	hp->q=hp->q->last;
	if(hp->q==hp->start)
	{
		hp->empty=1;
	}
	tempx->index=hp->q->index;
        tempx->value=hp->q->value;
        return tempx;
	free(hp->q);
	}
	else
	{
        tempx->value=0;
        tempx->index=0;
	return tempx;
	}
}
void add(stackmodel *hp,long double index,char temp)
{
	hp->q->index=temp;
	hp->q->value=index;
	hp->q->next=(stack*)malloc(sizeof(stack));
	hp->q->next->last=hp->q;
	hp->q=hp->q->next;
	hp->empty=0;
}

stackmodel *createstack()
{
	stackmodel *hp;
        hp=(stackmodel*)malloc(sizeof(stackmodel));
	hp->q=(stack*)malloc(sizeof(stack));
	hp->start=hp->q;
	hp->empty=1;
        hp->q->value=0;
        hp->q->index=0;
	return hp;
}


