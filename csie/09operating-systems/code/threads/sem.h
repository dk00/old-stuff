#ifndef SEM_H
#define SEM_H
#include "thread.h"
#include "kernel.h"
#include "main.h"
#include <cstring>
#include <queue>
#include <vector>

struct cmp{
  bool operator()(Thread* a,Thread* b){
    return a->prio > b->prio;
  }
};

class Sem{
  public:
    Sem(char* debugName, int initialValue);	// set initial value
    ~Sem();   					// de-allocate semaphore
    
    void lock();	 	// these are the only operations on a semaphore
    void unlock();	 	// they are both *atomic*
    int getPrio();

    char name[20];        // useful for debugging
  private:
    int value;         // semaphore value, always >= 0
    vector<Thread*> running;
    priority_queue<Thread*,vector<Thread*>,cmp> *queue;
		  	// threads waiting in P() for the value to be > 0
};
#endif
