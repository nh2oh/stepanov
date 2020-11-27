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








};  // namespace nop




