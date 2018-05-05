//
// Created by idob on 5/4/2018.
//

#ifndef T2_THREADMANAGER_H
#define T2_THREADMANAGER_H

#include "Thread.h"
#include "ID_handler.h"
#include <vector>
using namespace std;
class ThreadManager
{
public:
	/**
	 * makes data structures adds main thread and sets timer like in bla.cpp
	 */
	ThreadManager(time_t quantumLength);

	/**
	 * adds thread to vector and adds it's node to ready list
	 * this is essentially spawn
	 * @param f function for thread
	 */
	void addThread(void (*f)(void));

	/**
	 * stops running thread moves it to end of ready list and saves.
	 * takes thread from top of ready list and runs it.
	 */
	void schedule();

	/**
	 * if state is ready then block and remove from ready list, if running block and schedule.
	 * if blocked/synced
	 * handle errors as in pdf
	 * @return 0, on success. -1 on error
	 */
	int block(int id);

	/**
	 * if state is blocked add to ready and resume thread.
	 * handle errors as in pdf
	 * @return 0, on success. -1 on error
	 */
	int resume(int id);

	/**
	 * assert state is running
	 * sync thread, add it to sync list of id and schedule
	 * handle errors as in pdf
	 * @return 0, on success. -1 on error
	 */
	int sync(int id);

	/**
	 * assert not synced meaning that the thread being terminated is not synced!!!! we are supposed to suport it but it's problematic at the moment
	 * if state is ready then remove from ready list, if running schedule.
	 * before scheduling(if needed) get sync list of id and concat it to ready list
	 * teminate thread and only then schedule(if needed)
	 * handle errors as in pdf
	 * @return 0, on success. -1 on error
	 */
	int terminate(int id);

	//frees everything. DON'T WRITE THIS YET
	~ThreadManager();

private:
	int _runningId;
	vector<Thread> _threads;
	quant_time_t _totalQuantums;
	ID_handler _idHandler;// not realy int. put what you wrote
	ThreadList _readyList;

	void pushToReadyList(int tid);

	bool idIsValid(int tid);
};
#endif //T2_THREADMANAGER_H
