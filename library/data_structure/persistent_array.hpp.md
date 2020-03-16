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
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: data_structure/persistent_array.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/persistent_array.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-16 17:07:49+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

	node_ptr set(size_type idx, const T&& val, const node_ptr& t) {
		node_ptr ret = new node();
		if(t) {
			std::memcpy(ret->child, t->child, sizeof(t->child));
			ret->data = t->data;
		}

		if(!idx) ret->data = val;
		else ret->child[idx % K] = set(idx / K, std::forward(val), ret->child[idx % K]);
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

	size_type set(size_type idx, const T&& val, int time = -1) {
		if(time == -1) root.push_back(set(idx, std::forward(val), root.back()));
		else root.push_back(set(idx, std::forward(val), root[time]));
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/persistent_array.hpp"
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

	node_ptr set(size_type idx, const T&& val, const node_ptr& t) {
		node_ptr ret = new node();
		if(t) {
			std::memcpy(ret->child, t->child, sizeof(t->child));
			ret->data = t->data;
		}

		if(!idx) ret->data = val;
		else ret->child[idx % K] = set(idx / K, std::forward(val), ret->child[idx % K]);
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

	size_type set(size_type idx, const T&& val, int time = -1) {
		if(time == -1) root.push_back(set(idx, std::forward(val), root.back()));
		else root.push_back(set(idx, std::forward(val), root[time]));
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

