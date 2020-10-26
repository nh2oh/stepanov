#include "instrumented.h"
#include "count_operations.h"
#include <cstddef>
#include <iostream>
#include <vector>


int main() {
	//a9::test_instrumented();

	a9::count_operations(2,2*1024*1024+1,a9::std_sort_functor());

	return 0;
}
