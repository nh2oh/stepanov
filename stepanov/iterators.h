#pragma once
#include <utility>  // std::pair
#include <functional> // std::equal_to



//
// Notes on Programming 2018 (Alexander Stepanov)
// Chapter 13 "Lecture 13.  Iterators"
//
//

namespace nop {

// Binary predicate P
template<typename I, typename T, typename P>
I find(I beg, I end, const T& a, P p) {
	while (beg!=end && !p(*beg,a)) {
		++beg;
	}
	return beg;
}

template<typename I, typename T>
I find(I beg, I end, const T& a) {
	return nop::find(beg,end,a,std::equal_to<T>());
}


template<typename I, typename P>
I find_if(I beg, I end, P p) {
	while (beg!=end && !p(*beg)) {
		++beg;
	}
	return beg;
}


template<typename I, typename N, typename T, typename P>
std::pair<I,N> find_n(I beg, N n, const T& a, P p) {
	while (n != N(0) && !p(*beg,a)) {
		--n;
		++beg;
	}
	return {beg,n};
}



template<typename I, typename T, typename P>
I find_unguarded(I beg, const T& a, P p) {
	while (!p(*beg,a)) {
		++beg;
	}
	return beg;
}

};  // namespace nop



