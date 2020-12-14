#pragma once
#include <utility>  // std::pair
#include <algorithm>  // std::find
#include <functional>  // std::bind
#include "partition.h"

//
// Notes on Programming 2018 (Alexander Stepanov)
// Chapter 23 "Lecture 23.  Stable Partition"
//
//

namespace nop {

template<typename I1, typename I2, typename Eqv>
bool is_permutation_0(I1 beg1, I1 end1, I2 beg2, I2 end2, Eqv is_eqv) {
	I1 tmp1 = beg1;
	I2 tmp2 = beg2;
	while ((tmp1 != end1) && (tmp2 != end2)) {
		++tmp1;
		++tmp2;
	}
	if ((tmp1 != end1) || (tmp2 != end2)) {
		return false;
	}

	while (beg1 != end1) {
		tmp2 = std::find(beg2, end2, *beg1);
		if (tmp2 == end2) {
			return false;
		}
		std::iter_swap(tmp2,beg2);
		++beg1;
		++beg2;
	}

	return true;
}

// If sequences 1 and 2 are permutations of oneanother, returns {end1, end2}.  Otherwise,
// result.first == the first element in sequence 1 _not_ present in sequence 2, and
// result.second == end2.  
// Sequence 2 is re-ordered to match sequence 1.  
template<typename I1, typename I2, typename Eqv>
std::pair<I1,I2> mismatch_permuted(I1 beg1, I1 end1, I2 beg2, I2 end2, Eqv is_eqv) {
	while (beg1 != end1) {
		I2 tmp = std::find_if(beg2, end2, std::bind(is_eqv,*beg1));
		if (tmp == end2) { break; }
		std::iter_swap(tmp,beg2);
		++beg1;
		++beg2;
	}
	return std::pair {beg1, beg2};
}

template<typename I1, typename I2, typename Eqv>
bool is_permutation(I1 beg1, I1 end1, I2 beg2, I2 end2, Eqv is_eqv) {
	return nop::mismatch_permuted(beg1,end1,beg2,end2,is_eqv) == std::pair {end1,end2};
}

template<typename I1, typename I2, typename Eqv>
bool is_partitioning(I1 beg1, I1 end1, I2 beg2, I2 end2, Eqv is_eqv) {
	return nop::is_partitioned(beg1,end1,is_equiv) 
		&& nop::is_permutation(beg1,end1,beg2,end2,is_equiv);
}

template<typename I1, typename I2, typename I3, typename P, typename Eqv>
std::tuple<I1,I2,I3> mismatch_partitioned(I1 beg1, I1 end1, 
										I2 beg2_f, I2 end2_f, I3 beg2_t, I3 end2_t, 
										P p, Eqv is_eq) {
	while (beg1 != end1) {
		if (!p(*beg1)) {
			if ((beg2_f==end2_f) || !is_eq(*beg1,*beg2_f)) {
				break;
			}
			++beg2_f;
		} else {
			if ((beg2_t == end2_t) || !is_eq(*beg1, beg2_t)) {
				break;
			}
			++beg2_t;
		}
		++beg1;
	}

	return std::tuple {beg1, beg2_f, beg2_t};
}

// TODO:  Need to verify is_partitioned first
//template<typename I1, typename I2, typename I3, typename P, typename Eqv>
//bool is_stable_partitioning(I1 beg1, I1 end1, 
//										I2 beg2_f, I2 end2_f, I3 beg2_t, I3 end2_t, 
//										P p, Eqv is_eq) {
//	return mismatch_permuted(beg1,end1,beg2_f,end2_f,beg2_t,end2_t,p,is_eq)
//		== std::tuple {end1, end2_f, end2_t};
//}



};  // namespace nop


