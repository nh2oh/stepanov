#pragma once

//
// Notes on Programming 2018 (Alexander Stepanov)
// Chapter 20 "Lecture 20.  Partition"
//
//

namespace nop {


template<typename I, typename P>  // I models forward iterator
bool is_partitioned(I beg, I end, P pred) {
	beg = std::find_if(beg,end,pred);
	beg = std::find_if_not(beg,end,pred);
	return beg == end;
}

template<typename I, typename P>  // I models forward iterator
bool is_partitioned(I beg, I pvt, I end, P pred) {
	if (std::find_if(beg,pvt,pred) != pvt) { return false; }
	if (std::find_if_not(pvt,end,pred) != end) { return false; }
	return true;
}

template<typename I, typename P>  // I models fwd iterator
I partition(I beg, I end, P pred) {
	I pvt = std::find_if(beg,end,pred);
	if (pvt == end) { return pvt; }
	I curr = pvt;
	++curr;
	while (curr != end) {
		if (!pred(*curr)) {
			std::iter_swap(curr,pvt);
			++pvt;
		}
		++curr;
	}
	return pvt;
}


template<typename I, typename P> // I models bidirectional iterator
I find_backward_if_not(I beg, I end, P pred) {
	if (end == beg) { return end; }
	while (true) {
		--end;
		if (!pred(*end)) { return ++end; }
		if (end == beg) { return end; }
	}
}


};  // namespace nop

