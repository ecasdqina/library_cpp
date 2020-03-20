#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <algorithm>
#include "../../data_structure/segment_tree.hpp"
#include "../../other/fast_io.hpp"

int main() {
	int n, q; fin.scan(n, q);

	struct node {
		int x;

		node(int x = 1 << 30): x(x) {};
		node operator+(node r) const { return std::min(x, r.x); }
	};
	
	segment_tree<monoid<node>> seg(n);
	for(int i = 0; i < n; i++) {
		int a; fin.scan(a);

		seg.change(i, node(a));
	}

	while(q--) {
		int l, r; fin.scan(l, r);

		fout.println(seg.fold(l, r).x);
	}
}
