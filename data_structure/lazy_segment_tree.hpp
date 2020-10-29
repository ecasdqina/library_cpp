#pragma once

#include <vector>
#include <stack>
#include <cstdint>

#include "../data_structure/monoid.hpp"

namespace cplib {
template<class M, class E, class operation> class lazy_segment_tree {
public:
	using value_type 	= M;
	using T 			= typename value_type::value_type;
	using operator_type = E;
	using usize 		= std::uint_fast32_t;

	struct node_type {
		value_type value;
		operator_type lazy;

		node_type(const value_type& value, const operator_type& lazy): value(value), lazy(lazy) {}
	};

private:
	std::vector<node_type> data;

	value_type value(const node_type& x) const { return value_type{operation()(x.value.a, x.lazy.a)}; }
	usize countr_zeros(usize x) const { return __builtin_ctzll(x); }

	void add(operator_type& l, const operator_type& r) { l = operator_type::operation(l, r); }

	void propagate(usize idx) {
		add(data[idx * 2 + 0].lazy, data[idx].lazy);
		add(data[idx * 2 + 1].lazy, data[idx].lazy);
		data[idx].lazy = operator_type::identity();
	}
	void propagate_bound(usize idx) {
		if(idx == 0) return;

		std::stack<usize> order;

		idx >>= countr_zeros(idx);
		while(idx >>= 1) order.push(idx);
		while(!order.empty()){
			propagate(order.top());
			order.pop();
		}
	}

	void recalc(usize idx) { data[idx].value = value_type::operation(value(data[idx * 2 + 0]), value(data[idx * 2 + 1])); }
	void recalc_bound(usize idx) {
		if(idx == 0) return;

		idx >>= countr_zeros(idx);
		while(idx >>= 1) recalc(idx);
	}

public:
	lazy_segment_tree() = default;
	explicit lazy_segment_tree(usize n): data(n << 1, node_type(value_type::identity(), operator_type::identity())) {}
	template<class InputIt> explicit lazy_segment_tree(InputIt first, InputIt last)
	: lazy_segment_tree(std::distance(first, last)) {
		for(int index = 0; first != last; first++, index++) set(index, *first);
		build();
	}
	void build() { for(usize i = size() - 1; i > 0; i--) recalc(i); }

	usize size() { return data.size() >> 1; }
	bool empty() { return size() == 0; }
	void clear() { data.clear(); }
	void swap(lazy_segment_tree& r) { data.swap(r.data); }

	T get(usize i) { return fold(i, i + 1); }
	void set(usize i, const value_type& x) { data[i + size()].value = x; };

	void change(usize i, const value_type& x) {
		i += size();
		propagate_bound(((i >> 1) << 1) + 1);
		data[i] = node_type(x, operator_type::identity());
		recalc_bound(((i >> 1) << 1) + 1);
	}
	void update(usize i, const value_type& x) {
		i += size();
		propagate_bound(((i >> 1) << 1) + 1);
		data[i] = node_type(value_type::operation(value(data[i]), x), operator_type::identity());
		recalc_bound(((i >> 1) << 1) + 1);
	}

	T fold(usize first, usize last) {
		first += size();
		last  += size();
		propagate_bound(first);
		recalc_bound(first);
		propagate_bound(last);
		recalc_bound(last);

		value_type lval = value_type::identity();
		value_type rval = value_type::identity();
		while(first != last) {
			if(first & 1) {
				lval = value_type::operation(lval, value(data[first]));
				first++;
			}
			if(last  & 1) {
				last--;
				rval = value_type::operation(value(data[last]), rval);
			}
			first >>= 1;
			last  >>= 1;
		}
		return value_type::operation(lval, rval).a;
	}

	void update(usize first, usize last, const operator_type& x) {
		first += size();
		last  += size();
		usize first_tmp = first;
		usize last_tmp  = last;
		propagate_bound(first);
		propagate_bound(last);
		while(first != last) {
			if(first & 1) {
				add(data[first].lazy, x);
				first++;
			}
			if(last  & 1) {
				last--;
				add(data[last].lazy, x);
			}
			first >>= 1;
			last >>= 1;
		}
		recalc_bound(first_tmp);
		recalc_bound(last_tmp);
	}
};
}
