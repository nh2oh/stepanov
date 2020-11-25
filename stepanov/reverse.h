#pragma once
#include <iterator>  // std::iter_swap()
#include <utility> // std::pair


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









};  // namespace nop




