//
// Created by idob on 5/4/2018.
//

#include "ThreadList.h"
#include <iostream>
#include <cassert>

/**
 * creates an empty list
 */
ThreadList::ThreadList():_head{nullptr}{}

/**
 * adds node to end of list
 */
void ThreadList::push(ThreadNode *node)
{
	// make sure input is valid
	assert(node != nullptr);
	assert(node->next == nullptr && node->prev == nullptr);
	if (_head == nullptr)
	{
		_head = node;
		_tail = node;
	}
	else
	{
		_tail->next = node;
		node->prev = _tail;
		_tail = node;
	}
}

/**
	 * removes node at the top of the list
	 * @return pointer to removed node
	 */
ThreadNode* ThreadList::pop()
{
	ThreadNode *node;
	assert(_head != nullptr && _tail != nullptr);
	if (_head == _tail)
	{
		node = _head;
		_head = nullptr;
		_tail = nullptr;
	}
	else
	{
		node = _head;
		_head = node->next;
		node->next = nullptr;
		_head->prev = nullptr;
	}
	return node;
}

/**
 * removes given node from list (and set it's next, prev, list accordingly)
 * assumes given node is in the list
 */
void ThreadList::remove(ThreadNode* node)
{
	assert(node != nullptr);
	if (_head == _tail && _head == node)
	{
		_head = nullptr;
		_tail = nullptr;
	}
	else if(_head == node)
	{
		_head = node->next;
		node->next = nullptr;
	}
	else if(_tail == node)
	{
		_tail = node->prev;
		node->prev = nullptr;
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		node->next = nullptr;
		node->prev = nullptr;
	}
}

/**
 * concatenate nodes of given list to end of self and leave it empty
 */
void ThreadList::concat(ThreadList &other)
{
	if (other._head != nullptr)
	{
		if (_head == nullptr)
		{
			_head = other._head;
			_tail = other._tail;
			other._head = nullptr;
			other._tail = nullptr;
		} else
		{
			_tail->next = other._head;
			other._head->prev = _tail;
			_tail = other._tail;
			other._head = nullptr;
			other._tail = nullptr;
		}
	}
}

/**
 * prints contents
 */
void ThreadList::print()
{
	ThreadNode *node = _head;
	int i = 0;
	std::cout << "head: " << (u_long)_head << std::endl;
	if (_head == nullptr)
	{
		std::cout << "\tempty" << std::endl;
	}
	while (node != nullptr)
	{
		std::cout << "\ti: " << i << std::endl;
		std::cout << "\tid: " << node->id << std::endl;
		std::cout << "\tprev: " << (u_long)node->prev << std::endl;
		std::cout << "\taddr: " << (u_long)node << std::endl;
		std::cout << "\tnext: " << (u_long)node->next << std::endl;
		std::cout << "\t----------------------------------------------" << std::endl;
		node = node->next;
		i++;
	}
	std::cout << "tail: " << (u_long)_tail << std::endl;
}

//NEEDE TO GENERATE THIS !!
ThreadNode::ThreadNode(int i, void *pVoid, void *pVoid1)
{

}
