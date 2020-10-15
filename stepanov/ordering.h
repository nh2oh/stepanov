#pragma once
#include <functional>  // std::less



//
// Notes on Programming 2018 (Alexander Stepanov)
// Chapter 7 "Lecture 7.  Ordering and related algorithms"
//
//

namespace nop {

template<typename T, typename R>
T& min(T& x, T& y, R r) {
	if (r(y,x)) {  // "y < x"  not "x < y"
		return x;
	}
	return y;
}

template<typename T, typename R>
const T& min(const T& x, const T& y, R r) {
	if (r(y,x)) {  // "y < x"  not "x < y"
		return x;
	}
	return y;
}

template<typename T>
T& min(T& x, T& y) {
	return nop::min(x,y,std::less<T>{});
}

template <typename T>
const T& min(const T& x, const T& y) {
	return nop::min(x,y,std::less<T>{});
}













};




