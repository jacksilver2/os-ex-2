//
// Created by idob on 5/4/2018.
//
#include "ThreadManager.h"
#include <iostream>
#include <cassert>

/**
 *
 * @return 0 if thread associated with id is in threadList
 */
bool ThreadManager::idIsValid(int tid)
{
	//todo fix validity logic in id handler
	return tid < _threads.size();
}

/**
 * pushes thread with id tid to readyList
 * @return 0 on success -1 on failure
 */
void ThreadManager::pushToReadyList(int tid)
{
	assert(idIsValid(tid));
	_readyList.push(_threads[tid].getNode());

}

/**
 * adds thread to vector and adds it's node to ready list
 * this is essentially spawn
 * @param f function for thread
 */
void ThreadManager::addThread(void (*f)(void))
{
	//todo : is this it?
	//get id. if it's new then create new thread and place in id.
	//if it's not new then "override"(?) content of thread
	//that is currently associated with id.

	assert(f != nullptr); //todo: need this?

	int id;
	id = _idHandler.get_id();
	if (id > _threads.size())
	{
		//create new thread and push to _threads
	}
	else
	{
		_threads[id].setThread(id, f);
	}

}

/**
 * stops running thread moves it to end of ready list and saves.
 * takes thread from top of ready list and runs it.
 */
void ThreadManager::schedule()
{
	ThreadNode *node;
	int id;
	_readyList.push(_threads[_runningId].getNode());
	std::cout << "saving thread " << _runningId << std::endl;
	if ((id = _threads[_runningId].save()) == -1) //nice
	{
		node = _readyList.pop();
		std::cout << "running thread " << node->id << std::endl;
		_runningId = node->id;
		_threads[node->id].run();
	}
	std::cout << "Just came back from thread " << id << std::endl;
}

int ThreadManager::block(int id)
{
	assert(id > 0);
	if (id == 0)
	{
		//todo add error print: "Attempting to block main thread"
		return -1;
	}
	if (!idIsValid(id))
	{
		//todo add error: "Attempting to block non-existent id"
		return -1;
	}
	Thread cur_thread = _threads[id];
	state_t state = cur_thread.getState();

	if (state == NOT_SET)
	{
		//todo add error: "Attempting to block non-existent thread"
		return -1;
	}
	if (state == READY)
	{
		cur_thread.block();
		_readyList.remove(cur_thread.getNode());
		return 0;
	}
	if (state == RUNNING) //"if a state blocks itself a shc. decision is made"
	{
		cur_thread.block();
		schedule();
		return 0;
	}
	if (state == BLOCKED || state == SYNCED)
	{
		//all good. not an error according to pdf.
	}
	return 0;
}

int ThreadManager::resume(int id)
{
	if (!idIsValid(id))
	{
		//todo add error: "Attempting to resume non-existent id"
		return -1;
	}
	assert(id < 0);
	Thread cur_thread = _threads[id];
	state_t state = cur_thread.getState();
	if (state == BLOCKED)
	{
		if (!cur_thread.isSyncing())
		{
			//pushToReadyList(id);
			assert(idIsValid(id));
			_readyList.push(_threads[id].getNode());
		}
		//needed to make sure that this thread is not synced
		//added "_waitingToSyncWith" field

	}
	if (state == RUNNING || state == READY)
	{
		//has no effect according to pdf.
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
	if (!idIsValid(id))
	{
		//todo add error: "Attempting to sync non-existent id"
		return -1;
	}
	if (id == 0)
	{
		//todo add error: "Attampting to sync with main thread
		return -1;
	}
	if (id == _runningId)
	{
		//todo add error: "Attampting to sync with self
		return -1;
	}
	Thread runningThread = _threads[_runningId];
	Thread threadToSyncTo = _threads[id];
	assert(runningThread.getState() == RUNNING);
	runningThread.sync(id);
	threadToSyncTo.addToSyncList(runningThread.getNode());
	runningThread.block();
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
	return 0;
}

