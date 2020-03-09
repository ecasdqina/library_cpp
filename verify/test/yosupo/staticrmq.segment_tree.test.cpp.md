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


# :heavy_check_mark: test/yosupo/staticrmq.segment_tree.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/staticrmq.segment_tree.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-09 09:33:47+09:00


* see: <a href="https://judge.yosupo.jp/problem/staticrmq">https://judge.yosupo.jp/problem/staticrmq</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/data_structure/segment_tree.hpp.html">data_structure/segment_tree.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <stdio.h>
#include <algorithm>
#include "../../data_structure/segment_tree.hpp"

int main() {
	int n, q; scanf("%d%d", &n, &q);

	struct node {
		int x;

		node(int x = 1 << 30): x(x) {};
		node operator+(node r) const { return std::min(x, r.x); }
	};
	
	segment_tree<monoid<node>> seg(n);
	for(int i = 0; i < n; i++) {
		int a; scanf("%d", &a);

		seg.change(i, node(a));
	}

	while(q--) {
		int l, r; scanf("%d%d", &l, &r);

		printf("%d\n", seg.fold(l, r).x);
	}
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/staticrmq.segment_tree.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <stdio.h>
#include <algorithm>
#line 1 "test/yosupo/../../data_structure/segment_tree.hpp"
#include <cstdint>
#include <vector>
#include <functional>

template<class Monoid>
class segment_tree {
public:
	using T = typename Monoid::value_type;
	using size_type = std::uint_fast32_t;

	using updator = std::function<T(T)>;
	using checker = std::function<bool(T)>;
	
private:
	const size_type size_;
	size_type height_;

public:
	std::vector<T> data;
	
private:
	const size_type get_height(size_type size) const {
		size_type height = 1;
		while(1 << height <= size) height++;
		return height;
	}
	const size_type base_size() const { return 1 << height_; }

	void meld(size_type index) {
		data[index] = Monoid::operation(data[index << 1 ^ 0], data[index << 1 ^ 1]);
	}

public:
	segment_tree() = default;
	segment_tree(segment_tree&&) = default;
	segment_tree(const segment_tree&) = default;
	
	segment_tree(size_type size)
		: size_(size) {
		height_ = get_height(size);
		data.assign(base_size() << 1, T{});
	}
	T fold(size_type left, size_type right) {
		T l_value = T{};
		T r_value = T{};

		for(left += base_size(), right += base_size();
			left < right;
			left >>= 1, right >>= 1) {
			if(left & 1)  l_value = Monoid::operation(l_value, data[left++]);
			if(right & 1) r_value = Monoid::operation(data[--right], r_value); 
		}
		return Monoid::operation(std::move(l_value), std::move(r_value));
	}

	void update(size_type index, const updator& update) {
		index += base_size();
		data[index] = update(data[index]);

		while(index >>= 1) meld(index);
	}
	void update(size_type index, const T& value) { update(index, [&value](const T& x) { return Monoid::operation(x, value); }); }
	void change(size_type index, const T& value) { update(index, [&value](const T& x) { return value; }); }
	
	const size_type search(size_type left, const checker& check) {
		T val = T{};
		size_type k = left + base_size();
		while(true) {
			if(check(Monoid::operation(val, data[k]))) {
				val = Monoid::operation(val, data[k]);
				if(k & 1) {
					if((k + 1) & k) k = (k + 1) >> 1;
					else return size();
				} else {
					k = k + 1;
				}
			} else {
				if(k < base_size()) {
					k = k << 1 ^ 0;
				} else {
					return k - base_size();
				}
			}
		}
	}
	
	const T operator[](size_type index) const { return data[index + base_size()]; }
	const size_type size() const { return size_; }
	const bool empty() const { return data.empty(); }
};

template<class T>
struct monoid {
	using value_type = T;

	static value_type operation(const value_type& a, const value_type& b) { return a + b; };
};
#line 6 "test/yosupo/staticrmq.segment_tree.test.cpp"

int main() {
	int n, q; scanf("%d%d", &n, &q);

	struct node {
		int x;

		node(int x = 1 << 30): x(x) {};
		node operator+(node r) const { return std::min(x, r.x); }
	};
	
	segment_tree<monoid<node>> seg(n);
	for(int i = 0; i < n; i++) {
		int a; scanf("%d", &a);

		seg.change(i, node(a));
	}

	while(q--) {
		int l, r; scanf("%d%d", &l, &r);

		printf("%d\n", seg.fold(l, r).x);
	}
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

