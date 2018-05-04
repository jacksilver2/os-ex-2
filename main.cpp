
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <iostream>
#include "ID_handler.h"
#include "utils.h"
#include "state.h"
#include "ThreadList.h"


using std::cout;
using std::endl;



int id_test()
{
	cout << "Welcome to the ID_handler test" << endl;
	ID_handler h;
	h.get_id();
	h.get_id();
	h.get_id();
	h.recycle_id(3);
	h.recycle_id(1);
	h.print_ids_pq();
	h.get_id();
	h.get_id();
	h.get_id();
	h.get_id();
	h.recycle_id(4);
	h.recycle_id(5);
	h.recycle_id(1);
	h.print_ids_pq();
	h.get_id();
	h.recycle_id(2);
	h.recycle_id(1);
	h.recycle_id(3);
	h.print_ids_pq();
	h.get_id();
	h.get_id();
	h.get_id();
	h.get_id();
	h.get_id();
	h.get_id();
	h.print_ids_pq();
	return 0;
}

int thread_list_test()
{
	ThreadList list1{};
	ThreadList list2{};
	ThreadNode node1{5, nullptr, nullptr};
	ThreadNode node2{7, nullptr, nullptr};
	ThreadNode node3{9, nullptr, nullptr};
	ThreadNode node4{11, nullptr, nullptr};
	list1.push(&node1);
	list1.push(&node2);
	list2.push(&node3);
	list2.push(&node4);
	list1.print();
	list2.print();
	std::cout << "concat" << std::endl;
	list1.concat(list2);
	list1.print();
	list2.print();
	std::cout << "concat2" << std::endl;
	list2.concat(list1);
	list1.print();
	list2.print();
	std::cout << "concat3" << std::endl;
	list2.concat(list1);
	list1.print();
	list2.print();
	return 0;
}

int main()
{
	id_test();
	//thread_list_test();
	State s = READY;

}

