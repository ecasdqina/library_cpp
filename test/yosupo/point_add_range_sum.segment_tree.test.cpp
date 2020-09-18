#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../../data_structure/segment_tree.hpp"
#include "../../other/fast_io.hpp"

int main() {
	int n, q; fin.scan(n, q);
	std::vector<long long> a; for(auto& v: a) fin.scan(v);

	cplib::segment_tree<cplib::add_monoid<long long>> seg(begin(a), end(a));
	while(q--) {
		int type; fin.scan(type);

		if(type == 0) {
			int p, x; fin.scan(p, x);

			seg.update(p, x);
		} else if(type == 1) {
			int l, r; fin.scan(l, r);

			fout.println(seg.fold(l, r));
		}
	}
}
