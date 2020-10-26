#include "instrumented.h"
#include "count_operations.h"
#include <cstddef>
#include <iostream>
#include <vector>


int main() {
	//a9::test_instrumented();

	//a9::count_operations(2,1024*1024+1,a9::std_sort_functor());
	//a9::count_operations(2,8*1024*1024+1,a9::swap_each_pair_functor());
	//a9::count_operations(2,8*1024*1024+1,a9::std_reverse_functor());
	auto f = a9::std_count_functor(a9::instrumented(1024.0*1024.0));
	a9::count_operations(2,8*1024*1024+1,f);

	return 0;
}
