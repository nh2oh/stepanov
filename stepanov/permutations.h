#pragma once
#include <iterator>  // std::iterator_traits
#include <algorithm>  // std::count
#include <list>

//
// Notes on Programming 2018 (Alexander Stepanov)
// Chapter 17 "Lecture 17.  Permutation Algorithms"
//
//

namespace nop {

//bool yay() {
//	std::list<int> a;
//	std::list<int> b;
//	return std::is_permutation(a.begin(),a.end(),b.begin(),b.end());
//}

template<typename I0, typename I1>  // I0, I1 model forward iterator
bool is_permutation_p140(I0 beg0, I0 end0, I1 beg1, I1 end1) {
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


template<typename I1, typename I2>  // I1, I2 model fwd iterator
bool is_permutation(I1 beg1, I1 end1, I2 beg2, I2 end2) {
	I1 tmp1 = beg1;
	I2 tmp2 = beg2;
	while ((tmp1 != end1) && (tmp2 != end2)) {
		++tmp1;
		++tmp2;
	}
	if ((tmp1 != end1) || (tmp2 != end2)) {
		return false;  // sequences are different length
		// Note if statement this repeats the test made in the loop header and could
		// be better optimized.  
	}

	// Sequences are the same length
	tmp1 = beg1;
	while (tmp1 != end1) {
		if (std::count(beg1,end1,*tmp1) != std::count(beg2,end2,*tmp1)) {
			return false;
		}
		++tmp1;
	}
	return true;
}



template <typename I, typename A>  // I models fwd iterator, A models action on I
void do_cycle(I it, A a) {
	I next = it;
	a(next);
	if (next == it) { return; }

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

