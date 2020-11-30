#pragma once
#include "reverse.h"


//
// Notes on Programming 2018 (Alexander Stepanov)
// Chapter 19 "Lecture 19.  Rotate"
//
//


namespace nop {


template<typename I>  // I models bidirectional iterator
void rotate0(I beg, I mid, I end) {
	nop::reverse(beg,mid);
	nop::reverse(mid,end);
	nop::reverse(beg,end);
}






















};  // namespace nop


