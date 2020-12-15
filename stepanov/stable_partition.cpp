#include <vector>
#include <iostream>
#include "stable_partition.h"




void nop::test_stable_partition_with_buffer() {
	std::vector<int> t1 {9,1,2,3,4,5,6,7,8,6,9};
	std::vector<int> b1(t1.size(),0);

	for (const auto& e : t1) {
		std::cout << e << ' ';
	}
	std::cout << std::endl;

	auto m = nop::stable_partition_with_buffer(t1.begin(),t1.end(),b1.begin(),
		[](const int& x) -> bool {
			return ((x%2)==0);
		}
	);

	for (const auto& e : t1) {
		std::cout << e << ' ';
	}
	std::cout << std::endl;

}


