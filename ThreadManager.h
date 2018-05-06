//
// Created by idob on 5/4/2018.
//

#ifndef T2_THREADMANAGER_H
#define T2_THREADMANAGER_H

#include "Thread.h"
#include "IdHandler.h"
#include <vector>
#include <signal.h>
#include <sys/time.h>
#include <setjmp.h>

class ThreadManager
{
public:
	/**
	 * dosn't do much
	 */
	ThreadManager(time_t quantumLength);

	/**
	 * makes data structures adds main thread and sets timer
	 */
	int setup(int quantumLength);

	/**

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
	void schedule(int sig);

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

	/**
	 * prints exisiting threads states and ready list
	 */
	void print();

private:
	int _runningId;
	std::vector<Thread> _threads;
	quant_time_t _totalQuantums;
	IdHandler _idHandler;
	ThreadList _readyList;
	struct sigaction _sa;
	struct itimerval _timer;
};
#endif //T2_THREADMANAGER_H
