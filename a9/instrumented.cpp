#include "instrumented.h"
#include <iostream>
#include <cassert>



void a9::test_instrumented() {
	a9::instrumented<int> a(5);
	a9::instrumented<int> b(7);

	/*assert(a != b);
	assert(!(a==b));*/


	std::cout << "a:  " << a << "\tb:  " << b << std::endl;
	if (a == b) {
		std::cout << "a==b" << std::endl;
	}
	if (a != b) {
		std::cout << "a!=b" << std::endl;
	}


}









