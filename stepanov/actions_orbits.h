#pragma once
#include <utility>  // std::pair
#include <cstddef>  // std::size_t

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


//-----------------------------------------------------------------------------
// The "advance" family are actions that modify their arguments

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


//-----------------------------------------------------------------------------
// Distance

// count_type_traits<T>::type is a type big enough to hold all distinct 
// _values_ of T, not, for example, the max distance in memory that can 
// seperate two objects of T.  
template<typename T>
struct count_type_traits {
	using type = std::size_t;
};
template<>
struct count_type_traits<short> {
	using type = unsigned short;
};

// distance() does not count the distance in memory between two T's, it counts 
// the number of _values_ of T between the values first and last.  
template<typename T, typename A>
typename nop::count_type_traits<T>::type distance(T first, const T& last, A a) {
	typename nop::count_type_traits<T>::type n(0);
	while (first != last) {
		a(first);
		++n;
	}
	return n;
}









};  // namespace nop

