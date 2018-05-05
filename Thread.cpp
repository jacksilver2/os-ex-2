//
// Created by idob on 5/4/2018.
//

#include "Thread.h"

#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <cassert>

#define SECOND 1000000
#define STACK_SIZE 4096

#ifdef __x86_64__
/* code for 64 bit Intel arch */

typedef unsigned long address_t;
#define JB_SP 6
#define JB_PC 7

/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr)
{
	address_t ret;
	asm volatile("xor    %%fs:0x30,%0\n"
			"rol    $0x11,%0\n"
	: "=g" (ret)
	: "0" (addr));
	return ret;
}

#else
/* code for 32 bit Intel arch */

typedef unsigned int address_t;
#define JB_SP 4
#define JB_PC 5

/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr)
{
    address_t ret;
    asm volatile("xor    %%gs:0x18,%0\n"
		"rol    $0x9,%0\n"
                 : "=g" (ret)
                 : "0" (addr));
    return ret;
}

#endif

void Thread::setThread(int id, void (*f)(void))
{
	address_t sp, pc;
	_id = id;
	_node = new ThreadNode{id, nullptr, nullptr};
	//todo ThreadNode is a struct. Should be class?
	if (id)
	{
		_state = READY;
		_quantumsPassed = 1;
		_stackPtr = new char[STACK_SIZE];
		sp = (address_t)_stackPtr + STACK_SIZE - sizeof(address_t);
		pc = (address_t)f;
		sigsetjmp(_env, 1);
		(_env->__jmpbuf)[JB_SP] = translate_address(sp);
		(_env->__jmpbuf)[JB_PC] = translate_address(pc);
		sigemptyset(&_env->__saved_mask);
	}
	else
	{
		_state = READY;
		_quantumsPassed = 0;
		_stackPtr = nullptr;
		sigsetjmp(_env, 1);
	}
}

/**
 * runs thread
 */
void Thread::run()
{
	_state = RUNNING;
	_quantumsPassed++;
	siglongjmp(_env, _id + 1);
}

/**
	 * saves the threads current environment
	 * @return -1 if just saved, otherwise if came by jump returns id of thread we came from
	 */
int Thread::save()
{
	return sigsetjmp(_env, 1) - 1;
}

/**
 * blocks the thread
 */
void Thread::block()
{
	assert(_state != NOT_SET);
	if (_state == RUNNING || _state == READY || _state == BLOCKED)
	{
		_state = BLOCKED;
	}
}

/**
 * resumes blocked thread
 */
void Thread::resume()
{
	assert(_state != NOT_SET);
	if (_state == BLOCKED)
	{
		_state = READY;
	}
}

/**
 * move thread to sync state
 */
void Thread::sync(int id)
{
	assert(_state == RUNNING);
	_state = SYNCED;
	_waitingToSyncWith = id;
}

/**
 * adds node to sync list
 * @param node the pointer to the node to add
 */
void Thread::addToSyncList(ThreadNode* node)
{
	_syncList.push(node);
}

/**
 * changes state to terminated and frees internal memory
 */
void Thread::terminate()
{
	assert(_state != NOT_SET);
	_state = NOT_SET;
	_quantumsPassed = 0;
	delete _stackPtr;
	_stackPtr = nullptr;
	delete _node;
	_node = nullptr;
	delete _env;
	_env = nullptr;
}

bool Thread::isSyncing()
{
	return _waitingToSyncWith > 0;
}

void Thread::setSyncingFlag(bool flag)
{
	_waitingToSyncWith = flag;
}
