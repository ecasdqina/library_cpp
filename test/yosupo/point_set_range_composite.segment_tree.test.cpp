#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include "../../data_structure/segment_tree.hpp"
#include "../../math/modint.hpp"
#include "../../other/fast_io.hpp"

using mint = modint<998244353>;

int main() {
	int n, q; fin.scan(n, q);

	cplib::segment_tree<cplib::affine_composite_monoid<mint>> seg(n);
	for(int i = 0; i < n; i++) {
		int a, b; fin.scan(a, b);

		seg.set(i, cplib::affine<mint>(a, b));
	}
	seg.build();

	while(q--) {
		int type, x, y, z; fin.scan(type, x, y, z);

		if(type == 0) seg.change(x, cplib::affine<mint>(y, z));
		if(type == 1) fout.println(seg.fold(x, y).evaluate(z).value());
	}
	return 0;
}
