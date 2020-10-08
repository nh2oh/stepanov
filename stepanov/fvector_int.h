#pragma once
#include <cstddef>  // std::ptrdiff_t


//
// Notes on Programming 2018 (Alexander Stepanov)
// Chapter 2 "Lecture 2.  Designing fvector_int"
//


class fvector_int {
public:
	explicit fvector_int() : beg_(nullptr), back_(nullptr), end_(nullptr) {};
	explicit fvector_int(std::ptrdiff_t);
	fvector_int(const fvector_int&);

	fvector_int& operator=(const fvector_int&);

	~fvector_int();

	std::ptrdiff_t size() const;

	int* begin();
	int* back();
	int* end();
	const int* begin() const;
	const int* back() const;
	const int* end() const;

	int& operator[](std::ptrdiff_t);
	const int& operator[](std::ptrdiff_t) const;

private:
	int *beg_;
	int *back_;
	int *end_;
};


bool operator==(const fvector_int&, const fvector_int&);
bool operator!=(const fvector_int&, const fvector_int&);
