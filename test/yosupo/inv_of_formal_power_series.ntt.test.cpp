#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include "../../math/number_theoritic_transform.hpp"
#include "../../math/formal_power_series.hpp"
#include "../../other/fast_io.hpp"

using fps = formal_power_series<number_theoritic_transform<modint<998244353>>>;

int main() {
	int n; fin.scan(n);
	fps a(n);
	for(int i = 0; i < n; i++) {
		int x; fin.scan(x);

		a[i] = x;
	}

	for(auto v: a.inverse()) fout.print(v.value(), ' ');
	fout.println();
	return 0;
}
