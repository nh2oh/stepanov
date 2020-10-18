#pragma once
#include <functional>  // std::less
#include <cassert>


//
// Notes on Programming 2018 (Alexander Stepanov)
// Chapter 7 "Lecture 7.  Ordering and related algorithms"
// Chapter 8 "Lecture 8.  Order selection of up to 5 objects"
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


template<typename T>
T& median_3_2(T& x1, T& x2, T& x3) {
	assert(x1 <= x2);
	// p. 65:  return x3 < x2 ? max(x1, x3) : x2;
	if (x1 < x3) {
		return nop::min(x2,x3);
	}
	return x3;
}

template<typename T>
const T& median_3_2(const T& x1, const T& x2, const T& x3) {
	assert(x1 <= x2);
	// p. 65:  return x3 < x2 ? max(x1, x3) : x2;
	if (x1 < x3) {
		return nop::min(x2,x3);
	}
	return x3;
}

template<typename T>
T& median_3(T& x1, T& x2, T& x3) {
	if (x1 <= x2) {
		return nop::median_3_2(x1,x2,x3);
	}
	return nop::median_3_2(x2,x1,x3);
}

template<typename T>
const T& median_3(const T& x1, const T& x2, const T& x3) {
	if (x1 <= x2) {
		return nop::median_3_2(x1,x2,x3);
	}
	return nop::median_3_2(x2,x1,x3);
}


template<typename T>
void sort_3(T& x1, T& x2, T& x3) {
	nop::swap(x2,nop::median_3(x1,x2,x3));
	nop::swap(nop::min(x1,x3));
}








};  // namespace nop




