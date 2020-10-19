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


// struct binary_compose takes F(x,y), G(x), H(x) and returns a function object
// that does F(G(x), H(y))
template<typename F, typename G, typename H>
struct binary_compose {
	using arg_g_t = typename G::arg_t;
	using arg_h_t = typename H::arg_t;
	using result_t = typename F::result_t;

	F f_;
	G g_;
	H h_;

	binary_compose(const F& f, const G& g, const H& h) : f_(f), g_(g), h_(h) {}

	result_type operator()(const arg_g_t& x, const arg_h_t& y) const {
		return f_(g_(x),h_(y));
	}

};


// struct f_transpose takes f(x,y) and returns a function object that does f(y,x)
template<typename F>
struct f_transpose {
	using arg_t = F::arg_t;
	using result_t = F::result_t;

	F f_;

	f_transpose(const F& f) : f_(f) {}

	result_t operator()(const arg_t& x, const arg_t& y) const {
		return f_(y,x);
	}
};



};  // namespace nop




