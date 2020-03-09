## 計算量
- 空間 $\Theta(N)$

## operations
- fold(l, r)
	- $\Theta(\log N)$
- update(p, f)
	- data[p] $\leftarrow$ f(data[p])
	- $\Theta(\log N)$
- update(p, x)
	- data[p] $\leftarrow$ data[p] $\cdot$ x
	- $\Theta(\log N)$
- change(p, x)
	- data[p] $\leftarrow$ x
	- $\Theta(\log N)$
- operator[k]
	- $\Theta(1)$
- search(l, f)
	- $\max\lbrace x \vert f(fold(l, x)) = true, l \le x \le N \rbrace$ を返します．
	- $\Theta(\log N)$

## monoid
- デフォルトコンストラクタが単位元として定義されていること．
- operator+ が定義されていること．

## example
```cpp
using mint = modint<998244353>;

struct node {
	mint a, b;

	node(mint a = 1, mint b = 0): a(a), b(b) {}
	node operator+(node r) const { return node(r.a * a, r.a * b + r.b); }
	mint eval(mint x) { return a * x + b; }
};

int main() {
	int n, q; scanf("%d%d", &n, &q);
	segment_tree<monoid<node>> seg(n);
	for(int i = 0; i < n; i++) {
		int a, b; scanf("%d%d", &a, &b);

		seg.change(i, node(a, b));
	}

	while(q--) {
		int type, x, y, z; scanf("%d%d%d%d", &type, &x, &y, &z);

		if(type == 0) seg.change(x, node(y, z));
		if(type == 1) printf("%llu\n", seg.fold(x, y).eval(z));
	}
	return 0;
}

```