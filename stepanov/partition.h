#pragma once
#include <iterator>  // std::iter_swap()
#include<algorithm>  // std::find_if(), std::find_if_not()

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
I partition_forward(I beg, I end, P pred) {
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

template<typename I, typename P>  // I models fwd iterator
I partition_forward_inline_find(I beg, I end, P pred) {
	//I pvt = std::find_if(beg,end,pred);
	I pvt = beg;
	while (true) {
		if (pvt==end) { return pvt; }
		if (pred(*pvt)) { break; }
		++pvt;
	}
	// if (pvt == end) { return pvt; }  // inline find allows this check to be dropped
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
I find_backward_if_not0(I beg, I end, P pred) {
	if (end == beg) { return end; }
	while (true) {
		--end;
		if (!pred(*end)) { return ++end; }
		if (end == beg) { return end; }
	}
}

// Finds the rightmost element in the range [beg,end) for which !pred and returns
// its *successor*.  If all elements in the range satisfy pred, returns beg.  
template<typename I, typename P>  // I models bidirectional iterator
I find_backward_if_not(I beg, I end, P pred) {
	while (beg != end) {
		--end;
		if (!pred(*end)) { return ++end; }
	}
	// end == beg && pred(*end)
	return end;
}

template<typename I, typename P>  // I models bidirectional iterator
I partition_bidirectional_1(I beg, I end, P pred) {
	while (true) {
		beg = std::find_if(beg,end,pred);
		end = nop::find_backward_if_not(beg,end,pred);
		if (end == beg) { return beg; }
		--end;
		std::iter_swap(beg,end);
		++beg;
	}
}

// Inlined calls to find to generate a more optimal version
template<typename I, typename P>  // I models bidirectional iterator
I partition_bidirectional(I beg, I end, P pred) {
	while (true) {
		//beg = std::find_if(beg,end,pred);
		while (true) {
			if (beg == end) { return beg; }
			if (pred(*beg)) { break; }
			++beg;
		}
		// beg!=end && pred(*beg)

		//end = nop::find_backward_if_not(beg,end,pred);
		while (true) {
			--end;
			if (beg == end) { return ++beg; }
			if (!pred(*end)) { break; }
		}
		// beg!=end && !pred(*end)

		std::iter_swap(beg,end);
		++beg;
	}
}



};  // namespace nop

