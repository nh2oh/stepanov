#pragma once




//
// Notes on Programming 2018 (Alexander Stepanov)
// Chapter 18 "Lecture 18.  Reverse"
//
//

namespace nop {

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




};  // namespace nop




