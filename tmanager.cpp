//
// Created by Shmuel on 02-May-18.
//

#include "tmanager.h"

int ThreadManager::add_thread(void (*f)())
{
	int id;
	id = id_handler.get_id();
	if (v.size() == id)
	{
		v.push_back({id,f});
	}
	else
	{
		v[id].newThread(id,f);
	}
	return 0;
}

int ThreadManager::schedule()
{
	if (true)
	return 0;
}
