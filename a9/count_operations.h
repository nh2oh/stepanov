#pragma once
#include "instrumented.h"
#include <cstddef>  // std::size_t
#include <algorithm>  // std::max()
#include <numeric>  // std::iota
#include <vector>
#include <random>
#include <cmath>  // std::ceil(), std::log2()

namespace a9 {

void print_counts_table(const std::vector<std::string>&, 
						const std::vector<std::size_t>&, 
						const std::vector<std::vector<std::size_t>>&);
std::size_t num_digits_positive_int(std::size_t);

template<typename F>
void count_operations(std::size_t min_num_el, std::size_t max_num_el, F f) {
	std::random_device rd;
	std::mt19937 rg(rd());

	double r = static_cast<double>(max_num_el)/static_cast<double>(min_num_el);
	auto niter = static_cast<std::size_t>(std::max(std::ceil(std::log2(r)),0.0));

	std::vector<std::vector<std::size_t>> 
		results_table(niter,std::vector<std::size_t>(a9::instrumented_base::num_ops,0));
	std::vector<std::size_t> numel; numel.reserve(niter);

	std::size_t i = 0;
	for (auto num_el = min_num_el; num_el < max_num_el; num_el *= 2) {
		std::vector<a9::instrumented<double>> v(num_el);
		for (std::size_t i = 0; i < v.size(); ++i) {
			v[i] = a9::instrumented<double>(static_cast<double>(i));
		}
		std::shuffle(v.begin(),v.end(),rg);

		a9::instrumented_base::initialize();
		f(v.begin(),v.end());

		numel.push_back(num_el);
		std::copy(a9::instrumented_base::counts,
			a9::instrumented_base::counts+a9::instrumented_base::num_ops,
			results_table[i].begin());

		++i;
	}

	a9::print_counts_table(a9::instrumented_base::op_names,numel,results_table);
}


struct std_sort_functor {
	template<typename It>
	void operator()(It beg, It end) const {
		std::sort(beg,end);
	}
};

struct std_reverse_functor {
	template<typename It>
	void operator()(It beg, It end) const {
		std::reverse(beg,end);
	}
};

template<typename T>
struct std_count_functor {
	T val_;
	std_count_functor(const T& val) : val_(val) {}
	template<typename It>
	void operator()(It beg, It end) const {
		std::count(beg,end,val_);
	}
};


struct swap_each_pair_functor {
	template<typename It>
	void operator()(It beg, It end) const {
		It next = beg;
		while (beg != end) {
			// at start of loop, next == beg
			++next;
			if (next == end) {
				return;
			}
			std::iter_swap(beg,next);
			++beg;  // beg == next ( != end)
			++beg;  // beg might == end
			++next;  // next == beg; next might == end
		}
	}
};




};  // namespace a9

