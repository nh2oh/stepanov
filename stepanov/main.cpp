#include <iostream>
#include <vector>
#include <cstdio>
#include "fvector_int.h"
#include "function_objects.h"
#include "iterators.h"
#include "reverse.h"

int main() {

	//nop::benchmark_less_abs();

	//nop::fvector_int_copy_assign();

	nop::test_adjacent_swap_copy();

	return 0;
}
