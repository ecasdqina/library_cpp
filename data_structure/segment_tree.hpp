#pragma once

#include <vector>
#include <cstdint>

namespace cplib {
	template<class Monoid> class segment_tree {
	public:
		using value_type = Monoid;
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
		explicit segment_tree(const std::vector<value_type>& vec): segment_tree(vec.size()) {
			for(usize i = 0; i < vec.size(); i++) set(i, vec[i]);
			build();
		}

		usize size() const { return n; }
		value_type get(usize i) const { return data[i + base()]; }
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

		value_type fold(usize first, usize last) const {
			first += base();
			last += base();

			value_type lval = value_type::identity();
			value_type rval = value_type::identity();
			while(first != last) {
				if(first & 1) lval = value_type::operation(lval, data[first++]);
				if(last  & 1) rval = value_type::operation(data[--last], rval);
				first >>= 1;
				last  >>= 1;
			}
			return value_type::operation(lval, rval);
		}
		value_type fold_all() const { return data[1]; }

		// return max{r | f(fold(l, r - 1)) = true}
		template<class F> usize search_right(int l, const F& f) const {
			if(l == size()) return base();

			l += base();
			value_type acc = value_type::identity();
			do {
				while(l % 2 == 0) l >>= 1;
				if(!f(value_type::operation(acc, data[l]))) {
					while(l < base()) {
						l = l << 1;
						if(f(value_type::operation(acc, data[l]))) {
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
				if(!f(value_type::operation(data[r], acc))) {
					while(r < base()) {
						r = r * 2 + 1;
						if(f(value_type::operation(data[r], acc))) {
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
