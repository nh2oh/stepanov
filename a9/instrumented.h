#pragma once
#include <iostream>
#include <cstddef>  // std::size_t
#include <vector>
#include <string>


namespace a9 {


struct instrumented_base {
	enum : std::size_t { 
		default_construct,copy_construct,copy_assign,destruct,
		compare_equal,compare_less
	};
	static const std::size_t num_ops = 6;
	static std::size_t counts[num_ops];
	static std::vector<std::string> op_names;

	static void initialize();
};

template<typename T>
struct instrumented : instrumented_base {
	T value;

	instrumented() {
		counts[default_construct] += 1;
	}

	explicit instrumented(const T& x) : value(x) {};

	instrumented(const instrumented& x) : value(x.value) {
		counts[copy_construct] += 1;
	}

	instrumented& operator=(const instrumented& rhs) {
		counts[copy_assign] += 1;
		value = rhs.value;
		return *this;
	}

	/*instrumented& operator=(const T& rhs) {
		value = rhs;
		return *this;
	}*/

	~instrumented() {
		counts[destruct] += 1;
	}

	// This should work but does not compile
	// See:  https://isocpp.org/wiki/faq/templates#template-friends
	//friend std::ostream& operator<< <> (std::ostream&, const instrumented<T>&);

	template<typename U>
	friend std::ostream& operator<<(std::ostream&, const instrumented<U>&);
	
	/*template<typename U>
	friend std::ostream& operator<<(std::ostream& out, const instrumented<U>& rhs) {
		out << rhs.value;
		return out;
	}*/



	friend bool operator==(const instrumented& lhs, const instrumented& rhs) {
		counts[compare_equal] += 1;
		return lhs.value == rhs.value;
	}

	friend bool operator!=(const instrumented& lhs, const instrumented& rhs) {
		return !(lhs == rhs);
	}

	friend bool operator<(const instrumented& lhs, const instrumented& rhs) {
		counts[compare_less] += 1;
		return lhs.value < rhs.value;
	}

	friend bool operator>(const instrumented& lhs, const instrumented& rhs) {
		return rhs < lhs;
	}

	friend bool operator<=(const instrumented& lhs, const instrumented& rhs) {
		return !(rhs < lhs);
	}

	friend bool operator>=(const instrumented& lhs, const instrumented& rhs) {
		return !(lhs < rhs);
	}

};





void test_instrumented();




template<typename T>
std::ostream& operator<<(std::ostream& out, const instrumented<T>& rhs) {
	out << rhs.value;
	return out;
}


};  // namespace a9



