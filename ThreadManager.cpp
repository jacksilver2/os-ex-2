//
// Created by Shmuel on 02-May-18.
//

#include "tmanager.h"

int ThreadManager::add_thread(void (*f)())
{
	//add threads node to ready list
	int id;
	id = id_handler.get_id();
	if (v.size() == id)
	{
		v.push_back({id,f}); //creates new Thread and add to vs' end
	}
	else
	{
		v[id].newThread(id,f); // pours new content to existing thread associated with id
	}
	return 0;
}

int ThreadManager::schedule()
{
	if ("ready_list is not empty") //requires implementation for .empty() function
	{
		ThreadNode* node = ready_list.pop();
		total_quantums++;
		running = node->id;
		v[node->id].run();
	}
	else
	{
		total_quantums++; //perhaps?
	}
	return 0;
}

int ThreadManager::setup(int quantum_usecs)
{
	//set timers

	return 0;
}
