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





};  // namespace nop

