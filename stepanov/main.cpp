#include <iostream>
#include <vector>
#include <cstdio>
#include "fvector_int.h"


int main() {

	nop::fvector_int_copy_assign();




	std::vector<int> v1(6);
	std::vector<int> v2(123);

	std::printf("v1:  size==%d; capacity==%d\n",v1.size(),v1.capacity());
	std::printf("v2:  size==%d; capacity==%d\n",v2.size(),v2.capacity());

	auto v3 = v2;
	std::vector<int> v4(v2);
	std::printf("v3:  size==%d; capacity==%d\n",v3.size(),v3.capacity());
	std::printf("v4:  size==%d; capacity==%d\n",v4.size(),v4.capacity());
	
	v2 = v1;
	std::printf("v2:  size==%d; capacity==%d\n",v2.size(),v2.capacity());

	

	//std::cout << "yay" << std::endl;

	return 0;
}
