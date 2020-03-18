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


# :heavy_check_mark: test/yosupo/vertex_add_subtree_sum.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0b58406058f6619a0f31a172defc0230">test/yosupo</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/vertex_add_subtree_sum.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-18 17:46:43+09:00


* see: <a href="https://judge.yosupo.jp/problem/vertex_add_subtree_sum">https://judge.yosupo.jp/problem/vertex_add_subtree_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/data_structure/segment_tree.hpp.html">data_structure/segment_tree.hpp</a>
* :heavy_check_mark: <a href="../../../library/tree/heavy_light_decomposition.hpp.html">tree/heavy_light_decomposition.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include <stdio.h>
#include "../../data_structure/segment_tree.hpp"
#include "../../tree/heavy_light_decomposition.hpp"

using i64 = std::int_fast64_t;

int main() {
	int n, q; scanf("%d%d", &n, &q); std::vector<int> a(n);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);

	heavy_light_decomposition hld(n);
	for(int i = 1; i < n; i++) {
		int p; scanf("%d", &p);

		hld.add_edge(p, i);
	}
	hld.build();
	
	segment_tree<monoid<i64>> seg(n);
	for(int i = 0; i < n; i++) seg.change(hld[i], a[i]);
	while(q--) {
		int type; scanf("%d", &type);
		
		if(type == 0) {
			int x, y; scanf("%d%d", &x, &y);
			
			seg.update(hld[x], y);
		} if(type == 1) {
			int v; scanf("%d", &v);
			
			i64 ans = 0;
			auto p = [&](int l, int r) { ans += seg.fold(l, r); };
			hld.subtree(v, p);
			
			printf("%lld\n", ans);
		}
	}
	return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/vertex_add_subtree_sum.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include <stdio.h>
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

// @docs docs/segment_tree.md


#line 1 "test/yosupo/../../tree/heavy_light_decomposition.hpp"



#line 7 "test/yosupo/../../tree/heavy_light_decomposition.hpp"

class heavy_light_decomposition {
public:
	using i32 = std::int_fast32_t;
	using u32 = std::uint_fast32_t;

	using processor = std::function<void(u32, u32)>;

	std::vector<std::vector<u32>> g;
	std::vector<u32> edge_u, edge_v, size, et, in, out, head;
	std::vector<i32> parent, heavy;

private:
	void calc_size(u32 v) {
		size[v] = 1;
		for(int id: g[v]) {
			int to = edge_u[id] ^ edge_v[id] ^ v;
			if(to == parent[v]) continue;
			parent[to] = v;
			calc_size(to);
			size[v] += size[to];

			if(heavy[v] == -1 or size[heavy[v]] < size[to]) heavy[v] = to;
		}
	}
	void calc_et(u32 v) {
		in[v] = et.size();
		et.push_back(v);
		if(heavy[v] != -1) {
			head[heavy[v]] = head[v];
			calc_et(heavy[v]);
		}
		for(int id: g[v]) {	
			int to = edge_u[id] ^ edge_v[id] ^ v;
			if(to == parent[v] or to == heavy[v]) continue;
			head[to] = to;
			calc_et(to);
		}
		out[v] = et.size();
	}

	void path(i32 x, i32 y, const processor& process, bool edge) const {
		std::vector<std::pair<u32, u32>> l, r;
		while(true) {
			if(in[x] > in[y]) {
				std::swap(x, y);
				l.swap(r);
			}

			if(head[x] == head[y]) {
				l.emplace_back(in[x] + !!edge, in[y] + 1);
				break;
			}
			l.emplace_back(in[head[y]], in[y] + 1);
			y = parent[head[y]];
		}

		for(auto e: l) process(e.first, e.second);
		for(auto e: r) process(e.first, e.second);
	}
	void subtree(u32 v, const processor& process, bool edge) const {
		process(in[v] + !!edge, out[v]);
	}

public:
	heavy_light_decomposition() = default;
	heavy_light_decomposition(heavy_light_decomposition&&) = default;
	heavy_light_decomposition(const heavy_light_decomposition &) = default;

	heavy_light_decomposition(int n)
		: g(n), size(n), in(n), out(n), parent(n, -1), heavy(n, -1), head(n) {}

	void add_edge(int x, int y) {
		g[x].push_back(edge_u.size());
		g[y].push_back(edge_v.size());
		edge_u.push_back(x);
		edge_v.push_back(y);
	}
	void build(u32 root = 0) {
		calc_size(root);
		calc_et(root);
	}

	u32 lca(u32 x, u32 y) const {
		while(true) {
			if(in[x] > in[y]) std::swap(x, y);
			if(head[x] == head[y]) return x;
			y = parent[head[y]];
		}
	}
	
	void path_node(u32 x, u32 y, const processor& process) const { path(x, y, process, false); }
	void path_edge(u32 x, u32 y, const processor& process) const { path(x, y, process, true); }
	void path(u32 x, u32 y, const processor& process) const { path(x, y, process, false); }

	void subtree_node(u32 v, const processor& process) const { subtree(v, process, false); }
	void subtree_edge(u32 v, const processor& process) const { subtree(v, process, true); }
	void subtree(u32 v, const processor& process) const { subtree(v, process, false); }

	u32 index_node(u32 v) const { return in[v]; };
	u32 index_edge(u32 x, u32 y) const { return std::max(in[x], in[y]); };
	u32 index(u32 v) const { return in[v]; };
	
	const u32 operator[](u32 k) const { return in[k]; }
};


#line 6 "test/yosupo/vertex_add_subtree_sum.test.cpp"

using i64 = std::int_fast64_t;

int main() {
	int n, q; scanf("%d%d", &n, &q); std::vector<int> a(n);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);

	heavy_light_decomposition hld(n);
	for(int i = 1; i < n; i++) {
		int p; scanf("%d", &p);

		hld.add_edge(p, i);
	}
	hld.build();
	
	segment_tree<monoid<i64>> seg(n);
	for(int i = 0; i < n; i++) seg.change(hld[i], a[i]);
	while(q--) {
		int type; scanf("%d", &type);
		
		if(type == 0) {
			int x, y; scanf("%d%d", &x, &y);
			
			seg.update(hld[x], y);
		} if(type == 1) {
			int v; scanf("%d", &v);
			
			i64 ans = 0;
			auto p = [&](int l, int r) { ans += seg.fold(l, r); };
			hld.subtree(v, p);
			
			printf("%lld\n", ans);
		}
	}
	return 0;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

