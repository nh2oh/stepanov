#pragma once
//#include <forward_list>
#include <utility>  // std::pair


//
// Notes on Programming 2018 (Alexander Stepanov)
// Chapter 22 "Lecture 22.  Algorithms on Linked Iterators"
//
//

namespace nop {

template<typename I>  // I models linked iterator
I reverse_linked_0(I beg, I end) {
	I result = end;
	while (beg != end) {
		I next = successor(beg);
		set_successor(beg,result);
		result = beg;
		beg = next;
	}
	return result;
}

// For bidirectional iterators
template<typename I>  // I models linked iterator
void patch_back_links(I beg, I end) {
	while (beg != end) {
		I next = successor(beg);
		set_predecessor(next,beg);
		beg = next;
	}
}


template<typename I, typename P>  // I models linked iterator
std::pair<I,I> partition_node_reversed(I beg, I end, P pred) {
	I t = end;
	I f = end;
	while (beg != end) {
		I next = beg;
		if (pred(*beg)) {
			set_successor(beg,t);
			t = beg;
		} else {
			set_successor(beg,f);
			f = beg;
		}
		beg = next;
	}

	return std::pair {f,t};
}


template<typename I, typename P>
std::pair<std::pair<I,I>,std::pair<I,I>> partition_node_reversed2(I beg, I end, P pred) {
	I h_t = end;
	I h_f = end;
	I t_t = end;
	I t_f = end;


	if (pred(*beg)) {
		I next = successor(beg);
		set_successor(beg,t_t);
		t_t = beg;
		beg = next;
		while (pred(*beg)) {
			beg = successor(beg);
		}
	} else {
		I next = successor(beg);
		set_successor(beg,t_f);
		t_f = beg;
		beg = next;
		while (!pred(*beg)) {
			beg = successor(beg);
		}
	}

	return std::pair {std::pair<I,I> {h_f,t_f}, std::pair<I,I> {h_t,t_t}};
}




};  // namespace nop

