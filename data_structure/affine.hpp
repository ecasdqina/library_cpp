#pragma once

#include <algorithm>

namespace cplib {
template<class T> struct affine {
	using value_type = T;

	value_type a;
	value_type b;

	constexpr affine(const value_type& a = 1, const value_type& b = 0): a(a), b(b) {}
	constexpr affine operator+(const affine& r) const { return affine{a + r.a, b + r.b}; }
	constexpr affine composite(const affine& r) const { return affine{a * r.a, a * r.b + b}; }

	constexpr value_type evaluate(const value_type& x) { return a * x + b; }
};
}
