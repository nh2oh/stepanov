#include "dummy_static_lib.h"
#include <cstdint>


void swapyay(double& a, double& b) {
    double tmp = a;
    a = b;
    b = tmp;
	return;
}

void swapyay(std::uint64_t& a, std::uint64_t& b) {
    std::uint64_t tmp = a;
    a = b;
    b = tmp;
	return;
}

void swapyay(std::int64_t& a, std::int64_t& b) {
    std::int64_t tmp = a;
    a = b;
    b = tmp;
	return;
}



const std::uint64_t& minyay(const std::uint64_t& lhs, const std::uint64_t& rhs) {
    if (rhs < lhs) {
        return rhs;
    }
    return lhs;
}




