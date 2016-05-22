#include"sem.h"
Sem::Sem(char* debugName, int initialValue)
{
    strcpy(name,debugName);
    value = initialValue;
    queue = new priority_queue<Thread*,vector<Thread*>,cmp>;
    running.clear();
}

Sem::~Sem()
{
    delete queue;
}

//----------------------------------------------------------------------
// Semaphore::P
// 	Wait until semaphore value > 0, then decrement.  Checking the
//	value and decrementing must be done atomically, so we
//	need to disable interrupts before checking the value.
//
//	Note that Thread::Sleep assumes that interrupts are disabled
//	when it is called.
//----------------------------------------------------------------------

void
Sem::lock()
{
    Interrupt *interrupt = kernel->interrupt;
    Thread *currentThread = kernel->currentThread;
    
    // disable interrupts
    IntStatus oldLevel = interrupt->SetLevel(IntOff);	
    
    while (value == 0) { 		// semaphore not available
	cout<<" thread"<<currentThread->tid<<" is blocked at "<<
	    kernel->stats->totalTicks<<" due to "<<name<<endl;
	queue->push(currentThread);	// so go to sleep
	for(int i=0;i<running.size();++i){
	  kernel->scheduler->readyList->Remove(running[i]);
	  kernel->scheduler->readyList->Insert(running[i]);
	}
	currentThread->Sleep(FALSE);
    } 
    value--; 			// semaphore available, consume its value
    running.push_back(currentThread);
    currentThread->lock.push_back(this);
   
    // re-enable interrupts
    (void) interrupt->SetLevel(oldLevel);	
}

//----------------------------------------------------------------------
// Semaphore::V
// 	Increment semaphore value, waking up a waiter if necessary.
//	As with P(), this operation must be atomic, so we need to disable
//	interrupts.  Scheduler::ReadyToRun() assumes that interrupts
//	are disabled when it is called.
//----------------------------------------------------------------------

void
Sem::unlock()
{
    Interrupt *interrupt = kernel->interrupt;
    Thread *currentThread = kernel->currentThread;
    // disable interrupts
    IntStatus oldLevel = interrupt->SetLevel(IntOff);	
    for(vector<Thread*>::iterator i=running.begin();i!=running.end();++i)
      if( (*i) == currentThread ){
	running.erase(i);
	break;
      }
    
    if (!queue->empty()) {  // make thread ready
	kernel->scheduler->ReadyToRun(queue->top());
	queue->pop();
	for(int i=0;i<running.size();++i){
	  kernel->scheduler->readyList->Remove(running[i]);
	  kernel->scheduler->readyList->Insert(running[i]);
	}
    }
    value++;
    currentThread->lock.remove(this);
    // re-enable interrupts
    (void) interrupt->SetLevel(oldLevel);
}
int 
Sem::getPrio(){
  if(queue->empty())
    return -1;
  else
    return (queue->top())->prio;
}
