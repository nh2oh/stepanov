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


template<typename T>
T abs(const T& x) {
	if (x < T(0)) {
		return -x;
	}
	return x;
}

template<typename T>
struct less_distance {
	T a_;

	less_distance(T a) : a_(a) {}

	bool operator()(const T& lhs, const T& rhs) const {
		return nop::abs(lhs - a_) < nop::abs(rhs - a_);
	}
};

//-----------------------------------------------------------------------------


template<typename F>
struct binder2nd {
	using result_t = typename F::result_t;
	using arg_1_t = typename F::arg_1_t;
	using arg_2_t = typename F::arg_2_t;

	F fun_;
	arg_2_t a2_;

	binder2nd(const F& fun, arg_2_t a2) : fun_(fun), a2_(a2) {}

	result_t operator()(const arg_1_t& a1) const {
		return fun_(a1,a2_);
	}
};

};  // namespace nop




