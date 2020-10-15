#pragma once




namespace nop {



struct strict_weak_ordered_t {
	int first;
	int second;
};

bool operator==(const strict_weak_ordered_t&, const strict_weak_ordered_t&);
bool operator!=(const strict_weak_ordered_t&, const strict_weak_ordered_t&);
bool operator<(const strict_weak_ordered_t&, const strict_weak_ordered_t&);
bool operator<=(const strict_weak_ordered_t&, const strict_weak_ordered_t&);
bool operator>(const strict_weak_ordered_t&, const strict_weak_ordered_t&);
bool operator>=(const strict_weak_ordered_t&, const strict_weak_ordered_t&);

struct lt {
	bool operator()(const strict_weak_ordered_t&, const strict_weak_ordered_t&) const;
};
struct eq {
	bool operator()(const strict_weak_ordered_t&, const strict_weak_ordered_t&) const;
};



};  // namespace nop

