//
// Created by idob on 5/4/2018.
//
#include "ThreadManager.h"
#include <iostream>
#include <cassert>
#include <signal.h>
#include <sys/time.h>
#include <setjmp.h>
#include "ThreadManager.h"

/**
 * makes data structures adds main thread and sets timer
 */
int ThreadManager::setup(int quantumLength)
{
	if (quantumLength >= 0)
	{
		return -1;
	}
	_totalQuantums = 1;
	sigemptyset(&_sa.sa_mask);
	_sa.sa_flags = 0;
	// Install timer_handler as the signal handler for SIGVTALRM.
	_sa.sa_handler = &schedule;
	if (sigaction(SIGVTALRM, &_sa,NULL) < 0) {
		printf("sigaction error.");
	}
	_timer.it_value.tv_sec = quantumLength / 1000000;		// first time interval, seconds part
	_timer.it_value.tv_usec = quantumLength % 1000000;		// first time interval, microseconds part
	_timer.it_interval.tv_sec = quantumLength / 1000000;	// following time intervals, seconds part
	_timer.it_interval.tv_usec = quantumLength % 1000000;	// following time intervals, microseconds part

	// Start a virtual timer. It counts down whenever this process is executing.
	if (setitimer (ITIMER_VIRTUAL, &_timer, NULL)) {
		printf("setitimer error.");
	}
	return 0;
}

/**
 * adds thread to vector and adds it's node to ready list
 * this is essentially spawn
 * @param f function for thread
 */
void ThreadManager::addThread(void (*f)(void))
{
	int id;
	id = _idHandler.getId();
	if (id > _threads.size())
	{
		_threads.push_back({id, f});
	}
	else
	{
		_threads[id].setThread(id, f);
	}
	_readyList.push(_threads[id].getNode());
}

/**
 * stops running thread moves it to end of ready list and saves.
 * takes thread from top of ready list and runs it.
 */
void ThreadManager::schedule(int sig=0)
{
	ThreadNode *node;
	int id;
	_readyList.push(_threads[_runningId].getNode());
	std::cout << "saving thread " << _runningId << std::endl;
	if ((id = _threads[_runningId].save()) == -1)
	{
		node = _readyList.pop();
		std::cout << "running thread " << node->id << std::endl;
		_runningId = node->id;
		_threads[node->id].run();
	}
	std::cout << "Just came back from thread " << id << std::endl;
}

/**
 * if state is ready then block and remove from ready list, if running block and schedule.
 * if blocked/synced
 * handle errors as in pdf
 * @return 0, on success. -1 on error
 */
int ThreadManager::block(int id)
{
	if (id == 0)
	{
		std::cout << "atempting to block main thread" << id << std::endl;
		return -1;
	}
	if (id >= _threads.size() || id < 0 || _threads[id].getState() == NOT_SET)
	{
		std::cout << "Attempting to block non-existent id" << id << std::endl;
		return -1;
	}
	if (_threads[id].getState() == READY)
	{
		_threads[id].block();
		_readyList.remove(_threads[id].getNode());
		return 0;
	}
	if (_threads[id].getState() == RUNNING)
	{
		_threads[id].block();
		schedule();
		return 0;
	}
	return 0;
}

/**
 * if state is blocked add to ready and resume thread.
 * handle errors as in pdf
 * @return 0, on success. -1 on error
 */
int ThreadManager::resume(int id)
{
	if (id >= _threads.size() || id < 0 || _threads[id].getState() == NOT_SET)
	{
		std::cout << "Attempting to resume non-existent id" << id << std::endl;
		return -1;
	}
	if (_threads[id].getState() == BLOCKED)
	{
		if (!_threads[id].isSynced())
		{
			_readyList.push(_threads[id].getNode());
		}
	}
	return 0;
}

/**
 * assert state is running
 * sync thread, add it to sync list of id and schedule
 * handle errors as in pdf
 * @return 0, on success. -1 on error
 */
int ThreadManager::sync(int id)
{
	if (id >= _threads.size() || id < 0 || _threads[id].getState() == NOT_SET)
	{
		std::cout << "Attempting to sync non-existent id" << id << std::endl;
		return -1;
	}
	if (_runningId == 0)
	{
		std::cout << "main thread attempts to sync with another thread" << id << std::endl;
		return -1;
	}
	if (id == _runningId)
	{
		std::cout << "Attempting to sync with self" << id << std::endl;
		return -1;
	}
	Thread runningThread = _threads[_runningId];
	Thread threadToSyncTo = _threads[id];
	assert(_threads[_runningId].getState() == RUNNING);
	_threads[_runningId].sync(id);
	_threads[id].addToSyncList(runningThread.getNode());
	schedule();
	return 0;
}

/**
 * assert not synced meaning that the thread being terminated is not synced!!!! we are supposed to suport it but it's problematic at the moment
 * if state is ready then remove from ready list, if running schedule.
 * before scheduling(if needed) get sync list of id and concat it to ready list
 * teminate thread and only then schedule(if needed)
 * handle errors as in pdf
 * @return 0, on success. -1 on error
 */
int ThreadManager::terminate(int id)
{
	if (id >= _threads.size() || id < 0 || _threads[id].getState() == NOT_SET)
	{
		std::cout << "Attempting to terminate non-existent id" << id << std::endl;
		return -1;
	}
	if (id == 0)
	{
		std::cout << "terminate main thread" << std::endl;
		// TODO release memory first
		exit(0);
	}
	if (_threads[id].getState() == READY)
	{
		_readyList.remove(_threads[id].getNode());
	}
	if (_threads[id].isSynced())
	{
		int tmpId = _threads[id].getSyncedTo();
		assert(tmpId < _threads.size() || tmpId >= 0 && _threads[tmpId].getState() == NOT_SET);
		_threads[tmpId].getSyncList().remove(_threads[id].getNode());
	}
	std::cout << "terminate thread " << id << std::endl;
	_readyList.concat(_threads[id].getSyncList());
	_threads[id].terminate();
	_idHandler.recycleId(id);
	return 0;
}

/**
 * prints exisiting threads states and ready list
 */
void ThreadManager::print()
{
	std::cout << "total quanntums " << _totalQuantums << std::endl;
	std::cout << "running " << _runningId << std::endl;
	for (int i=0;i<_threads.size();++i)
	{
		if (_threads[i].getState() != NOT_SET)
		{
			std::cout << "thread " << i << "is" << _threads[i].getState();
			if (_threads[i].isSynced())
			{
				std::cout << " and synced to" << _threads[i].getSyncedTo();
			}
			std::cout << std::endl;
		}
	}
	_readyList.print();
}