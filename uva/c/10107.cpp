#include<stdio.h>
#include<stdlib.h>
struct link{
	int n;
	link *left;
	link *right;
};
void main(){
link s;
link *i,*m,*newp,*tmp;
int n,move=0,l;
m=&s;
m->left=NULL;
m->right=NULL;
scanf("%d",&n);
m->n=n;
printf("%d\n",n);
for(l=2;1;l++){
	scanf("%d",&n);
	if(n<=0)
		break;
	newp=(link *)malloc(sizeof(link));
	for(i=m;;){
		if(i->left==NULL && i->n>=n){	// left top
			move--;
			i->left=newp;
			newp->right=i;
			newp->left=NULL;
			break;
		}
		else if(i->right==NULL && i->n<=n){	// right top
			move++;
			i->right=newp;
			newp->left=i;
			newp->right=NULL;
			break;
		}
		else if(i->n>n && (i->left)->n<=n){	//put in left
			move--;
			newp->right=i;
			newp->left=i->left;
			(i->left)->right=newp; // *(*i.left).right=newp
			i->left=newp;
			break;
		}
		else if(i->n<=n && (i->right)->n>n){	//put in right
			move++;
			newp->left=i;
			newp->right=i->right;
			(i->left)->right=newp;
			i->right=newp;
			break;
		}
		if(i->n>n && i->left!=NULL)	// move left
			i=i->left;
		else if(i->n<=n && i->right!=NULL)	// move right
			i=i->right;
	}
	newp->n=n;
	if(l%2==0){	//2n
		if(move>0)
			printf("%d\n",(m->n+(m->right)->n)/2);
		else
			printf("%d\n",(m->n+(m->left)->n)/2);
	}
	else{	//2n+1
		if(move>0)
			m=m->right;
		else if(move<0)
			m=m->left;
		printf("%d\n",m->n);
		move=0;
	}
}
}