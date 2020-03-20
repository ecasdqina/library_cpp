#define PROBLEM "https://yukicoder.me/problems/no/901"

#include <functional>
#include "../../tree/heavy_light_decomposition.hpp"
#include "../../other/fast_io.hpp"

using i64 = std::int_fast64_t;

template<typename Monoid, typename OperatorMonoid = Monoid>
class lazy_segment_tree {
	using value_type = Monoid;
	using operator_type = OperatorMonoid;
	using size_type = size_t;

	using F = std::function<value_type (value_type, value_type)>;
	using G = std::function<value_type (value_type, operator_type, int, int)>;
	using H = std::function<operator_type (operator_type, operator_type)>;
	
	size_type size_;
	size_type height_;

	F f;
	G g;
	H h;
	value_type id;
	operator_type id_op;
	std::vector<value_type> data;
	std::vector<operator_type> lazy;
	std::vector<size_type> depth;
	
	const size_type get_height(const size_type& size) const {
		size_type height = 1;
		while(1 << height < size) height++;
		return height;
	}
	const size_type base_size() const {
		return 1 << height_;
	}
	const value_type reflect(const size_type & k) {
		if(lazy[k] == id_op) return data[k];
		return g(data[k], lazy[k], 0, 0);
	}
	void eval(const size_type & k) {
		if(lazy[k] == id_op) return;
		lazy[k << 1 ^ 0] = h(lazy[k << 1 ^ 0], lazy[k]);
		lazy[k << 1 ^ 1] = h(lazy[k << 1 ^ 1], lazy[k]);
		data[k] = reflect(k);
		lazy[k] = id_op;
	}
	void thrust(const size_type & k) {
		for(int i = height_; i; i--) eval(k >> i);
	}
	void recalc(size_type k) {
		while(k >>= 1) data[k] = f(reflect(k << 1 ^ 0), reflect(k << 1 ^ 1));
	}
	
	public:
	lazy_segment_tree() {}
	lazy_segment_tree(int n, const F & f, const G & g, const H & h, const value_type & id, const operator_type & id_op) :
		size_(n), f(f), g(g), h(h), id(id), id_op(id_op) {
		height_ = get_height(size_);
		data.assign(base_size() << 1, id);
		lazy.assign(base_size() << 1, id_op);
		depth.assign(base_size() << 1, 0);
		for(int i = 0; i < height_ + 1; i++)
			for(int j = (1 << i); j < (1 << (i + 1)); j++)
				depth[j] = i;
	}
	void update(size_type a, size_type b, operator_type x) {
		thrust(a += base_size());
		thrust(b += base_size() - 1);
		for(size_type l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
			if(l & 1) lazy[l] = h(lazy[l], x), l++;
			if(r & 1) --r, lazy[r] = h(lazy[r], x);
		}
		recalc(a);
		recalc(b);
	}
	void change(size_type k, const value_type x) {
		thrust(k += base_size());
		data[k] = x;
		lazy[k] = id_op;
		recalc(k);
	}
	const value_type fold(size_type a, size_type b) {
		thrust(a += base_size());
		thrust(b += base_size() - 1);

		value_type left_value = id;
		value_type right_value = id;
		for(size_type l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
			if(l & 1) left_value = f(left_value, reflect(l++));
			if(r & 1) right_value = f(reflect(--r), right_value);
		}
		return f(left_value, right_value);
	}

	const value_type operator[](const size_type & k) {
		return fold(k, k + 1);
	}
};

struct node {
	int v, v_all;
	
	node() : v(-1), v_all(-1) {}
	node(int v_all) : v(-1), v_all(v_all) {}
	node(int v, int v_all) : v(v), v_all(v_all) {}
};

std::vector<int> depth;
constexpr int dep(const int & k) { return (k < 0 ? -1 : depth[k]); };

int main() {
	int n; fin.scan(n);
	std::vector<std::vector<std::pair<int, i64>>> g(n);
	heavy_light_decomposition hld(n);
	for(int i = 0; i < n - 1; i++) {
		int a, b, c; fin.scan(a, b, c);

		g[a].push_back({b, c});
		g[b].push_back({a, c});
		hld.add_edge(a, b);
	}
	hld.build();

	depth.assign(n, 0);
	std::vector<i64> dist(n);
	auto dfs = [&](auto && dfs, int v, int par) -> void {
		for(auto e: g[v]) {
			if(e.first == par) continue;
			dist[e.first] = dist[v] + e.second;
			depth[e.first] = depth[v] + 1;
			dfs(dfs, e.first, v);
		}
	};
	dfs(dfs, 0, -1);
	
	auto calc = [dist, &hld](int u, int v) { return dist[u] + dist[v] - 2LL * dist[hld.lca(u, v)]; };
	auto f = [&](node a, node b) {
		return node(
				(dep(a.v) < dep(b.v) ? b.v : a.v),
				(dep(a.v_all) < dep(b.v_all) ? b.v_all : a.v_all));
	};
	auto g_ = [](node a, int b, int l, int r) {
		return node(
				(b ? a.v_all : -1),
				a.v_all);
	};
	auto h = [](int a, int b) { return b; };
	
	lazy_segment_tree<node, int> A(n, f, g_, h,  node(), -1);
	for(int i = 0; i < n; i++) A.change(hld[i], node(i));
	auto kiri = [&A](int l, int r) { A.update(l, r, 1); };
	auto irik = [&A](int l, int r) { A.update(l, r, 0); };

	int q; fin.scan(q);
	while(q--) {
		int k; fin.scan(k);
				
		i64 ans = 0;
		int c; fin.scan(c);
		for(int i = 1; i < k; i++) {
			int v; fin.scan(v);
			node tmp = node();
			auto tanpo = [&](int l, int r) { tmp = f(tmp, A.fold(l, r)); };
			hld.path(0, v, tanpo);
			
			int u = (tmp.v == -1 ? c : tmp.v);
			hld.path(u, v, kiri);
			c = hld.lca(v, c);
			ans += calc(v, u);
		}

		A.update(0, n, 0);
		fout.println(ans);
	}
	return 0;
}

