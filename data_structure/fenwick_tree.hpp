#pragma once

#include <vector>
#include <functional>

#include "../data_structure/monoid.hpp"

namespace cplib {
template<class CommutativeMonoid> class fenwick_tree {
public:
	using value_type = CommutativeMonoid;
	using T			 = typename value_type::value_type;
	using usize      = std::uint_fast32_t;

	std::vector<value_type> data;

private:
	usize lsb(usize i) const { return i & (~i + 1); }

public:
	fenwick_tree() = default;

	fenwick_tree(usize n): data(n + 1, value_type::identity()) {}

	template<class InputIt> fenwick_tree(InputIt first, InputIt last)
	: fenwick_tree(std::distance(first, last)) {
		for(int index = 0; first != last; first++, index++) update(index, *first);
	}

	usize size() const { return data.size() - 1; }
	bool empty() const { return size() == 0; }
	void clear() { data.clear(); }
	void swap(fenwick_tree& r) { data.swap(r.data); }

	T get(usize i) const { return fold(i, i + 1); }
	void set(usize i, const value_type& x) const { change(i, x); }

	T fold(usize last) const {
		value_type acc = value_type::identity();
		while(last) {
			acc = value_type::operation(data[last], acc);

			last -= lsb(last);
		}

		return acc.a;
	}
	T fold(usize first, usize last) const {
		value_type acc = value_type::identity();
		while(first < last) {
			acc = value_type::operation(data[last], acc);

			last -= lsb(last);
		}

		while(last < first) {
			acc = value_type::operation(data[first].inverse(), acc);

			first -= lsb(first);
		}

		return acc.a;
	}
	void update(usize i, const value_type& x) {
		for(++i; i < data.size(); i += lsb(i))
			data[i] = value_type::operation(data[i], x);
	}
	void change(usize i, const value_type& x) {
		update(i, value_type::operation((*this)[i].inverse(), x));
	}

	// return min{x | f(fold(x)) = true}
	template<class F> usize search(const F& f) const {
		if(f(value_type::identity())) return 0;

		value_type acc = value_type::identity();
		usize i = 0, k = data.size();
		while(k >>= 1) {
			if((i | k) < data.size() and !f(value_type::operation(acc, data[i | k]))) {
				acc = value_type::operation(acc, data[i | k]);
				i |= k;
			}
		}
		return i + 1;
	}
};
}
