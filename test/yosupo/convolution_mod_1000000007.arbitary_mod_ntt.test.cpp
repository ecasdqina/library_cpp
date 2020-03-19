#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include <stdio.h>
#include "../../math/arbitary_mod_number_theoritic_transform.hpp"

using mint = modint<(int)(1e9 + 7)>;

int main() {
	int n, m; scanf("%d%d", &n, &m);
	arbitary_mod_number_theoritic_transform<mint> a(n), b(m);
	for(int i = 0; i < n; i++) {
		int x; scanf("%d", &x);
		a[i] = x;
	}
	for(int i = 0; i < m; i++) {
		int x; scanf("%d", &x);
		b[i] = x;
	}

	auto c = a * b;
	for(auto v: c) printf("%d ", v.value());
	printf("\n");
	return 0;
}
