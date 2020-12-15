#pragma once
#include <utility>  // std::pair
#include <algorithm>  // std::find, std::find_if_not
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
	return nop::is_partitioned(beg1,end1,is_eqv) 
		&& nop::is_permutation(beg1,end1,beg2,end2,is_eqv);
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

// True if the first range is partitoned by predicate p and if the partitioning
// is stable wrt the order of the elements in range 2.  
template<typename I1, typename I2, typename P, typename Eqv>
bool is_stable_partitioning(I1 beg1, I1 end1, I2 beg2, I2 end2, P p, Eqv is_eq) {
	I1 m = std::find_if(beg1,end1,p);
	bool is_partitioned = (std::find_if_not(m,end1,p) == end1);
	bool is_permutation = (nop::mismatch_permuted(beg2,end2,beg1,m,m,end1,p,is_eq)
							== std::tuple {end2, m, end1});
	
	return is_permutation && is_partitioned;
}


// p.196:  Problem: Define stable_partition_with_buffer – a function that partitions a
// range by first copying elements into a buffer.  
template<typename I, typename P>
I stable_partition_with_buffer(I beg, I end, I bffr, P pred) {
	I m = beg;
	I bffr_curr = bffr;
	while (beg != end) {
		if (!pred(*beg)) {
			*m = *beg;
			++m;
		} else {
			*bffr_curr = *beg;
			++bffr_curr;
		}
		++beg;
	}
	I end_t = m;
	while (end_t != end) {
		*end_t = *bffr;
		++bffr;
		++end_t;
	}

	return m;
}

void test_stable_partition_with_buffer();



};  // namespace nop


