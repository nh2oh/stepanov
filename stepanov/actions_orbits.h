#pragma once
#include <utility>  // std::pair


//
// Notes on Programming 2018 (Alexander Stepanov)
// Chapter 12 "Lecture 12.  Actions and their Orbits"
//
//


namespace nop {

// Default for total actions
template<typename T, typename A>
bool is_defined(const T& x, const A& a) {
	return true;
}

// Function object for the action "increment"
template<typename T>
struct increment {
	void operator()(T& x) const {
		++x;
	}
};

// Generalized advance to apply an action n times
template<typename T, typename A, typename I>
void advance(T& x, I n, A a) {
	while (I(0) < n) {
		assert(nop::is_defined(x,a));
		a(x);
		--n;
	}
}

template<typename T, typename A, typename I>
I guarded_advance(T& x, I n, A a) {
	while (I(0) < n) {
		if (!nop::is_defined(x,a)) {
			break;
		}
		nop::increment<T>()(x);
		--n;
	}
	return n;
}

// STL-like advance() defined in terms of the more general version above
template<typename T, typename I>
void advance(T& x, I n) {
	nop::advance(x, n, nop::increment<T>());
}



//-----------------------------------------------------------------------------
// the "successor" funtions are functional versions of the advance() family that
// do not modify the arguments
template<typename T, typename A, typename I>
T successor_n(T x, I n, A a) {
	nop::advance(x,n,a);
	return x;
}

template<typename T, typename A, typename I>
std::pair<T,I> guarded_successor_n(T x, I n, A a) {
	n = nop::guarded_advance(x, n, nop::increment<T>());
	return std::pair<T,I> {x,n};
}

// More specialized version that uses nop::increment<T> when no action is
// specified
template<typename T, typename I>
T successor_n(T x, I n) {
	return nop::successor_n(x, n, nop::increment<T>());
}

template<typename T>
T successor(T x) {
	nop::increment<T>()(x);
	return x;
}

template<typename T







};  // namespace nop

