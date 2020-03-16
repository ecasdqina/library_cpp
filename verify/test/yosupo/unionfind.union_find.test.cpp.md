---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: test/yosupo/unionfind.union_find.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0b58406058f6619a0f31a172defc0230">test/yosupo</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/unionfind.union_find.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-09 13:35:51+09:00


* see: <a href="https://judge.yosupo.jp/problem/unionfind">https://judge.yosupo.jp/problem/unionfind</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/data_structure/union_find.hpp.html">data_structure/union_find.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/unionfind.union_find.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <stdio.h>
#line 1 "test/yosupo/../../data_structure/union_find.hpp"
#include <cstdint>
#include <vector>

class union_find {
public:
	using size_type = std::int_fast32_t;
	using container = std::vector<size_type>;
	
	container data;
	size_type comp_cnt;

private:
	const size_type find(size_type k) {
		if(data[k] < 0) return k;
		return data[k] = find(data[k]);
	}

public:
	union_find() = default;
	union_find(const union_find &) = default;
	union_find(union_find&&) = default;

	union_find & operator=(const union_find &) = default;
	union_find & operator=(union_find &&) = default;

	union_find(size_type N): data(N, -1), comp_cnt(N) {}

	bool unite(size_type x, size_type y) {
		x = find(x); y = find(y);
		if(x == y) return false;
		if(data[x] > data[y]) std::swap(x, y);
		
		data[x] += data[y];
		data[y] = x;
		comp_cnt--;
		return true;
	}
	
	bool is_united(size_type x, size_type y) { return find(x) == find(y); }
	size_type size() const { return data.size(); }
	size_type size(size_type k) { return -data[find(k)]; }
	size_type comp(size_type k) { return find(k); };
	size_type count() const { return comp_cnt; }
	size_type operator[](size_type k) { return find(k); }
	
	void swap(union_find & r) {
		data.swap(r.data);
		std::swap(comp_cnt, r.comp_cnt);
	}
};
#line 5 "test/yosupo/unionfind.union_find.test.cpp"

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

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

