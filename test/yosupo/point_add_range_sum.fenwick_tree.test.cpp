#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <stdio.h>
#include "../../data_structure/fenwick_tree.hpp"

int main() {
	int n, q; scanf("%d%d", &n, &q);
	fenwick_tree<monoid<std::int_fast64_t>> bit(n);
	for(int i = 0; i < n; i++) {
		int a; scanf("%d", &a);

		bit.change(i, a);
	}

	while(q--) {
		int type; scanf("%d", &type);

		if(type == 0) {
			int p, x; scanf("%d%d", &p, &x);

			bit.update(p, x);
		} else if(type == 1) {
			int l, r; scanf("%d%d", &l, &r);

			printf("%lld\n", bit.fold(l, r));
		}
	}
}
