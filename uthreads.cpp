//
// Implementations for uthreads.h functions
//

/**Defs and consts**/
#define MAIN_THREAD 0
#define READY 100
#define RUNNING 200
#define BLOCKED 300
#define NONEXISTENT 400
#define SYNCED 500

/**Data structures**/

using namespace std;

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
