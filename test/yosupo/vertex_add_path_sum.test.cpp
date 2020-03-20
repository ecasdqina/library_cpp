#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include <stdio.h>
#include "../../data_structure/segment_tree.hpp"
#include "../../tree/heavy_light_decomposition.hpp"
#include "../../other/fast_io.hpp"

using i64 = std::int_fast64_t;

int main() {
	int n, q; fin.scan(n, q); std::vector<int> a(n);
	for(int i = 0; i < n; i++) fin.scan(a[i]);

	heavy_light_decomposition hld(n);
	for(int i = 0; i < n - 1; i++) {
		int a, b; fin.scan(a, b);

		hld.add_edge(a, b);
	}
	hld.build();
	
	segment_tree<monoid<i64>> seg(n);
	for(int i = 0; i < n; i++) seg.change(hld[i], a[i]);
	while(q--) {
		int type, x, y; fin.scan(type, x, y);

		if(type == 0) seg.update(hld[x], y);
		if(type == 1) {
			i64 ans = 0;
			auto p = [&](int l, int r) { ans += seg.fold(l, r); };
			hld.path(x, y, p);
			
			fout.println(ans);
		}
	}
	return 0;
}
