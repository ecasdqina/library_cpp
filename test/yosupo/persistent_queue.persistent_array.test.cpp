#define PROBLEM "https://judge.yosupo.jp/problem/persistent_queue"

#include "../../data_structure/persistent_array.hpp"
#include "../../other/fast_io.hpp"

int main() {
	int q; fin.scan(q);

	std::vector<int> l(1, 0), r(1, 0);
	persistent_array<int> pa;
	for(int i = 0; i < q; i++) {
		int type; fin.scan(type);

		if(type == 0) {
			int t, x; fin.scan(t, x); t++;
			
			pa.set(r[t], x, t);
			l.push_back(l[t]);
			r.push_back(r[t] + 1);
		} else if(type == 1) {
			int t; fin.scan(t); t++;

			fout.println(pa.get(l[t], t));
			pa.set(l[t], -1, t);
			l.push_back(l[t] + 1);
			r.push_back(r[t]);
		}
	}
	return 0;
}
