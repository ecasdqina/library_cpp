#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <stdio.h>
#include "../../data_structure/union_find.hpp"
#include "../../other/fast_io.hpp"

int main() {
	int n, q; fin.scan(n, q);

	union_find uf(n);
	while(q--) {
		int type, x, y; fin.scan(type, x, y);

		if(type == 0) uf.unite(x, y);
		if(type == 1) fout.println(uf.is_united(x, y));
	}
	return 0;
}
