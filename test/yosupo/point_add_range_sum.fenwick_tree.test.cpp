#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../../data_structure/fenwick_tree.hpp"
#include "../../other/fast_io.hpp"

int main() {
	int n, q; fin.scan(n, q);
	fenwick_tree<monoid<std::int_fast64_t>> bit(n);
	for(int i = 0; i < n; i++) {
		int a; fin.scan(a);

		bit.change(i, a);
	}

	while(q--) {
		int type; fin.scan(type);

		if(type == 0) {
			int p, x; fin.scan(p, x);

			bit.update(p, x);
		} else if(type == 1) {
			int l, r; fin.scan(l, r);

			fout.println(bit.fold(l, r));
		}
	}
}
