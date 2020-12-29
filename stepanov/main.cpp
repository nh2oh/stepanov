#include <iostream>
#include <vector>
#include <cstdio>
#include "fvector_int.h"
#include "function_objects.h"
#include "iterators.h"
#include "reverse.h"
#include "stable_partition.h"
#include "reduction.h"

int main() {

	//nop::benchmark_less_abs();

	//nop::fvector_int_copy_assign();

	//nop::test_adjacent_swap_copy();

	//nop::test_stable_partition_with_buffer();

	nop::test_stable_partition_slow_iterative();

	return 0;
}
