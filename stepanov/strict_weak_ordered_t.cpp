#include "strict_weak_ordered_t.h"


bool nop::operator==(const nop::strict_weak_ordered_t& lhs, const nop::strict_weak_ordered_t& rhs) {
	return ((lhs.first == rhs.first) && (lhs.second == rhs.second));
}
bool nop::operator!=(const nop::strict_weak_ordered_t& lhs, const nop::strict_weak_ordered_t& rhs) {
	return !(lhs == rhs);
}
bool nop::operator<(const nop::strict_weak_ordered_t& lhs, const nop::strict_weak_ordered_t& rhs) {
	if (lhs.first < rhs.first) {
		return true;
	}
	return lhs.second < rhs.second;
}
bool nop::operator<=(const nop::strict_weak_ordered_t& lhs, const nop::strict_weak_ordered_t& rhs) {
	return !(rhs < lhs);
}
bool nop::operator>(const nop::strict_weak_ordered_t& lhs, const nop::strict_weak_ordered_t& rhs) {
	return rhs < lhs;
}
bool nop::operator>=(const nop::strict_weak_ordered_t& lhs, const nop::strict_weak_ordered_t& rhs) {
	return !(lhs < rhs);
}

bool nop::eq::operator()(const nop::strict_weak_ordered_t& lhs, const nop::strict_weak_ordered_t& rhs) const {
	return lhs.first == rhs.first;
}
bool nop::lt::operator()(const nop::strict_weak_ordered_t& lhs, const nop::strict_weak_ordered_t& rhs) const {
	return lhs.first < rhs.first;
}




