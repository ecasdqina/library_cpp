#pragma once

#include <vector>
#include <cstdint>

#include "../data_structure/monoid.hpp"

namespace cplib {
template<class Monoid> class segment_tree {
public:
	using value_type = Monoid;
	using T = typename value_type::value_type;
	using usize = std::uint_fast32_t;

private:
	int n;
	std::vector<value_type> data;

private:
	usize base() const { return data.size() >> 1; }

public:
	segment_tree() = default;
	explicit segment_tree(usize n): n(n) {
		usize size = 1;
		while(size <= n) size <<= 1;
		data.assign(size << 1, value_type::identity());
	}
	explicit segment_tree(usize n, const T& x): segment_tree(n) {
		for(usize index = 0; index < n; index++) set(index, x);
		build();
	}
	template<class InputIt, typename std::iterator_traits<InputIt>::iterator_category()>
	segment_tree(InputIt first, InputIt last, std::input_iterator_tag) {
		for(usize index = 0; first != last; first++, index++) set(index, *first);
		build();

	}

	usize size() const { return n; }
	bool empty() const { return size() == 0; }
	void clear() {
		n = 0;
		data.clear();
	}
	void swap(segment_tree& r) {
		std::swap(n, r.n);
		data.swap(r.data);
	}

	T get(usize i) const { return data[i + base()].a; }
	void set(usize i, const value_type& x) { data[i + base()] = x; }

	void build() {
		for(usize i = (int)base() - 1; i > 0; i--)
			data[i] = value_type::operation(data[i * 2 + 0], data[i * 2 + 1]);
	}
	void change(usize i, const value_type& x) {
		data[i += base()] = x;
		while(i >>= 1) data[i] = value_type::operation(data[i * 2 + 0], data[i * 2 + 1]);
	}
	void update(usize i, const value_type& x) { change(i, value_type::operation(get(i), x)); }

	T fold(usize first, usize last) const {
		first += base();
		last += base();

		value_type lval = value_type::identity();
		value_type rval = value_type::identity();
		while(first != last) {
			if(first & 1) {
				lval = value_type::operation(lval, data[first]);
				first++;
			}
			if(last  & 1) {
				--last;
				rval = value_type::operation(data[last], rval);
			}
			first >>= 1;
			last  >>= 1;
		}
		return value_type::operation(lval, rval).a;
	}
	T fold_all() const { return data[1].a; }

	// return max{r | f(fold(l, r - 1)) = true}
	template<class F> usize search_right(int l, const F& f) const {
		if(l == size()) return base();

		l += base();
		value_type acc = value_type::identity();
		do {
			while(l % 2 == 0) l >>= 1;
			if(!f(value_type::operation(acc, data[l]).a)) {
				while(l < base()) {
					l = l << 1;
					if(f(value_type::operation(acc, data[l]).a)) {
						acc = value_type::operation(acc, data[l]);
						l += 1;
					}
				}
				return l - base();
			}
			acc = value_type::operation(acc, data[l]);
			l += 1;
		} while((l & -l) != l);
		return size();
	}

	// return min{l | f(fold(l, r - 1) = true}
	template<class F> usize search_left(int r, const F& f) const {
		if(r == 0) return 0;

		r += base();
		value_type acc = value_type::identity();
		do {
			r--;
			while(r > 1 and (r % 2)) r >>= 1;
			if(!f(value_type::operation(data[r], acc).a)) {
				while(r < base()) {
					r = r * 2 + 1;
					if(f(value_type::operation(data[r], acc).a)) {
						acc = value_type::operation(data[r], acc);
						r -= 1;
					}
				}
				return r + 1 - base();
			}
			acc = value_type::operation(data[r], acc);
		} while((r & -r) == r);
		return 0;
	}
};
}

// @docs docs/segment_tree.md
