#include "fvector_int.h"
#include <cstddef>  // std::ptrdiff_t
#include <cstring>  // std::memcpy
#include <numeric>  // std::min
#include <cassert>



nop::fvector_int::fvector_int(std::ptrdiff_t sz) {
	this->beg_ = new int[sz];
	this->last_ = this->beg_ + sz;
	this->end_ = this->beg_ + sz;
}

nop::fvector_int::fvector_int(const nop::fvector_int& rhs) {
	auto rhs_cap = rhs.end_ - rhs.beg_;
	auto rhs_n = rhs.last_ - rhs.beg_;
	
	this->beg_ = new int[rhs_cap];
	std::memcpy(this->beg_, rhs.beg_, sizeof(int)*rhs_n);
	this->last_ = this->beg_ + rhs_n;
	this->end_ = this->beg_ + rhs_cap;
}

nop::fvector_int& nop::fvector_int::operator=(const nop::fvector_int& rhs) {
	if (this == &rhs) {
		return *this;
	}

	auto rhs_cap = rhs.end_ - rhs.beg_;
	auto rhs_n = rhs.last_ - rhs.beg_;

	if (rhs_cap == (this->end_-this->beg_)) {
		std::memcpy(this->beg_, rhs.beg_, sizeof(int)*rhs_n);
		this->last_ = this->beg_ + rhs_n;
	} else {
		delete [] this->beg_;
		this->beg_ = new int[rhs_cap];
		std::memcpy(this->beg_, rhs.beg_, sizeof(int)*rhs_n);
		this->last_ = this->beg_+rhs_n;
		this->end_ = this->beg_ + rhs_cap;
	}

	return *this;
}

nop::fvector_int::~fvector_int() {
	delete [] this->beg_;
}

std::ptrdiff_t nop::fvector_int::size() const {
	return this->last_ - this->beg_;
}

std::ptrdiff_t nop::fvector_int::capacity() const {
	return this->end_ - this->beg_;
}

int* nop::fvector_int::begin() {
	return this->beg_;
}
int* nop::fvector_int::back() {
	return this->last_;
}
int* nop::fvector_int::end() {
	return this->end_;
}
const int* nop::fvector_int::begin() const {
	return this->beg_;
}
const int* nop::fvector_int::back() const {
	return this->last_;
}
const int* nop::fvector_int::end() const {
	return this->end_;
}

int& nop::fvector_int::operator[](std::ptrdiff_t idx) {
	return *(this->beg_ + idx);
}
const int& nop::fvector_int::operator[](std::ptrdiff_t idx) const {
	return *(this->beg_ + idx);
}


bool nop::operator==(const nop::fvector_int& lhs, const nop::fvector_int& rhs) {
	if (lhs.size() != rhs.size()) {
		return false;
	}

	for (std::ptrdiff_t i=0; i<lhs.size(); ++i) {
		if (lhs[i] != rhs[i]) {
			return false;
		}
	}

	return true;
}

bool nop::operator!=(const nop::fvector_int& lhs, const nop::fvector_int& rhs) {
	return !(lhs==rhs);
}

bool nop::operator<(const nop::fvector_int& lhs, const nop::fvector_int& rhs) {
	auto min_sz = std::min(lhs.size(), rhs.size());
	for (std::ptrdiff_t i=0; i<min_sz; ++i) {
		if (lhs[i] < rhs[i]) { return true; }
	}
	return lhs.size() < rhs.size();
}

bool nop::operator>(const nop::fvector_int& lhs, const nop::fvector_int& rhs) {
	return rhs < lhs;
}

bool nop::operator<=(const nop::fvector_int& lhs, const nop::fvector_int& rhs) {
	return !(rhs < lhs);
}

bool nop::operator>=(const nop::fvector_int& lhs, const nop::fvector_int& rhs) {
	return !(lhs < rhs);
}

std::ptrdiff_t nop::areaof(const nop::fvector_int& v) {
	return sizeof(v) + v.size()*sizeof(int);
}
double nop::memory_utilization(const nop::fvector_int& v) {
	return static_cast<double>(v.size()*sizeof(int)) / static_cast<double>(areaof(v));
}


void nop::swap(nop::fvector_int& x, nop::fvector_int& y) {
	swap(x.beg_,y.beg_);
	swap(x.last_,y.last_);
	swap(x.end_,y.end_);
}


void nop::fvector_int_copy_assign() {
	nop::fvector_int a(100);
	nop::fvector_int b(3);

	// Copy assignment and copy construction behave in exactly the same way
	// Assign a small thing to a big thing
	a = b;
	assert(a==b && a.size()==b.size() && a.capacity()==b.capacity(),
		"a==b && a.size()==b.size() && a.capacity()==b.capacity()");
	nop::fvector_int c(a);
	assert(a==c && a.size()==c.size() && a.capacity()==c.capacity(),
		"a==c && a.size()==c.size() && a.capacity()==c.capacity()");


	return;
}



