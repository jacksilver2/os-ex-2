
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <iostream>
#include "utils.h"
#include "uthreads.h"
using std::cout;
using std::endl;
int main()
{
	cout << "Welcome to the EX2 tester" << endl;
	cout << SOMECONST << endl;
	uthread_init(3);
}

