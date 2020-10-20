#include "generic_algs.h"
#include <cmath>
#include <cassert>

int nop::gcd_positive_subtractive_recursive(int a, int b) {
	assert(0 < a && 0 < b);
	if (a == b) {
		return a;
	}
	if (a < b) {
		return nop::gcd_positive_subtractive_recursive(a,b-a);
	}
	return nop::gcd_positive_subtractive_recursive(a-b,b);
}





