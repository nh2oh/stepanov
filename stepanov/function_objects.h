#pragma once
#include <cmath>  // std::abs()


//
// Notes on Programming 2018 (Alexander Stepanov)
// Chapter 9 "Lecture 9.  Function Objects"
//
//


namespace nop {

bool less_abs_fun(double lhs, double rhs);

struct less_abs {
	bool operator()(double lhs, double rhs) const;
};

void benchmark_less_abs();


};  // namespace nop




