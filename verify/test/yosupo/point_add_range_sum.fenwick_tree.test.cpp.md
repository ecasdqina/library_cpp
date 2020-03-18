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


# :heavy_check_mark: test/yosupo/point_add_range_sum.fenwick_tree.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0b58406058f6619a0f31a172defc0230">test/yosupo</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/point_add_range_sum.fenwick_tree.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-18 17:46:43+09:00


* see: <a href="https://judge.yosupo.jp/problem/point_add_range_sum">https://judge.yosupo.jp/problem/point_add_range_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/data_structure/fenwick_tree.hpp.html">data_structure/fenwick_tree.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <stdio.h>
#include "../../data_structure/fenwick_tree.hpp"

int main() {
	int n, q; scanf("%d%d", &n, &q);
	fenwick_tree<monoid<std::int_fast64_t>> bit(n);
	for(int i = 0; i < n; i++) {
		int a; scanf("%d", &a);

		bit.change(i, a);
	}

	while(q--) {
		int type; scanf("%d", &type);

		if(type == 0) {
			int p, x; scanf("%d%d", &p, &x);

			bit.update(p, x);
		} else if(type == 1) {
			int l, r; scanf("%d%d", &l, &r);

			printf("%lld\n", bit.fold(l, r));
		}
	}
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/point_add_range_sum.fenwick_tree.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <stdio.h>
#line 1 "test/yosupo/../../data_structure/fenwick_tree.hpp"



#include <functional>
#include <vector>

template<class CommutativeMonoid>
class fenwick_tree {
public:
	using T = typename CommutativeMonoid::value_type;
	using size_type = std::uint_fast32_t;

	using checker = std::function<bool(T)>;

	std::vector<T> data;
	
private:
	size_type get_lsb(size_type i) const { return i & (~i + 1); }
	
public:
	fenwick_tree() = default;
	fenwick_tree(const fenwick_tree &) = default;
	fenwick_tree(fenwick_tree &&) = default;

	fenwick_tree(size_type size): data(size + 1, T{}) {}

	template<class InputIt>
	fenwick_tree(InputIt first, InputIt last) : fenwick_tree(std::distance(first, last)) {
		for(int index = 0; first != last; first++, index++) add(index, *first);
	}
	
	fenwick_tree & operator=(const fenwick_tree &) = default;
	fenwick_tree & operator=(fenwick_tree &&) = default;

	T fold(size_type last) const {
		T acc{};
		while(last) {
			acc = CommutativeMonoid::operation(data[last], acc);

			last -= get_lsb(last);
		}
		
		return acc;
	}
	T fold(size_type first, size_type last) const {
		T acc{};
		while(first < last) {
			acc = CommutativeMonoid::operation(data[last], acc);

			last -= get_lsb(last);
		}

		while(last < first) {
			acc = CommutativeMonoid::operation(CommutativeMonoid::inverse(data[first]), acc);

			first -= get_lsb(first);
		}
		
		return acc;
	}
	void update(size_type index, const T& value) {
		for(++index; index < data.size(); index += get_lsb(index)) {
			data[index] = CommutativeMonoid::operation(data[index], value);
		}
	}
	void change(size_type index, const T& value) {
		update(index, CommutativeMonoid::operation(CommutativeMonoid::inverse((*this)[index]), value));
	}

	// min{x | f(fold(x)) = true}
	template<class F>
	size_type search(const F & f) {
		if(f(T{})) return 0;

		T acc{};
		size_type i = 0, k = data.size();
		while(k >>= 1) {
			if((i | k) < data.size() and !f(CommutativeMonoid::operation(acc, data[i | k]))) {
				acc = CommutativeMonoid::operation(acc, data[i | k]);
				i |= k;
			}
		}
		return i + 1;
	}

	T operator[](const size_type& k) const { return fold(k, k + 1); };

	bool empty() const { return size() == 0; }
	size_type size() const { return data.size() - 1; }
	void swap(fenwick_tree & r) { data.swap(r.data); }
};

template<class T>
struct monoid {
	using value_type = T;

	static value_type operation(const value_type& a, const value_type& b) { return a + b; };
	static value_type inverse(const value_type& x) { return -x; }
};


#line 5 "test/yosupo/point_add_range_sum.fenwick_tree.test.cpp"

int main() {
	int n, q; scanf("%d%d", &n, &q);
	fenwick_tree<monoid<std::int_fast64_t>> bit(n);
	for(int i = 0; i < n; i++) {
		int a; scanf("%d", &a);

		bit.change(i, a);
	}

	while(q--) {
		int type; scanf("%d", &type);

		if(type == 0) {
			int p, x; scanf("%d%d", &p, &x);

			bit.update(p, x);
		} else if(type == 1) {
			int l, r; scanf("%d%d", &l, &r);

			printf("%lld\n", bit.fold(l, r));
		}
	}
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

