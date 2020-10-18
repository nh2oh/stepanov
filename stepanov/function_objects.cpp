#include "function_objects.h"
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iostream>



bool nop::less_abs_fun(double lhs, double rhs) {
	return std::abs(lhs) < std::abs(rhs);
}

bool nop::less_abs::operator()(double lhs, double rhs) const {
	return std::abs(lhs) < std::abs(rhs);
}




void nop::benchmark_less_abs() {
	std::random_device rd;
	std::mt19937 re(rd());
	std::uniform_real_distribution<double> dist(1.0,2.0);

	std::vector<double> rnums_init(1'000'000);
	for (auto& e : rnums_init) {
		e = dist(re);
	}

	std::vector<std::chrono::duration<double>> fun_times;
	std::vector<std::chrono::duration<double>> fun_obj_times;
	for (int i=0; i<10; ++i) {
		auto rnums = rnums_init;
		auto t_start = std::chrono::steady_clock::now();
		//std::sort(rnums.begin(),rnums.end(),nop::less_abs_fun);
		std::sort(rnums.data(),rnums.data()+rnums.size(),nop::less_abs_fun);
		auto t_end = std::chrono::steady_clock::now();
		fun_times.push_back(t_end-t_start);

		rnums = rnums_init;
		t_start = std::chrono::steady_clock::now();
		//std::sort(rnums.begin(),rnums.end(),nop::less_abs());
		std::sort(rnums.data(),rnums.data()+rnums.size(),nop::less_abs());
		t_end = std::chrono::steady_clock::now();
		fun_obj_times.push_back(t_end-t_start);
	}

	std::cout << "less_abs_fun:\n";
	for (int i=0; i<fun_times.size(); ++i) {
		std::cout << fun_times[i].count() << "s\n";
	}

	std::cout << "\n\nless_abs:\n";
	for (int i=0; i<fun_obj_times.size(); ++i) {
		std::cout << fun_obj_times[i].count() << "s\n";
	}

}




