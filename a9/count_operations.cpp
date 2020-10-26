#include "count_operations.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <cstddef>  // std::size_t


void a9::print_counts_table(const std::vector<std::string>& h, 
							const std::vector<std::size_t>& num_objects,
							const std::vector<std::vector<std::size_t>>& t) {
	// h are col headers for the cols in t; each row in t is expected to have h.size()
	// entries.  
	// num_objects is the number of objects of instrumented<T> corresponding to each 
	// row of t.  num_objects.size() should == t.size().  
	// The width of each col in t is calculated into max_w (.size() == h.size()); the 
	// first col, n, is generated from num_objects and its width is calculated seprately
	// in max_w_n.  
	const std::size_t col_spacing = 3;

	if (num_objects.size() != t.size()) {
		return;
	}

	std::vector<std::size_t> max_w(h.size(),0);
	for (std::size_t c = 0; c < h.size(); ++c) {
		max_w[c] = h[c].size() + col_spacing;
	}

	// Since the numbers in t are monotonically increasing, only the last row needs
	// to be examined to get the largest number in the col.  
	for (std::size_t c = 0; c < t.back().size(); ++c) {
		max_w[c] = std::max(max_w[c],a9::num_digits_positive_int(t.back()[c])+col_spacing);
	}

	std::size_t max_w_n = 0;
	for (const auto& e : num_objects) {
		max_w_n = std::max(max_w_n,a9::num_digits_positive_int(e) + col_spacing);
	}

	std::cout << std::setw(max_w_n) << "n";
	for (std::size_t c = 0; c < h.size(); ++c) {
		std::cout << std::setw(max_w[c]) << h[c];
	}
	std::cout << std::endl;

	for (std::size_t r = 0; r < t.size(); ++r) {
		std::cout << std::setw(max_w_n) << num_objects[r];
		for (std::size_t c = 0; c < t[r].size(); ++c) {
			std::cout << std::setw(max_w[c]) << t[r][c];
		}
		std::cout << std::endl;
	}

}



std::size_t a9::num_digits_positive_int(std::size_t n) {
	std::size_t n_dig = 0;
	while (n > 0) {
		++n_dig;
		n /= 10;
	}
	return n_dig;
}





