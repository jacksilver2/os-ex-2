//
// Created by Shmuel on 02-May-18.
//

#ifndef EX2_TMANAGER_H
#define EX2_TMANAGER_H


#include "ID_handler.h"
#include "thread.h"

class ThreadManager
{
public:
	int total_quantums;
	int running;
	ID_handler id_handler;
	vector<Thread> v;

	/**
	 * adds a new thread to the threads_vector
	 */
	int add_thread(void (*f)());

	/**
	 * makes the scheduling decision
	 */
	int schedule();

};


#endif //EX2_TMANAGER_H
