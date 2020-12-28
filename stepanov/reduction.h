#pragma once
#include <utility>  // std::pair
#include <algorithm>


//
// Notes on Programming 2018 (Alexander Stepanov)
// Chapter 24 "Lecture 24.  Reduction and Balanced Reduction"
//
//
namespace nop {


template<typename T, typename I, typename O>
T reduce_nonzeros(I beg, I end, O op, T z) {
	beg = std::find_if_not(beg,end,z);
	if (beg == end) { return z; }
	T result = *beg;
	++beg;
	while (beg != end) {
		if (*beg != z) {
			result = op(result,*beg);
		}
		++beg;
	}
	return result;
}



template<typename I>
struct combine_ranges {
	std::pair<I,I> operator()(const std::pair<I,I>& x, const std::pair<I,I>& y) {
		return std::pair<I,I> {std::rotate(x.first,x.second,y.first), y.second};
	}
};



template<typename I, typename P>
struct partition_trivial {
	P p;

	partition_trivial(const P& x) : p(x) {};

	std::pair<I,I> operator()(I it) {
		if (p(*it)) {
			return std::pair<I,I> {it,it};
		} else {
			return std::pair<I,I> {it,++it};
		}
	}
};


// When incremented, increments the iterator
// When dereferenced, returns the result of f(it)
template<typename I, typename F>
class value_iterator {
public:
	value_iterator() {};
	value_iterator(const I& it, const F& f) : it(it), f(f) {}

	value_iterator& operator++(int) { // postincrement
		auto tmp = *this;
		++*this;
		return tmp;
	}

	value_iterator& operator++() {  // preincrement
		++this;
		return *this;
	}

	auto operator*() {
		return f(it);
	}

	friend bool operator==(const value_iterator& left, const value_iterator& right) {
		static_assert(left.f == right.f);
		return left.it==right.it;
	}
	friend bool operator!=(const value_iterator& left, const value_iterator& right) {
		return !(left==right);
	}

private:
	I it;
	F f;
};




};  // namespace nop

