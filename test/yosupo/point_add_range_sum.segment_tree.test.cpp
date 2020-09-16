#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../../data_structure/segment_tree.hpp"
#include "../../other/fast_io.hpp"

int main() {
	int n, q; fin.scan(n, q);

	using T = cplib::add_monoid<long long>;
	cplib::segment_tree<T> seg(n);
		int a; fin.scan(a);

		seg.change(i, T{a});
	}

	while(q--) {
		int type; fin.scan(type);

		if(type == 0) {
			int p, x; fin.scan(p, x);

			seg.update(p, T{x});
		} else if(type == 1) {
			int l, r; fin.scan(l, r);

			fout.println(seg.fold(l, r).a);
		}
	}
}
