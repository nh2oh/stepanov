#include "reduction.h"
#include <vector>
#include <iostream>



void nop::test_stable_partition_slow_iterative(){
	std::vector<int> v {1,3,6,5,8,7,4,5,6,9,98,2,1,5,0,4};
	for (const auto &e : v) {
		std::cout << e << ", ";
	}
	std::cout << std::endl;

	auto p = nop::stable_partition_slow_iterative(v.begin(), v.end(), nop::is_even<int>());
	for (const auto &e : v) {
		std::cout << e << ", ";
	}
	std::cout << std::endl;

}












