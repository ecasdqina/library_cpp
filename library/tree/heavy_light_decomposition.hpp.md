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


# :heavy_check_mark: tree/heavy_light_decomposition.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c0af77cf8294ff93a5cdb2963ca9f038">tree</a>
* <a href="{{ site.github.repository_url }}/blob/master/tree/heavy_light_decomposition.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-09 05:32:49+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/2667.test.cpp.html">test/aoj/2667.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yukicoder/901.test.cpp.html">test/yukicoder/901.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cstdint>
#include <vector>

class heavy_light_decomposition {
public:
	using i32 = std::int_fast32_t;
	using u32 = std::uint_fast32_t;

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

	template<class F>
	void path(i32 x, i32 y, F& process, bool edge) const {
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
	template<class F>
	void subtree(u32 v, F& process, bool edge) const {
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
	
	template<class F>
	void path_node(u32 x, u32 y, const F& process) const { path(x, y, process, false); }
	template<class F>
	void path_edge(u32 x, u32 y, const F& process) const { path(x, y, process, true); }
	template<class F>
	void path(u32 x, u32 y, const F& process) const { path(x, y, process, false); }

	template<class F>
	void subtree_node(u32 v, const F& process) const { subtree(v, process, false); }
	template<class F>
	void subtree_edge(u32 v, const F& process) const { subtree(v, process, true); }
	template<class F>
	void subtree(u32 v, const F& process) const { subtree(v, process, false); }

	u32 index_node(u32 v) const { return in[v]; };
	u32 index_edge(u32 x, u32 y) const { return std::max(in[x], in[y]); };
	u32 index(u32 v) const { return in[v]; };
	
	const u32 operator[](u32 k) const { return in[k]; }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "tree/heavy_light_decomposition.hpp"
#include <cstdint>
#include <vector>

class heavy_light_decomposition {
public:
	using i32 = std::int_fast32_t;
	using u32 = std::uint_fast32_t;

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

	template<class F>
	void path(i32 x, i32 y, F& process, bool edge) const {
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
	template<class F>
	void subtree(u32 v, F& process, bool edge) const {
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
	
	template<class F>
	void path_node(u32 x, u32 y, const F& process) const { path(x, y, process, false); }
	template<class F>
	void path_edge(u32 x, u32 y, const F& process) const { path(x, y, process, true); }
	template<class F>
	void path(u32 x, u32 y, const F& process) const { path(x, y, process, false); }

	template<class F>
	void subtree_node(u32 v, const F& process) const { subtree(v, process, false); }
	template<class F>
	void subtree_edge(u32 v, const F& process) const { subtree(v, process, true); }
	template<class F>
	void subtree(u32 v, const F& process) const { subtree(v, process, false); }

	u32 index_node(u32 v) const { return in[v]; };
	u32 index_edge(u32 x, u32 y) const { return std::max(in[x], in[y]); };
	u32 index(u32 v) const { return in[v]; };
	
	const u32 operator[](u32 k) const { return in[k]; }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

