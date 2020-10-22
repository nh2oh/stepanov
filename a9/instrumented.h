#pragma once
#include <iostream>
#include <cstddef>  // std::size_t

namespace a9 {


struct instrumented_base {
	enum : std::size_t { 
		default_construct,copy_construct,copy_assign,destruct,
		compare_equal,compare_less
	};

	static std::size_t* counts[6];
};

template<typename T>
struct instrumented {
	T value;

	instrumented() {};
	explicit instrumented(const T& x) : value(x) {};
	instrumented(const instrumented& x) : value(x.value) {};

	instrumented& operator=(const instrumented& rhs) {
		value = rhs.value;
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
};


template<typename T>
bool operator==(const instrumented<T>& lhs, const instrumented<T>& rhs) {
	return lhs.value == rhs.value;
}

template<typename T>
bool operator!=(const instrumented<T>& lhs, const instrumented<T>& rhs) {
	return !(lhs == rhs);
}

template<typename T>
bool operator<(const instrumented<T>& lhs, const instrumented<T>& rhs) {
	return lhs.value < rhs.value;
}

template<typename T>
bool operator>(const instrumented<T>& lhs, const instrumented<T>& rhs) {
	return rhs < lhs;
}

template<typename T>
bool operator<=(const instrumented<T>& lhs, const instrumented<T>& rhs) {
	return !(rhs < lhs);
}

template<typename T>
bool operator>=(const instrumented<T>& lhs, const instrumented<T>& rhs) {
	return !(lhs < rhs);
}


void test_instrumented();




template<typename T>
std::ostream& operator<<(std::ostream& out, const instrumented<T>& rhs) {
	out << rhs.value;
	return out;
}


};  // namespace a9



