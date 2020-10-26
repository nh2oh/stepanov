#include "instrumented.h"
#include <iostream>
#include <cassert>
#include <cstddef>
#include <algorithm>
#include <vector>
#include <string>

std::size_t a9::instrumented_base::counts[];

std::vector<std::string> a9::instrumented_base::op_names {"def_ctor","copy_ctor","copy_assign","dtor",
	"comp_eq","comp_lt"};


void a9::instrumented_base::initialize() {
	std::fill(counts, counts+num_ops, 0);
}

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









