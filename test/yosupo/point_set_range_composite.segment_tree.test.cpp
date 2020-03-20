#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include "../../data_structure/segment_tree.hpp"
#include "../../math/modint.hpp"
#include "../../other/fast_io.hpp"

using mint = modint<998244353>;

struct node {
	mint a, b;

	node(mint a = 1, mint b = 0): a(a), b(b) {}
	node operator+(node r) const { return node(r.a * a, r.a * b + r.b); }
	mint eval(mint x) { return a * x + b; }
};

int main() {
	int n, q; fin.scan(n, q);
	segment_tree<monoid<node>> seg(n);
	for(int i = 0; i < n; i++) {
		int a, b; fin.scan(a, b);

		seg.change(i, node(a, b));
	}

	while(q--) {
		int type, x, y, z; fin.scan(type, x, y, z);

		if(type == 0) seg.change(x, node(y, z));
		if(type == 1) fout.println(seg.fold(x, y).eval(z).value());
	}
	return 0;
}
