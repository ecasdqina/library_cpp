#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <stdio.h>
#include <algorithm>
#include "../../data_structure/segment_tree.hpp"

int main() {
	int n, q; scanf("%d%d", &n, &q);

	struct node {
		int x;

		node(int x = 1 << 30): x(x) {};
		node operator+(node r) const { return std::min(x, r.x); }
	};
	
	segment_tree<monoid<node>> seg(n);
	for(int i = 0; i < n; i++) {
		int a; scanf("%d", &a);

		seg.change(i, node(a));
	}

	while(q--) {
		int l, r; scanf("%d%d", &l, &r);

		printf("%d\n", seg.fold(l, r).x);
	}
}
