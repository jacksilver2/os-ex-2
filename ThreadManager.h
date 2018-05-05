//
// Created by Shmuel on 02-May-18.
//

#ifndef EX2_TMANAGER_H
#define EX2_TMANAGER_H


#include "ID_handler.h"
#include "Thread.h"
#include "ThreadList.h"



class ThreadManager
{
public: //for now all is public
	int total_quantums;
	int running;
	ID_handler id_handler;
	vector<Thread> v;
	ThreadList ready_list;

	/**
	 * adds a new thread to the threads_vector
	 */
	int add_thread(void (*f)());

	/**
	 * makes the scheduling decision
	 */
	int schedule();

	/**
	 * sets up the thread manager
	 * @param quantum_usecs_usecs length of quantum (as passed down by the uthreads_init
	 * function)
	 * @return
	 */
	int setup(int quantum_usecs);

};


#endif //EX2_TMANAGER_H
