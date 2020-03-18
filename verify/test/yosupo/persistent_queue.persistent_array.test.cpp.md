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


# :heavy_check_mark: test/yosupo/persistent_queue.persistent_array.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0b58406058f6619a0f31a172defc0230">test/yosupo</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/persistent_queue.persistent_array.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-18 17:54:53+09:00


* see: <a href="https://judge.yosupo.jp/problem/persistent_queue">https://judge.yosupo.jp/problem/persistent_queue</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/data_structure/persistent_array.hpp.html">data_structure/persistent_array.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/persistent_queue.persistent_array.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/persistent_queue"

#include <stdio.h>
#line 1 "test/yosupo/../../data_structure/persistent_array.hpp"



#include <cstdint>
#include <cstring>
#include <vector>
#include <algorithm>

template<class T, std::uint_fast32_t K = 20>
class persistent_array {
	using u32 = std::uint_fast32_t;

public:
	using value_type = T;
	using size_type = u32;

private:
	struct node {
		T data;
		node* child[K];

		node() = default;
	};
	using node_ptr = node*;
	std::vector<node_ptr> root;

	void change(size_type idx, const T& val, node_ptr& t) {
		if(!t) t = new node();
		
		if(!idx) t->data = val;
		else change(idx / K, val, t->child[idx % K]);
	}
	node_ptr set(size_type idx, const T& val, const node_ptr& t) {
		node_ptr ret = new node();
		if(t) {
			std::memcpy(ret->child, t->child, sizeof(t->child));
			ret->data = t->data;
		}

		if(!idx) ret->data = val;
		else ret->child[idx % K] = set(idx / K, val, ret->child[idx % K]);
		return ret;
	}
	T get(size_type idx, const node_ptr& t) const {
		if(!t) return T{};
		if(idx == 0) return t->data;
		return get(idx / K, t->child[idx % K]);
	}

public:
	persistent_array(persistent_array&&) = default;
	persistent_array(const persistent_array &) = default;

	persistent_array(): root(1, nullptr) {}

	void change(size_type idx, const T& val, int time = -1) {
		if(time == -1) change(idx, val, root.back());
		else change(idx, val, root[time]);
	}
	size_type set(size_type idx, const T& val, int time = -1) {
		if(time == -1) root.push_back(set(idx, val, root.back()));
		else root.push_back(set(idx, val, root[time]));
		return root.size() - 1;
	}
	T get(size_type idx, int time = -1) const {
		if(time == -1) return get(idx, root.back());
		return get(idx, root[time]);
	}

	const T operator[](size_type k) const { return get(k); }
	bool empty() const { return (root.size() == 1 and root[0] == nullptr); }
	size_type now() const { return root.size() - 1; }
	void clear() { root.assign(1, nullptr); }
	void swap(const persistent_array& r) { root.swap(r.root); }
};


#line 5 "test/yosupo/persistent_queue.persistent_array.test.cpp"

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

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

