//
// Created by idob on 5/4/2018.
//

#ifndef T2_THREAD_H
#define T2_THREAD_H

#include <setjmp.h>
#include "ThreadList.h"


typedef unsigned long quant_time_t;

typedef enum e_state
{
	RUNNING = 0,
	READY 	= 1,
	BLOCKED	= 2,
	NOT_SET	= 4
} state_t;

class Thread
{
public:
	/**
	 * create new thread
	 * @param id the id the thread should have
	 * @param f pointer to the function the thread should run
	 */
	Thread(int id, void (*f)(void));

	/**
	 * sets an empty thread (eather new or terminated)
	 * @param id the id the thread should have
	 * @param f pointer to the function the thread should run
	 * @return
	 */
	void setThread(int id, void (*f)(void));

	/**
	 * @return state of thread
	 */
	state_t getState()
	{
		return _state;
	}
	/**
	 * @return node of thread
	 */
	ThreadNode* getNode()
	{
		return _node;
	}

	/**
	 * @return node of thread
	 */
	ThreadList& getSyncList()
	{
		return _syncList;
	}

	/**
	 * runs thread
	 */
	void run();

	/**
	 * saves the threads current environment
	 * @return -1 if just saved, otherwise if came by jump returns id of thread we came from
	 */
	int save();

	/**
	 * blocks the thread
	 */
	void block();

	/**
	 * resumes blocked thread
	 */
	void resume();

	/**
	 * block thread and set syncedTo to id
	 */
	void sync(int id);

	/**
	 * adds node to sync list
	 * @param node the pointer to the node to add
	 */
	void addToSyncList(ThreadNode* node);

	/**
	 * changes state to terminated and frees internal memory
	 */
	void terminate();
    
    /**
     * @return true if sync to other thread
    */
	bool isSynced();

	/**
	 * @return id of thread sync to, -1 if not synced
	*/
	int getSyncedTo();

private:
	sigjmp_buf _env;
	state_t _state;
	ThreadNode *_node;
	ThreadList _syncList;
	char *_stackPtr;
	int _id;
	quant_time_t _quantumsPassed;
	int _syncedTo;
};
#endif //T2_THREAD_H