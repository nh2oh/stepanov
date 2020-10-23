#include "count_operations.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>



void a9::print_counts_table(const std::vector<std::string>& h, 
						const std::vector<std::vector<std::size_t>>& t) {

	std::vector<std::size_t> max_w(h.size(),0);
	for (std::size_t c = 0; c < h.size(); ++c) {
		max_w[c] = h[c].size();
	}

	for (std::size_t r = 0; r < t.size(); ++r) {
		if (t[r].size() != h.size()) {
			return;
		}
		for (std::size_t c = 0; c < t[r].size(); ++c) {
			auto num_digs = a9::num_digits_positive_int(t[r][c]);
			if (max_w[c] < num_digs) {
				max_w[c] = num_digs;
			}
		}
	}

	for (auto& e : max_w) {
		e += 3;
	}

	for (std::size_t c = 0; c < h.size(); ++c) {
		std::cout << std::setw(max_w[c]) << h[c];
	}
	std::cout << std::endl;

	for (std::size_t r = 0; r < t.size(); ++r) {
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





