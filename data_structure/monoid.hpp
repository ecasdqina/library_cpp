#pragma once

#include <algorithm>

namespace cplib {
template<class T, T id = T{}> struct add_monoid {
	using value_type = T;

	T a;

	constexpr add_monoid(T a): a(a) {}
	static constexpr add_monoid operation(const add_monoid& l, const add_monoid& r) { return add_monoid{l.a + r.a}; }
	static constexpr add_monoid identity() { return add_monoid{id}; };
	static constexpr add_monoid inverse(const add_monoid& x) { return add_monoid{-x.a}; }
};

template<class T, T id = T{1}> struct mul_monoid {
	using value_type = T;

	T a;

	constexpr mul_monoid(T a): a(a) {}
	static constexpr mul_monoid operation(const mul_monoid& l, const mul_monoid& r) { return mul_monoid{l.a * r.a}; }
	static constexpr mul_monoid identity() { return mul_monoid{id}; };
};

template<class T, T id = T{}> struct max_monoid {
	using value_type = T;

	T a;

	constexpr max_monoid(T a): a(a) {}
	static constexpr max_monoid operation(const max_monoid& l, const max_monoid& r) { return max_monoid{std::max(l.a, r.a)}; }
	static constexpr max_monoid identity() { return max_monoid{id}; };
};

template<class T, T id = T{}> struct min_monoid {
	using value_type = T;

	T a;

	constexpr min_monoid(T a): a(a) {}
	static constexpr min_monoid operation(const min_monoid& l, const min_monoid& r) { return min_monoid{std::min(l.a, r.a)}; }
	static constexpr min_monoid identity() { return min_monoid{id}; };
};

template<class T, T& id> struct monoid {
	using value_type = T;

	T a;

	constexpr monoid(T a): a(a) {}
	static constexpr monoid operation(const monoid& l, const monoid& r) { return monoid{l.a + r.a}; }
	static constexpr monoid identity() { return monoid{id}; }
	static constexpr monoid inverse(const monoid& x) { return monoid{x.a.inverse()}; }
};
}
