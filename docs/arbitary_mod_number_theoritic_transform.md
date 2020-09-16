## 計算量
- 時間 $\Theta(N\log N)$

## note
- テンプレート引数として modint が渡されることを想定している．

## description
三素数による NTT を garner のアルゴリズムによって復元するため定数倍が重い．

## reference
- https://math314.hateblo.jp/entry/2015/05/07/014908

## example
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../math/arbitary_mod_number_theoritic_transform.hpp"
#include "../../other/fast_io.hpp"

using mint = modint<(int)(1e9 + 7)>;

int main() {
	int n, m; fin.scan(n, m);
	arbitary_mod_number_theoritic_transform<mint> a(n), b(m);
	for(int i = 0; i < n; i++) {
		int x; fin.scan(x);
		a[i] = x;
	}
	for(int i = 0; i < m; i++) {
		int x; fin.scan(x);
		b[i] = x;
	}

	for(auto v: a * b) fout.print(v.value(), ' ');
	fout.println();
	return 0;
}
```