/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 

#include "kernel.h"




void SysHalt()
{
    kernel->interrupt->Halt();
}


int SysAdd(int op1, int op2)
{
    return op1 + op2;
}

inline void SysSimplePrint()
{
    int i,d,tmp,tmp1;
    i=kernel->machine->ReadRegister(4);
    d=kernel->machine->ReadRegister(5);
    for(;kernel->machine->ReadMem(i,1,&tmp) && tmp;i++){
	kernel->machine->ReadMem(i+1,1,&tmp1);
	if(tmp=='%' && tmp1=='d'){
	    cout << d;
	    i+=2;
	    break;
	}
	else
	    cout <<(char)tmp;
    }
    for(;kernel->machine->ReadMem(i,1,&tmp) && tmp;i++)
	cout <<(char)tmp;
}

static void verySimpleThread(int tid){
    cout<<"This is thread "<<tid<<" (prio="<<kernel->tidTable[tid]->prio<<")"<<endl;
}

inline void SysCreateThreads(){
    Thread *thread = new Thread("new thread");
    thread->tid=kernel->idDistribution(thread);
    thread->prio=kernel->currentThread->prio+1;
    kernel->machine->WriteRegister(2,thread->tid);
    if(thread->tid<0){
	delete thread;
	return;
    }
    thread->Fork((VoidFunctionPtr) verySimpleThread, (void *) thread->tid);
}

inline void SysSetPriority(){
    int tid = kernel->machine->ReadRegister(4);
    int prio = kernel->machine->ReadRegister(5);
    if(tid<0 || tid>=kernel->tidTable.size()){
	cerr << "Invalid tid: " << tid << endl;
	return;
    }
    kernel->setPriority(tid,prio);
}

#endif /* ! __USERPROG_KSYSCALL_H__ */
