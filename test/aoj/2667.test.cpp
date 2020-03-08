#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2667"

#include <stdio.h>
#include <functional>
#include "../../tree/heavy_light_decomposition.hpp"

using i64 = std::int_fast64_t;

template<typename Monoid, typename OperatorMonoid = Monoid>
class lazy_segment_tree {
	using value_type = Monoid;
	using operator_type = OperatorMonoid;
	using size_type = size_t;

	using F = std::function<value_type (value_type, value_type)>;
	using G = std::function<value_type (value_type, operator_type, int, int)>;
	using H = std::function<operator_type (operator_type, operator_type)>;
	
	size_type size_;
	size_type height_;

	F f;
	G g;
	H h;
	value_type id;
	operator_type id_op;
	std::vector<value_type> data;
	std::vector<operator_type> lazy;
	std::vector<size_type> depth;
	
	const size_type get_height(const size_type& size) const {
		size_type height = 1;
		while(1 << height < size) height++;
		return height;
	}
	const size_type base_size() const {
		return 1 << height_;
	}
	const value_type reflect(const size_type & k) {
		if(lazy[k] == id_op) return data[k];
		int l = (k - (1 << depth[k])) * (base_size() >> depth[k]);
		int r = l + (base_size() >> depth[k]);
		return g(data[k], lazy[k], l, r);
	}
	void propagate(const size_type & k) {
		if(lazy[k] == id_op) return;
		lazy[k << 1 ^ 0] = h(lazy[k << 1 ^ 0], lazy[k]);
		lazy[k << 1 ^ 1] = h(lazy[k << 1 ^ 1], lazy[k]);
		data[k] = reflect(k);
		lazy[k] = id_op;
	}
	void thrust(const size_type & k) {
		for(int i = height_; i; i--) propagate(k >> i);
	}
	void recalc(size_type k) {
		while(k >>= 1) data[k] = f(reflect(k << 1 ^ 0), reflect(k << 1 ^ 1));
	}
	
public:
	lazy_segment_tree() {}
	lazy_segment_tree(int n, const F & f, const G & g, const H & h, const value_type & id, const operator_type & id_op) :
		size_(n), f(f), g(g), h(h), id(id), id_op(id_op) {
		height_ = get_height(size_);
		data.assign(base_size() << 1, id);
		lazy.assign(base_size() << 1, id_op);
		depth.assign(base_size() << 1, 0);
		for(int i = 0; i < height_ + 1; i++)
			for(int j = (1 << i); j < (1 << (i + 1)); j++)
				depth[j] = i;
	}
	void update(size_type a, size_type b, operator_type x) {
		thrust(a += base_size());
		thrust(b += base_size() - 1);
		for(size_type l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
			if(l & 1) lazy[l] = h(lazy[l], x), l++;
			if(r & 1) --r, lazy[r] = h(lazy[r], x);
		}
		recalc(a);
		recalc(b);
	}
	void change(size_type k, const value_type x) {
		thrust(k += base_size());
		data[k] = x;
		lazy[k] = id_op;
		recalc(k);
	}
	const value_type fold(size_type a, size_type b) {
		thrust(a += base_size());
		thrust(b += base_size() - 1);

		value_type left_value = id;
		value_type right_value = id;
		for(size_type l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
			if(l & 1) left_value = f(left_value, reflect(l++));
			if(r & 1) right_value = f(reflect(--r), right_value);
		}
		return f(left_value, right_value);
	}

	const value_type operator[](const size_type & k) {
		return fold(k, k + 1);
	}
};

int main() {
	int n, q; scanf("%d%d", &n, &q);
	heavy_light_decomposition hld(n);
	for(int i = 0; i < n - 1; i++) {
		int a, b; scanf("%d%d", &a, &b);

		hld.add_edge(a, b);
	}
	hld.build();

	auto f = [&](i64 a, i64 b) { return a + b; };
	auto g = [&](i64 a, i64 b, i64 l, i64 r) { return a + b * (r - l); };
	auto h = [&](i64 a, i64 b) { return a + b; };
	lazy_segment_tree<i64> seg(n, f, g, h, 0, 0);

	while(q--) {
		int type; scanf("%d", &type);

		if(type == 0) {
			int x, y; scanf("%d%d", &x, &y);

			i64 ans = 0;
			auto p = [&](int l, int r) { ans += seg.fold(l, r); };
			hld.path_edge(x, y, p);

			printf("%lld\n", ans);
		} else if(type == 1) {
			int x, y; scanf("%d%d", &x, &y);

			auto p = [&](int l, int r) { seg.update(l, r, y); };
			hld.subtree_edge(x, p);
		}
	}
	return 0;
}
