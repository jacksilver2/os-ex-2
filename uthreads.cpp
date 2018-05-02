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

int cnt; //counter for allocated ids

vector<int> state_vec;

queue<int> ready_q;

vector<queue<int> > sync_vec; //sync_vector
//index of vector cell represents a tid and the queue in that cell
//represents its dependencies

priority_queue<int>ids_pq;

//? blocked_list ?

int get_new_id(){
	if (ids_pq.empty())
	{
		return cnt++;
	}
	else
	{
		int ret = ids_pq.top();
		ids_pq.pop();
		return ret;
	}

}
int release_id(int tid){
	ids_pq.push(tid);
	return 0;
}

int uthread_init(int quantum_usecs)
{
	//initialization of structures
	cnt = 1;
	state_vec[MAIN_THREAD] = READY; // do we need this?
	ready_q.push(MAIN_THREAD);
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
