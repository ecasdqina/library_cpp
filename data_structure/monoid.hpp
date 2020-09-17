#pragma once

#include <algorithm>

namespace cplib {
	template<class T, T id = T{}>
	struct add_monoid {
		T a;

		static constexpr add_monoid operation(const add_monoid& l, const add_monoid& r) { return add_monoid{l.a + r.a}; }
		static constexpr add_monoid identity{id};
	};

	template<class T, T id = T{1}>
	struct mul_monoid {
		T a;

		static constexpr mul_monoid operation(const mul_monoid& l, const mul_monoid& r) { return mul_monoid{l.a * r.a}; }
		static constexpr mul_monoid identity{id};
	};

	template<class T, T id = T{}>
	struct max_monoid {
		T a;

		static constexpr max_monoid operation(const max_monoid& l, const max_monoid& r) { return max_monoid{std::max(l.a, r.a)}; }
		static constexpr max_monoid identity{id};
	};

	template<class T, T id = T{}>
	struct min_monoid {
		T a;

		static constexpr min_monoid operation(const min_monoid& l, const min_monoid& r) { return min_monoid{std::min(l.a, r.a)}; }
		static constexpr min_monoid identity{id};
	};
}
