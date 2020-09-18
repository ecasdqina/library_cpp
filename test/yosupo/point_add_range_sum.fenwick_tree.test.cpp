#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../../data_structure/fenwick_tree.hpp"
#include "../../other/fast_io.hpp"

int main() {
	int n, q; fin.scan(n, q);
	std::vector<long long> a; for(auto& v: a) fin.scan(v);

	cplib::fenwick_tree<cplib::add_monoid<long long>> fwt(begin(a), end(a));
	while(q--) {
		int type; fin.scan(type);

		if(type == 0) {
			int p, x; fin.scan(p, x);

			fwt.update(p, x);
		} else if(type == 1) {
			int l, r; fin.scan(l, r);

			fout.println(fwt.fold(l, r));
		}
	}
}
