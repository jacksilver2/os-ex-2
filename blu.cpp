/*
 * sigsetjmp/siglongjmp demo program.
 * Hebrew University OS course.
 * Author: OS, os@cs.huji.ac.il
 */

#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

#define SECOND 1000000
#define STACK_SIZE 4096

char stack1[STACK_SIZE];
char stack2[STACK_SIZE];
char stack3[STACK_SIZE];

sigjmp_buf env[4];

#ifdef __x86_64__
/* code for 64 bit Intel arch */

typedef unsigned long address_t;
#define JB_SP 6
#define JB_PC 7

/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr)
{
    address_t ret;
    asm volatile("xor    %%fs:0x30,%0\n"
		"rol    $0x11,%0\n"
                 : "=g" (ret)
                 : "0" (addr));
    return ret;
}

#else
/* code for 32 bit Intel arch */

typedef unsigned int address_t;
#define JB_SP 4
#define JB_PC 5 

/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr)
{
    address_t ret;
    asm volatile("xor    %%gs:0x18,%0\n"
		"rol    $0x9,%0\n"
                 : "=g" (ret)
                 : "0" (addr));
    return ret;
}

#endif

void switchThreads(int k)
{
  static int currentThread = 3;

  int ret_val = sigsetjmp(env[currentThread],1);
  printf("SWITCH: ret_val=%d\n", ret_val); 
  if (ret_val == 1) {
      return;
  }
printf("currentThread=%d\n",currentThread);
  currentThread = (currentThread+1)%4;
  siglongjmp(env[currentThread],1);
}

void f(void)
{
  unsigned long i = 0;
  while(1){
    ++i;
	if (i%100000000==0){
    printf("in f (%lu)\n",i);
}
    }
 //   usleep(SECOND);
}

void g(void)
{
  unsigned long i = 0;
  while(1){
    ++i;
	if (i%100000000==0){
    printf("in g (%lu)\n",i);
}
    }
 //   usleep(SECOND);
}

void h(void)
{
  unsigned long i = 0;
  while(1){
    ++i;
	if (i%100000000==0){
    printf("in h (%lu)\n",i);
}
    }
 //   usleep(SECOND);
}

void setup(void)
{
  address_t sp, pc;
  struct sigaction sa;
  struct itimerval timer;
  sp = (address_t)stack1 + STACK_SIZE - sizeof(address_t);
  pc = (address_t)f;
  sigsetjmp(env[0], 1);
  (env[0]->__jmpbuf)[JB_SP] = translate_address(sp);
  (env[0]->__jmpbuf)[JB_PC] = translate_address(pc);
  sigemptyset(&env[0]->__saved_mask);     

  sp = (address_t)stack2 + STACK_SIZE - sizeof(address_t);
  pc = (address_t)g;
  sigsetjmp(env[1], 1);
  (env[1]->__jmpbuf)[JB_SP] = translate_address(sp);
  (env[1]->__jmpbuf)[JB_PC] = translate_address(pc);
  sigemptyset(&env[1]->__saved_mask);

  sp = (address_t)stack3 + STACK_SIZE - sizeof(address_t);
  pc = (address_t)h;
  sigsetjmp(env[2], 1);
  (env[2]->__jmpbuf)[JB_SP] = translate_address(sp);
  (env[2]->__jmpbuf)[JB_PC] = translate_address(pc);
  sigemptyset(&env[2]->__saved_mask);

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	// Install timer_handler as the signal handler for SIGVTALRM.
	sa.sa_handler = &switchThreads;
	if (sigaction(SIGVTALRM, &sa,NULL) < 0) {
		printf("sigaction error.");
	}
	// Configure the timer to expire after 1 sec... */
	timer.it_value.tv_sec = 1;		// first time interval, seconds part
	timer.it_value.tv_usec = 0;		// first time interval, microseconds part

	// configure the timer to expire every 3 sec after that.
	timer.it_interval.tv_sec = 3;	// following time intervals, seconds part
	timer.it_interval.tv_usec = 0;	// following time intervals, microseconds part

	// Start a virtual timer. It counts down whenever this process is executing.
	if (setitimer (ITIMER_VIRTUAL, &timer, NULL)) {
		printf("setitimer error.");
	}

}

int main(void)
{
  unsigned long i = 0;
  setup();		
//  siglongjmp(env[0], 1);

  while(1){
    ++i;
	if (i%100000000==0){
    printf("in main (%lu)\n",i);
}
    }

  return 0;
}


