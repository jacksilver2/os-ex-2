//
// Implementations for uthreads.h functions
//
#include "ThreadManager.h"
#include <vector>
#include <queue>

int uthread_init(int quantum_usecs)
{

	return 0;
}

int uthread_spawn(void (*f)(void))
{
	return 0;
}

int uthread_terminate(int tid)
{
	return 0;
}

int uthread_block(int tid)
{
	return 0;
}

int uthread_resume(int tid)
{
	return 0;
}

int uthread_sync(int tid)
{
	return 0;
}

int uthread_get_tid()
{
	return 0;
}

int uthread_get_total_quantums()
{
	return 0;
}

int uthread_get_quantums(int tid)
{
	return 0;
}
