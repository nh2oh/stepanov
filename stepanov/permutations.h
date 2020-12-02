#pragma once
#include <iterator>  // std::iterator_traits
#include <algorithm>  // std::count

//
// Notes on Programming 2018 (Alexander Stepanov)
// Chapter 17 "Lecture 17.  Permutation Algorithms"
//
//

namespace nop {

template<typename I0, typename I1>  // I0, I1 model forward iterator
bool is_permutation(I0 beg0, I0 end0, I1 beg1, I1 end1) {
	I0 curr0 = beg0;
	while (curr != end0) {
		if (std::count(beg0,end0,*curr0) != std::count(beg1,end1,*curr0)) {
			return false;
		}
		++curr0;
	}

	I1 curr1 = beg1;
	while (curr1 != end1) {
		if (std::count(beg1,end1,*curr1) != std::count(beg0,end0,*curr1)) {
			return false;
		}
		++curr1;
	}

	return true;
}



template <typename I, typename A>  // I models fwd iterator, A models action on I
void do_cycle(I it, A a) {
	I next = it;
	a(next);
	if (next == i) { return; }

	// UNDERLYING_TYPE(VALUE_TYPE(I)) tmp;
	// move_raw(deref(i), tmp);
	typename std::iterator_traits<I>::value_type tmp;
	tmp = *it;
	
	I first = it;
	do {
		//move_raw(deref(next), deref(first));
		*next = *first;
		first = next;
		a(next);
	} while (next != it);

	//move_raw(tmp, deref(first));
	*first = tmp;
}








};  // namespace nop

