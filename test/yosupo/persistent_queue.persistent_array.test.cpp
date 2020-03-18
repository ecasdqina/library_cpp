#define PROBLEM "https://judge.yosupo.jp/problem/persistent_queue"

#include <stdio.h>
#include "../../data_structure/persistent_array.hpp"

int main() {
	int q; scanf("%d", &q);

	std::vector<int> l(1, 0), r(1, 0);
	persistent_array<int> pa;
	for(int i = 0; i < q; i++) {
		int type; scanf("%d", &type);

		if(type == 0) {
			int t, x; scanf("%d%d", &t, &x); t++;
			pa.set(r[t], x, t);
			l.push_back(l[t]);
			r.push_back(r[t] + 1);
		} else if(type == 1) {
			int t; scanf("%d", &t); t++;

			printf("%d\n", pa.get(l[t], t));
			pa.set(l[t], -1, t);
			l.push_back(l[t] + 1);
			r.push_back(r[t]);
		}
	}
	return 0;
}
