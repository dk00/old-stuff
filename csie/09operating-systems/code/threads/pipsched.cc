#include "main.h"
#include "sem.h"
class trigger:public CallBackObj{
    Thread *t;
public:
    trigger(Thread *t):t(t){}
    void CallBack(){
	kernel->scheduler->ReadyToRun(t);
        if(t->prio < kernel->currentThread->prio)
	    kernel->interrupt->YieldOnReturn();
    }
};
struct PIPTestData{
    int n,tst,tlen;
    int *type,*start,*len;
    PIPTestData(int n,int tst,int tlen):n(n),tst(tst),tlen(tlen){
	type=new int[n];
	start=new int[n];
	len=new int[n];
    }
    ~PIPTestData(){
	delete[] type;
	delete[] start;
	delete[] len;
    }
};
Sem **sem;
static void PIPTest(PIPTestData *dat)
{
    int &now=kernel->stats->totalTicks;
    Thread *&me=kernel->currentThread;
    if(now<dat->tst){
	trigger tg(me);
        kernel->interrupt->Schedule(&tg,dat->tst,TimerInt);
	IntStatus oldLevel=kernel->interrupt->SetLevel(IntOff);
	kernel->currentThread->Sleep(false);
	kernel->interrupt->SetLevel(oldLevel);
    }
    for(int t=0;t<dat->tlen;++t){
	for(int i=0;i<dat->n;i++){
	    if(dat->start[i] >= 0 && dat->start[i] == t){
		sem[dat->type[i]]->lock();
		cout << " thread"<<me->tid<<" locks "<<
		    sem[dat->type[i]]->name << " at "<<now<< '\n';
		dat->start[i]=-1;
	    }
	    if(dat->start[i]<0){
		if(!--dat->len[i]){
		    sem[dat->type[i]]->unlock();
		    cout << " thread"<<me->tid<<" unlocks " <<
			sem[dat->type[i]]->name<<" at "<<now+1<< '\n';
		}
	    }
	}

	kernel->interrupt->OneTick();

	if(!kernel->scheduler->readyList->IsEmpty()){
	  Thread* t= kernel->scheduler->readyList->Front();
	  if(t!=NULL && t->getPrio() < kernel->currentThread->getPrio()){
	    kernel->currentThread->Yield();
	  }
	}
    }
}
void Thread::pipSched(const char filename[])
{
    FILE *fp=fopen(filename,"r");
    int i,j,n,m;
    fscanf(fp,"%d",&m);
    sem=new Sem*[m];
    for(i=0;i<m;i++){
	fscanf(fp,"%d",&j);
	char name[20];
	sprintf(name,"Sem%c",'A'+i);
	sem[i]=new Sem(name,j);
    }
    fscanf(fp,"%d",&n);
    int *tid=new int[n];
    PIPTestData **test=new PIPTestData *[n];
    for(i=0;i<n;i++){
	int prio,start,len,nr;
	fscanf(fp,"%d %d %d %d",&prio,&start,&len,&nr);
	test[i]=new PIPTestData(nr,start,len);
	for(j=0;j<nr;j++)
	    fscanf(fp,"%d %d %d",
		&test[i]->type[j],&test[i]->start[j],&test[i]->len[j]);
	tid[i]=kernel->createThread((void *)PIPTest,test[i]);
	kernel->setPriority(tid[i],prio);
    }
    for(i=0;i<n;i++){
	kernel->currentThread->Join(tid[i]);
	delete test[i];
    }
    for(i=0;i<m;i++)
	delete sem[i];
    delete[] tid;
    delete[] test;
    delete[] sem;
}

