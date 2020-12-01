#pragma once
#include <iterator>  // std::iter_swap(), std::iterator_traits
#include <utility> // std::pair
#include "actions_orbits.h"  // nop::advance()

//
// Notes on Programming 2018 (Alexander Stepanov)
// Chapter 18 "Lecture 18.  Reverse"
//
//

namespace nop {

template<typename I>  // I models forward iterator w/ modifiable ref type
void adjacent_swap(I beg, I end) {
	I next;
	while (true) {
		if (beg == end) { return; }
		next = beg;
		++next;
		if (next == end) { return; }
		std::iter_swap(beg,next);
		beg = next;
		++beg;
	}
}


template<typename I, typename O>
O adjacent_swap_copy(I beg, I end, O dest) {
	while (true) {
		if (beg == end) { return dest; }
		I next = beg;  ++next;
		if (next == end) { *dest++ = *beg;  return dest; }
		*dest++ = *next;
		*dest++ = *beg;
		beg = next;  ++beg;
	}
}

void test_adjacent_swap_copy();


//-----------------------------------------------------------

// Returns a pair of iterators corresponding to the range of elements that were
// not swapped.  Thus, for a range containing an odd number of elements, result.first
// is the middle element and result.second is one past the middle element.  For a 
// range containing an even number of elements, result.first == result.second.  
template<typename I>  // I models bidirectional iterator
std::pair<I,I> reverse(I beg, I end) {
	while (true) {
		if (beg == end) { return std::pair {beg, end}; }
		--end;
		if (beg == end) { return std::pair {beg, ++end}; }  // Note:  ++end
		std::iter_swap(beg,end);
		++beg;
	}
}

// Returns a pair of iterators corresponding to the range of elements that were
// not swapped.  Thus, for a range containing an odd number of elements, result.first
// is the middle element and result.second is one past the middle element.  For a 
// range containing an even number of elements, result.first == result.second.  
template<typename I, typename N>  // I models bidirectional iterator, N models integer
std::pair<I,I> reverse_n(I beg, I end, N n) {
	while (n > N(1)) {
		--end;
		std::iter_swap(beg,end);
		++beg;
		n -= 2;
	}
	return std::pair {beg,end};
}

// Copying versions of reverse ("4 useful variations")

template<typename I, typename O>  // I models bidirectional iterator, O models output iterator
O reverse_copy(I beg, I end, O dest) {
	while (beg != end) {
		--end;
		*dest = *end;
		++dest;
	}
}

// result.first points at the last item copied, result.second points one past the last
// item copied.  
template<typename I, typename N, typename O>  // I models bidirectional iterator, O models output iterator
std::pair<I,O> reverse_copy_n(I end, N n, O dest) {
	while (n > N(0)) {
		--end;
		*dest = *end;
		++dest;
		--n;
	}
	return std::pair {end,dest};
}

template<typename I, typename O>  // I models input iterator, O models bidirectional iterator
O copy_reverse(I beg, I end, O dest_end) {
	while (beg != end) {
		--dest_end;
		*dest_end = *beg;
		++beg;
	}
	return dest_end;
}

template<typename I, typename N, typename O>  // I models input iterator, O models bidirectional iterator
std::pair<I,O> copy_reverse_n(I beg, N n, O dest_end) {
	while (n > N(0)) {
		--dest_end;
		*dest_end = *beg;
		++beg;
		--n;
	}
	return std::pair {beg, dest_end};
}

// TODO:  test me
// TODO:  bffr arg should point to the front of the buffer
template<typename I, typename B>  // I models forward iterator, B models bidirectional iterator
void reverse_with_buffer(I beg, I end, B bffr_end) {
	I curr = beg;
	while (curr != end) {
		--bffr_end;
		*bffr_end = *curr;
		++curr;
	}

	while (beg != end) {
		*beg = *bffr_end;
		++beg;
		++bffr_end;
	}
}


// bffr points to the *front* of the buffer
// TODO:  Don't need end
template<typename I, typename N, typename B>  // I models forward iterator, B models bidirectional iterator
void reverse_n_with_buffer(I beg, I end, N n, B bffr) {
	I curr = beg;
	N m = n;
	while (m > N(0)) {
		*bffr = *curr;
		++curr;
		++bffr;
		--m;
	}

	m = n;
	while (m > N(0)) {
		--bffr;
		*beg = *bffr;
		++beg;
		--m;
	}
}


// Quadratic in-place reverse that works with fwd iterators
template<typename I>  // I models fwd iterator
void reverse_in_place_quadratic(I beg, I end) {
	typename std::iterator_traits<I>::difference_type n {0};
	I last = beg;
	while (last != end) {
		++n;
		++last;
	}

	while (n >= 2) {
		last = beg;
		nop::advance(last,n-1);
		std::iter_swap(beg,last);
		++beg;
		n -= 2;
	}
}


template<typename I1, typename I2>  // I1, I2 model forward iterator
I2 swap_ranges(I1 beg1, I1 end1, I2 beg2) {
	while (beg1 != end1) {
		std::iter_swap(beg1,beg2);
		++beg1;
		++beg2;
	}
	return beg2;
}

// Result.first and result.second are one past the last element swapped from both ranges.  
template<typename I1, typename I2>  // I1, I2 model fwd iterator
std::pair<I1,I2> swap_ranges(I1 beg1, I1 end1, I2 beg2, I2 end2) {
	while ((beg1 != end1) && (beg2 != end2)) {
		std::iter_swap(beg1,beg2);
		++beg1;
		++beg2;
	}
	return std::pair {beg1,beg2};
}

template<typename I1, typename N, typename I2>  // I1, I2 model fwd iterator
std::pair<I1,I2> swap_ranges(I1 beg1, N n, I2 beg2) {
	while (n > 0) {
		std::iter_swap(beg1,beg2);
		++beg1;
		++beg2;
		--n;
	}
	return std::pair {beg1,beg2};
}




//template<typename I, typename N>  // I models fwd iterator
//I reverse_n_in_place(I beg, N n) {
//	//...
//}




};  // namespace nop




