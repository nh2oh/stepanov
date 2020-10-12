#pragma once
#include <cstddef>  // std::ptrdiff_t


//
// Notes on Programming 2018 (Alexander Stepanov)
// Chapter 2 "Lecture 2.  Designing fvector_int"
// Chapter 3.  "Continuing with fvector_int"
//

namespace nop {  // "notes on programming"

class fvector_int {
public:
	explicit fvector_int() : beg_(nullptr), last_(nullptr), end_(nullptr) {};
	explicit fvector_int(std::ptrdiff_t);
	fvector_int(const fvector_int&);

	fvector_int& operator=(const fvector_int&);

	~fvector_int();

	std::ptrdiff_t size() const;
	std::ptrdiff_t capacity() const;

	int* begin();
	int* back();
	int* end();
	const int* begin() const;
	const int* back() const;
	const int* end() const;

	int& operator[](std::ptrdiff_t);
	const int& operator[](std::ptrdiff_t) const;


	friend void swap(fvector_int&, fvector_int&);
private:
	int *beg_;
	int *last_;
	int *end_;
};


bool operator==(const fvector_int&, const fvector_int&);
bool operator!=(const fvector_int&, const fvector_int&);
bool operator<(const fvector_int&, const fvector_int&);
bool operator>(const fvector_int&, const fvector_int&);
bool operator<=(const fvector_int&, const fvector_int&);
bool operator>=(const fvector_int&, const fvector_int&);

// Total memory utilization stack + heap
std::ptrdiff_t areaof(const fvector_int&);
// Size on heap / (size on stack + size on heap)
double memory_utilization(const fvector_int&);

template <typename T>
void swap(T& x, T& y) {
	T tmp = y;
	y = x;
	x = tmp;
}



void fvector_int_copy_assign();


};  // namespace nop

