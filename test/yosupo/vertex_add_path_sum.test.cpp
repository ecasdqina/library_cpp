#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include <stdio.h>
#include "../../data_structure/segment_tree.hpp"
#include "../../tree/heavy_light_decomposition.hpp"

using i64 = std::int_fast64_t;

int main() {
	int n, q; scanf("%d%d", &n, &q); std::vector<int> a(n);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);

	heavy_light_decomposition hld(n);
	for(int i = 0; i < n - 1; i++) {
		int a, b; scanf("%d%d", &a, &b);

		hld.add_edge(a, b);
	}
	hld.build();
	
	segment_tree<monoid<i64>> seg(n);
	for(int i = 0; i < n; i++) seg.change(hld[i], a[i]);
	while(q--) {
		int type, x, y; scanf("%d%d%d", &type, &x, &y);

		if(type == 0) seg.update(hld[x], y);
		if(type == 1) {
			i64 ans = 0;
			auto p = [&](int l, int r) { ans += seg.fold(l, r); };
			hld.path(x, y, p);
			
			printf("%lld\n", ans);
		}
	}
	return 0;
}
