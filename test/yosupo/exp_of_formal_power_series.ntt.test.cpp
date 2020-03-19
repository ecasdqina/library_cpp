#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include <stdio.h>
#include "../../math/number_theoritic_transform.hpp"
#include "../../math/formal_power_series.hpp"

using fps = formal_power_series<number_theoritic_transform<modint<998244353>>>;

int main() {
	int n; scanf("%d", &n);
	fps a(n);
	for(int i = 0; i < n; i++) {
		int x; scanf("%d", &x);

		a[i] = x;
	}

	for(auto v: a.exp()) printf("%d ", v.value());
	printf("\n");
	return 0;
}
