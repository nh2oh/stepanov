#pragma once
#include <utility>  // std::pair
#include <iterator>  // std::iter_swap
#include "reverse.h"
#include "permutations.h"  // nop::do_cycle()

//
// Notes on Programming 2018 (Alexander Stepanov)
// Chapter 19 "Lecture 19.  Rotate"
//
//

namespace nop {

//-----------------------------------------------------------------------------
// Rotate for bidirectional iterators

// rotate_0(...) returns void which is not "correct"
template<typename I>  // I models bidirectional iterator
void rotate_0(I beg, I mid, I end) {
	nop::reverse(beg,mid);
	nop::reverse(mid,end);
	nop::reverse(beg,end);
}


// result.first has _not_ been swapped, result.second _has_ been swapped, hence
// calling reverse(result.first,result.second) will reverse the whole range.  
template<typename I>  // I models bidirectional iterator
std::pair<I,I> reverse_until(I f, I m, I l) {
	while ((f != m) && (l != m)) {
		--l;
		std::iter_swap(f,l);
		++f;
	}
	return std::pair {f,l};
}


// One of result.first, result.second is the old rotation point.  If the old rotation
// point is closer to the front it is result.first, if closer to the end, it is result.end.  
// The remaining iterator is the first element of the (initial) first subrange ?
template<typename I> // I models bidirectional iterator
std::pair<I,I> rotate(I f, I m, I l) {
	nop::reverse(f,m);
	nop::reverse(m,l);
	auto p = nop::reverse_until(f,m,l);
	nop::reverse(p.first,p.second);
	return p;
}


//-----------------------------------------------------------------------------
// Rotate for forward iterators

template<typename I>  // I models forward iterator
void rotate_recursive(I f, I m, I l) {
	auto p = nop::swap_ranges(f,m,m,l);

	// 1) p.first == m && p.second == l => DONE
	// 2) p.first == m && p.second != l
	// 3) p.first != m && p.second == l
	if ((p.first == m) && (p.seond != l)) {
		return nop::rotate_recursive(p.first,p.second,l);
	} else if ((p.first != m) && (p.second == l)) {
		nop::rotate_recursive(p.first,m,l);
	}
}

template<typename I>  // I models forward iterator
void rotate_iterative_0(I f, I m, I l) {
	while (true) {
		auto p = nop::swap_ranges(f,m,m,l);
		// 1) p.first == m && p.second == l => DONE
		// 2) p.first == m && p.second != l
		// 3) p.first != m && p.second == l
		if ((p.first == m) && (p.seond != l)) {
			//return nop::rotate_recursive(p.first,p.second,l);
			f = p.first;
			m = p.second;
		} else if ((p.first != m) && (p.second == l)) {
			//nop::rotate_recursive(p.first,m,l);
			f = p.first;
		} else {
			return;
		}
	}
}

// TODO:  Version with non-void return value


//-----------------------------------------------------------------------------
// Rotate for random access iterators

template<typename I> // I models random access iterator
class rotate_iterator_action {
public:
	rotate_iterator_action(I f, I m, I l) 
		: forward(m-f), backward(m-l), new_rotation_point(f+(l-m)) {};

	void operator()(I& it) {
		it += it < new_rotation_point ? forward : backward;
	}
private:
	typename std::iterator_traits<I>::distance_type forward;
	typename std::iterator_traits<I>::distance_type backward;
	// new_rotation_point is one past the end of the first subrange (after the rotation
	// is complete), equal to the first element of the second subrange (after the
	// rotation is complete).  
	I new_rotation_point;
};



};  // namespace nop

