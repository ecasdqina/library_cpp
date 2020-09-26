#pragma once

#include <algorithm>
#include <limits>
#include "../data_structure/affine.hpp"

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

template<class T, T id = std::numeric_limits<T>::max()> struct min_monoid {
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

template<class A, class B> struct cartesian_product_monoid {
	using value_type = std::pair<typename A::value_type, typename B::value_type>;

	value_type a;

	constexpr cartesian_product_monoid(const value_type& a): a(a) {}
	static constexpr cartesian_product_monoid operation(const cartesian_product_monoid& l, const cartesian_product_monoid& r) {
		return cartesian_product_monoid{{A::operation(l.a.first, r.a.first).a, B::operation(l.a.second, r.a.second).a}};
	}
	static constexpr cartesian_product_monoid identity() { return cartesian_product_monoid{{A::identity().a, B::identity().a}}; }
	static constexpr cartesian_product_monoid inverse(const cartesian_product_monoid& x) {
		return cartesian_product_monoid{{A::inverse(x.a.first).a, B::inverse(x.a.second).a}};
	}
};

template<class T> struct affine_composite_monoid {
	using value_type = cplib::affine<T>;

	value_type a;

	constexpr affine_composite_monoid(const value_type& a): a(a) {}
	static constexpr affine_composite_monoid operation(const affine_composite_monoid& l,
													   const affine_composite_monoid& r) {
		return affine_composite_monoid{r.a.composite(l.a)};
	}
	static constexpr affine_composite_monoid identity() {
		return affine_composite_monoid{value_type()};
	}
};
}
