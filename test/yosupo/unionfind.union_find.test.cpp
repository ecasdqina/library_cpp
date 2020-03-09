#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <stdio.h>
#include "../../data_structure/union_find.hpp"

int main() {
	int n, q; scanf("%d%d", &n, &q);

	union_find uf(n);
	while(q--) {
		int type, x, y; scanf("%d%d%d", &type, &x, &y);

		if(type == 0) uf.unite(x, y);
		if(type == 1) printf("%d\n", uf.is_united(x, y));
	}
	return 0;
}
