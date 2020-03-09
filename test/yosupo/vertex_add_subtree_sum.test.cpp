#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include <stdio.h>
#include "../../data_structure/segment_tree.hpp"
#include "../../tree/heavy_light_decomposition.hpp"

using i64 = std::int_fast64_t;

int main() {
	int n, q; scanf("%d%d", &n, &q); std::vector<int> a(n);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);

	heavy_light_decomposition hld(n);
	for(int i = 1; i < n; i++) {
		int p; scanf("%d", &p);

		hld.add_edge(p, i);
	}
	hld.build();
	
	segment_tree<monoid<i64>> seg(n);
	for(int i = 0; i < n; i++) seg.change(hld[i], a[i]);
	while(q--) {
		int type; scanf("%d", &type);
		
		if(type == 0) {
			int x, y; scanf("%d%d", &x, &y);
			
			seg.update(hld[x], y);
		} if(type == 1) {
			int v; scanf("%d", &v);
			
			i64 ans = 0;
			auto p = [&](int l, int r) { ans += seg.fold(l, r); };
			hld.subtree(v, p);
			
			printf("%lld\n", ans);
		}
	}
	return 0;
}
