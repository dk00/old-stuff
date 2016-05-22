#include<queue>
#include<ctime>
#include<cstdio>
#include"bigint.h"
using namespace std;
typedef unsigned long long u64;
const u64 u64_max = 0xffffffffffffffffllu;
int Type;
struct Task {
  int id, run_time, period, remaining, deadline, ready, start;
  bool operator<(const Task& a) const {
    int i, j;
    if (!ready)
      return start > a.start;
    if (Type == 0)    // RMS
      i = period, j = a.period;
    else  // (Type == 1) EDF
      i = deadline, j = a.deadline;
    if (i != j) return i > j;
    return id > a.id;
  }
};
inline void PrintNanosec(bool diff = false) {
	static timespec prev;
  timespec tp;
  clock_gettime(CLOCK_REALTIME, &tp);
	if (diff)
		printf("%llu\n", (tp.tv_sec - prev.tv_sec)*1000000000llu 
			+ tp.tv_nsec - prev.tv_nsec);
	else
 		printf("%d%09d\n", tp.tv_sec, tp.tv_nsec);
	prev = tp;
}
u64 gcd(u64 a, u64 b) { //calculate greatest common divisor
  if(!a||!b)return a+b;
  while((a%=b)&&(b%=a));
  return a+b;
}
inline void SetNext(Task& t) {
  if (t.remaining <= 0) {
    t.start += t.period;
    t.remaining = t.run_time;
    t.ready = 0;
  }
  t.deadline = t.start + t.period - t.remaining;
}
void InitTaskSet(priority_queue<Task>& q, int& max_period, bigint& hyper) {
  max_period = 0;
  hyper = 1;
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    Task t;
    t.id = i + 1;
    scanf("%d %d", &t.run_time, &t.period);
    hyper *= t.period/gcd(t.period, hyper%t.period);
    t.start = 0;
    t.remaining = t.run_time;
    SetNext(t);
    t.ready = 1;    
    q.push(t);
    if (t.period > max_period)
      max_period = t.period;
  }
}

enum Event { Start = 0, End, Preempt, Resume };
int Display, Events;
inline void Output(int t, int id, Event e) {
  if (!Display) return;
  ++Events;
  static int prev_t = -1;
  if (t != prev_t) printf("%d", t);
  printf(" %d %d", id, e);
  prev_t = t;
}

main() {
  int C;
  scanf("%d", &C);
  while (C--) {
    PrintNanosec();
    int n, max_period, flag = 1;
    scanf("%d %d", &Type, &Display);
    priority_queue<Task> ready, waiting;
    bigint hyper;
    u64 now = 0, elapse = 0;
    InitTaskSet(ready, max_period, hyper);
    vector<Task> tmp;
    Task running;
    running.id = -1;
    while (elapse < hyper.s[0]) {
      Events = 0;
      if (running.id > 0 && running.remaining <= 0) { 
        Output(elapse, running.id, End);
        SetNext(running);           // current task is finished
        running.ready = 0;
        waiting.push(running);
        running.id = -1;
      }
      while (!waiting.empty() && now >= waiting.top().start) {
        Task t = waiting.top();     // move ready tasks to ready queue
        waiting.pop();
        t.ready = 1;
        ready.push(t);
      }
      if (!ready.empty()) {
        if (running.id < 0) {
          running = ready.top();    // start highest priority task
          ready.pop();
          Output(elapse, running.id, 
              running.remaining<running.run_time?Resume:Start);
        }
        else if (running < ready.top()) {
          SetNext(running);
          running.ready = 0;
          waiting.push(running);
          Output(elapse, running.id, running.remaining>0?Preempt:End);
          Output(elapse, ready.top().id, 
              ready.top().remaining<ready.top().run_time?Resume:Start);
          running = ready.top();    // switch to highest priority
          ready.pop();
        }
      }
      if (Events > 0) puts("");
      if (now > running.deadline) {
        flag = 0;   // missed deadline
        break;
      }
      if (!Display && ready.empty() && running.id < 0)
        break;      // Idle
      int leap = 1; // time before next event
      if (!waiting.empty() && (running.id < 0 || running < waiting.top()))
        leap = waiting.top().start - now;   // next waiting task ready
      else if (running.id >= 0)
        leap = running.remaining;
      if (running.id >= 0 && running.remaining < leap)
        leap = running.remaining;   // time before current task finish
      running.remaining -= leap;
      now += leap;
      elapse += leap;
    }
    if (flag) printf("%d %s\n", now, hyper.tostr());
    else printf("not schedulable\n");
    PrintNanosec(true);
  }
}

