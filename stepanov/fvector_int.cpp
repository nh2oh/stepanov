#include "fvector_int.h"
#include <cstddef>  // std::ptrdiff_t
#include <cstring>  // std::memcpy
#include <numeric>  // std::min
#include <cassert>


fvector_int::fvector_int(std::ptrdiff_t sz) {
	this->beg_ = new int[sz];
	this->last_ = this->beg_ + sz;
	this->end_ = this->beg_ + sz;
}

fvector_int::fvector_int(const fvector_int& rhs) {
	auto rhs_cap = rhs.end_ - rhs.beg_;
	auto rhs_n = rhs.last_ - rhs.beg_;
	
	this->beg_ = new int[rhs_cap];
	std::memcpy(this->beg_, rhs.beg_, sizeof(int)*rhs_n);
	this->last_ = this->beg_ + rhs_n;
	this->end_ = this->beg_ + rhs_cap;
}

fvector_int& fvector_int::operator=(const fvector_int& rhs) {
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

fvector_int::~fvector_int() {
	delete [] this->beg_;
}

std::ptrdiff_t fvector_int::size() const {
	return this->last_ - this->beg_;
}

std::ptrdiff_t fvector_int::capacity() const {
	return this->end_ - this->beg_;
}

int* fvector_int::begin() {
	return this->beg_;
}
int* fvector_int::back() {
	return this->last_;
}
int* fvector_int::end() {
	return this->end_;
}
const int* fvector_int::begin() const {
	return this->beg_;
}
const int* fvector_int::back() const {
	return this->last_;
}
const int* fvector_int::end() const {
	return this->end_;
}

int& fvector_int::operator[](std::ptrdiff_t idx) {
	return *(this->beg_ + idx);
}
const int& fvector_int::operator[](std::ptrdiff_t idx) const {
	return *(this->beg_ + idx);
}


bool operator==(const fvector_int& lhs, const fvector_int& rhs) {
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

bool operator!=(const fvector_int& lhs, const fvector_int& rhs) {
	return !(lhs==rhs);
}

bool operator<(const fvector_int& lhs, const fvector_int& rhs) {
	auto min_sz = std::min(lhs.size(), rhs.size());
	for (std::ptrdiff_t i=0; i<min_sz; ++i) {
		if (lhs[i] < rhs[i]) { return true; }
	}
	return lhs.size() < rhs.size();
}

bool operator>(const fvector_int& lhs, const fvector_int& rhs) {
	return rhs < lhs;
}

bool operator<=(const fvector_int& lhs, const fvector_int& rhs) {
	return !(rhs < lhs);
}

bool operator>=(const fvector_int& lhs, const fvector_int& rhs) {
	return !(lhs < rhs);
}

std::ptrdiff_t areaof(const fvector_int& v) {
	return sizeof(v) + v.size()*sizeof(int);
}
double memory_utilization(const fvector_int& v) {
	return static_cast<double>(v.size()*sizeof(int)) / static_cast<double>(areaof(v));
}



void fvector_int_copy_assign() {
	fvector_int a(100);
	fvector_int b(3);

	// Copy assignment and copy construction behave in exactly the same way
	// Assign a small thing to a big thing
	a = b;
	assert(a==b && a.size()==b.size() && a.capacity()==b.capacity(),
		"a==b && a.size()==b.size() && a.capacity()==b.capacity()");
	fvector_int c(a);
	assert(a==c && a.size()==c.size() && a.capacity()==c.capacity(),
		"a==c && a.size()==c.size() && a.capacity()==c.capacity()");


	return;
}



