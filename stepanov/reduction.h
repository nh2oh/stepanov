#pragma once
#include "actions_orbits.h"  // nop::successor
#include <utility>  // std::pair
#include <algorithm>


//
// Notes on Programming 2018 (Alexander Stepanov)
// Chapter 24 "Lecture 24.  Reduction and Balanced Reduction"
//
//
namespace nop {

template<typename T>
struct is_even {
	bool operator()(const T& x) {
		return (x%2)==0;
	}
};


template<typename I, typename O, typename T>
T reduce_nonzeros(I beg, I end, O op, T z) {
	//auto x = *beg;
	/*beg = std::find_if_not(beg,end,z);
	if (beg == end) { return z; }
	T result = *beg;
	++beg;
	while (beg != end) {
		if (*beg != z) {
			result = op(result,*beg);
		}
		++beg;
	}
	return result;*/
	return *beg;
}



template<typename I>
struct combine_ranges {
	std::pair<I,I> operator()(const std::pair<I,I>& x, const std::pair<I,I>& y) {
		return std::pair<I,I> {std::rotate(x.first,x.second,y.first), y.second};
	}
};


template<typename I, typename P>
struct partition_trivial {
	using result_type = std::pair<I,I>;
	P p;

	partition_trivial(const P& x) : p(x) {};

	std::pair<I,I> operator()(I it) {
		if (p(*it)) {
			return std::pair<I,I> {it,it};
		} else {
			//auto it1 = it;
			return std::pair<I,I> {it,nop::successor(it)};
		}
	}
};

// When incremented, increments the iterator
// When dereferenced, returns the result of f(it)
template<typename I, typename F>
class value_iterator {
public:
	using value_type = typename F::result_type;
	using difference_type = std::ptrdiff_t;
	using iterator_category = typename std::forward_iterator_tag;

	value_iterator() {};
	value_iterator(const I& it, const F& f) : it(it), f(f) {}

	value_iterator& operator++(int) { // postincrement
		auto tmp = *this;
		++*this;
		return tmp;
	}

	value_iterator& operator++() {  // preincrement
		++*this;
		return *this;
	}

	value_type operator*() {
		return f(it);
	}

	friend bool operator==(const value_iterator& left, const value_iterator& right) {
		//static_assert(left.f == right.f);
		return left.it==right.it;
	}
	friend bool operator!=(const value_iterator& left, const value_iterator& right) {
		return !(left==right);
	}

private:
	I it;
	F f;
};


template<typename I, typename P>
I stable_partition_slow_iterative(I beg, I end, P p) {
	//using fun_t = nop::partition_trivial<I,P>;
	//using val_iter = nop::value_iterator<I,fun_t>;

	nop::partition_trivial<I,P> fun(p);
	std::pair<I,I> z(end,end);
	nop::combine_ranges<I> op;
	nop::value_iterator<I,nop::partition_trivial<I,P>> beg1(beg,fun);
	nop::value_iterator<I,nop::partition_trivial<I,P>> end1(end,fun);

	auto b1 = *beg1;
	auto test1 = (beg1==end1);
	auto b2 = *beg1;
	auto test2 = (*beg1==z);
	auto yay = std::find_if_not(beg1,end1,
		[&z](const std::pair<I,I>& x) -> bool {
			return ((x.first==x.first) && (z.second==x.second));
		});

	//return nop::reduce_nonzeros(beg1,end1,op,z).first;
	return beg;
}

void test_stable_partition_slow_iterative();



};  // namespace nop

