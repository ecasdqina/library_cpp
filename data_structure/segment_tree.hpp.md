---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: data_structure/affine.hpp
    title: data_structure/affine.hpp
  - icon: ':question:'
    path: data_structure/monoid.hpp
    title: data_structure/monoid.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/point_add_range_sum.segment_tree.test.cpp
    title: test/yosupo/point_add_range_sum.segment_tree.test.cpp
  - icon: ':x:'
    path: test/yosupo/point_set_range_composite.segment_tree.test.cpp
    title: test/yosupo/point_set_range_composite.segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/vertex_add_path_sum.test.cpp
    title: test/yosupo/vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/vertex_add_subtree_sum.test.cpp
    title: test/yosupo/vertex_add_subtree_sum.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    _deprecated_at_docs: docs/segment_tree.md
    links: []
  bundledCode: "#line 2 \"data_structure/segment_tree.hpp\"\n\n#include <vector>\n\
    #include <cstdint>\n\n#line 2 \"data_structure/monoid.hpp\"\n\n#include <algorithm>\n\
    #include <limits>\n#line 2 \"data_structure/affine.hpp\"\n\n#line 4 \"data_structure/affine.hpp\"\
    \n\nnamespace cplib {\ntemplate<class T> struct affine {\n\tusing value_type =\
    \ T;\n\n\tvalue_type a;\n\tvalue_type b;\n\n\tconstexpr affine(const value_type&\
    \ a = 1, const value_type& b = 0): a(a), b(b) {}\n\tconstexpr affine operator+(const\
    \ affine& r) const { return affine{a + r.a, b + r.b}; }\n\tconstexpr affine composite(const\
    \ affine& r) const { return affine{a * r.a, a * r.b + b}; }\n\n\tconstexpr value_type\
    \ evaluate(const value_type& x) { return a * x + b; }\n};\n}\n#line 6 \"data_structure/monoid.hpp\"\
    \n\nnamespace cplib {\ntemplate<class T, T id = T{}> struct add_monoid {\n\tusing\
    \ value_type = T;\n\n\tT a;\n\n\tconstexpr add_monoid(T a): a(a) {}\n\tstatic\
    \ constexpr add_monoid operation(const add_monoid& l, const add_monoid& r) { return\
    \ add_monoid{l.a + r.a}; }\n\tstatic constexpr add_monoid identity() { return\
    \ add_monoid{id}; };\n\tstatic constexpr add_monoid inverse(const add_monoid&\
    \ x) { return add_monoid{-x.a}; }\n};\n\ntemplate<class T, T id = T{1}> struct\
    \ mul_monoid {\n\tusing value_type = T;\n\n\tT a;\n\n\tconstexpr mul_monoid(T\
    \ a): a(a) {}\n\tstatic constexpr mul_monoid operation(const mul_monoid& l, const\
    \ mul_monoid& r) { return mul_monoid{l.a * r.a}; }\n\tstatic constexpr mul_monoid\
    \ identity() { return mul_monoid{id}; };\n};\n\ntemplate<class T, T id = T{}>\
    \ struct max_monoid {\n\tusing value_type = T;\n\n\tT a;\n\n\tconstexpr max_monoid(T\
    \ a): a(a) {}\n\tstatic constexpr max_monoid operation(const max_monoid& l, const\
    \ max_monoid& r) { return max_monoid{std::max(l.a, r.a)}; }\n\tstatic constexpr\
    \ max_monoid identity() { return max_monoid{id}; };\n};\n\ntemplate<class T, T\
    \ id = std::numeric_limits<T>::max()> struct min_monoid {\n\tusing value_type\
    \ = T;\n\n\tT a;\n\n\tconstexpr min_monoid(T a): a(a) {}\n\tstatic constexpr min_monoid\
    \ operation(const min_monoid& l, const min_monoid& r) { return min_monoid{std::min(l.a,\
    \ r.a)}; }\n\tstatic constexpr min_monoid identity() { return min_monoid{id};\
    \ };\n};\n\ntemplate<class T, T& id> struct monoid {\n\tusing value_type = T;\n\
    \n\tT a;\n\n\tconstexpr monoid(T a): a(a) {}\n\tstatic constexpr monoid operation(const\
    \ monoid& l, const monoid& r) { return monoid{l.a + r.a}; }\n\tstatic constexpr\
    \ monoid identity() { return monoid{id}; }\n\tstatic constexpr monoid inverse(const\
    \ monoid& x) { return monoid{x.a.inverse()}; }\n};\n\ntemplate<class A, class\
    \ B> struct cartesian_product_monoid {\n\tusing value_type = std::pair<typename\
    \ A::value_type, typename B::value_type>;\n\n\tvalue_type a;\n\n\tconstexpr cartesian_product_monoid(const\
    \ value_type& a): a(a) {}\n\tstatic constexpr cartesian_product_monoid operation(const\
    \ cartesian_product_monoid& l, const cartesian_product_monoid& r) {\n\t\treturn\
    \ cartesian_product_monoid{{A::operation(l.a.first, r.a.first).a, B::operation(l.a.second,\
    \ r.a.second).a}};\n\t}\n\tstatic constexpr cartesian_product_monoid identity()\
    \ { return cartesian_product_monoid{{A::identity().a, B::identity().a}}; }\n\t\
    static constexpr cartesian_product_monoid inverse(const cartesian_product_monoid&\
    \ x) {\n\t\treturn cartesian_product_monoid{{A::inverse(x.a.first).a, B::inverse(x.a.second).a}};\n\
    \t}\n};\n\ntemplate<class T> struct affine_composite_monoid {\n\tusing value_type\
    \ = cplib::affine<T>;\n\n\tvalue_type a;\n\n\tconstexpr affine_composite_monoid(const\
    \ value_type& a): a(a) {}\n\tstatic constexpr affine_composite_monoid operation(const\
    \ affine_composite_monoid& l,\n\t\t\t\t\t\t\t\t\t\t\t\t\t   const affine_composite_monoid&\
    \ r) {\n\t\treturn affine_composite_monoid{r.a.composite(l.a)};\n\t}\n\tstatic\
    \ constexpr affine_composite_monoid identity() {\n\t\treturn affine_composite_monoid{value_type()};\n\
    \t}\n};\n}\n#line 7 \"data_structure/segment_tree.hpp\"\n\nnamespace cplib {\n\
    template<class Monoid> class segment_tree {\npublic:\n\tusing value_type = Monoid;\n\
    \tusing T = typename value_type::value_type;\n\tusing usize = std::uint_fast32_t;\n\
    \nprivate:\n\tint n;\n\tstd::vector<value_type> data;\n\nprivate:\n\tusize base()\
    \ const { return data.size() >> 1; }\n\npublic:\n\tsegment_tree() = default;\n\
    \texplicit segment_tree(usize n): n(n) {\n\t\tusize size = 1;\n\t\twhile(size\
    \ <= n) size <<= 1;\n\t\tdata.assign(size << 1, value_type::identity());\n\t}\n\
    \ttemplate<class InputIt> explicit segment_tree(InputIt first, InputIt last)\n\
    \t: segment_tree(std::distance(first, last)) {\n\t\tfor(int index = 0; first !=\
    \ last; first++, index++) set(index, *first);\n\t\tbuild();\n\t}\n\n\tusize size()\
    \ const { return n; }\n\tbool empty() const { return size() == 0; }\n\tvoid clear()\
    \ {\n\t\tn = 0;\n\t\tdata.clear();\n\t}\n\tvoid swap(segment_tree& r) {\n\t\t\
    std::swap(n, r.n);\n\t\tdata.swap(r.data);\n\t}\n\n\tT get(usize i) const { return\
    \ data[i + base()].a; }\n\tvoid set(usize i, const value_type& x) { data[i + base()]\
    \ = x; }\n\n\tvoid build() {\n\t\tfor(usize i = (int)base() - 1; i > 0; i--)\n\
    \t\t\tdata[i] = value_type::operation(data[i * 2 + 0], data[i * 2 + 1]);\n\t}\n\
    \tvoid change(usize i, const value_type& x) {\n\t\tdata[i += base()] = x;\n\t\t\
    while(i >>= 1) data[i] = value_type::operation(data[i * 2 + 0], data[i * 2 + 1]);\n\
    \t}\n\tvoid update(usize i, const value_type& x) { change(i, value_type::operation(get(i),\
    \ x)); }\n\n\tT fold(usize first, usize last) const {\n\t\tfirst += base();\n\t\
    \tlast += base();\n\n\t\tvalue_type lval = value_type::identity();\n\t\tvalue_type\
    \ rval = value_type::identity();\n\t\twhile(first != last) {\n\t\t\tif(first &\
    \ 1) lval = value_type::operation(lval, data[first++]);\n\t\t\tif(last  & 1) rval\
    \ = value_type::operation(data[--last], rval);\n\t\t\tfirst >>= 1;\n\t\t\tlast\
    \  >>= 1;\n\t\t}\n\t\treturn value_type::operation(lval, rval).a;\n\t}\n\tT fold_all()\
    \ const { return data[1].a; }\n\n\t// return max{r | f(fold(l, r - 1)) = true}\n\
    \ttemplate<class F> usize search_right(int l, const F& f) const {\n\t\tif(l ==\
    \ size()) return base();\n\n\t\tl += base();\n\t\tvalue_type acc = value_type::identity();\n\
    \t\tdo {\n\t\t\twhile(l % 2 == 0) l >>= 1;\n\t\t\tif(!f(value_type::operation(acc,\
    \ data[l]).a)) {\n\t\t\t\twhile(l < base()) {\n\t\t\t\t\tl = l << 1;\n\t\t\t\t\
    \tif(f(value_type::operation(acc, data[l]).a)) {\n\t\t\t\t\t\tacc = value_type::operation(acc,\
    \ data[l]);\n\t\t\t\t\t\tl += 1;\n\t\t\t\t\t}\n\t\t\t\t}\n\t\t\t\treturn l - base();\n\
    \t\t\t}\n\t\t\tacc = value_type::operation(acc, data[l]);\n\t\t\tl += 1;\n\t\t\
    } while((l & -l) != l);\n\t\treturn size();\n\t}\n\n\t// return min{l | f(fold(l,\
    \ r - 1) = true}\n\ttemplate<class F> usize search_left(int r, const F& f) const\
    \ {\n\t\tif(r == 0) return 0;\n\n\t\tr += base();\n\t\tvalue_type acc = value_type::identity();\n\
    \t\tdo {\n\t\t\tr--;\n\t\t\twhile(r > 1 and (r % 2)) r >>= 1;\n\t\t\tif(!f(value_type::operation(data[r],\
    \ acc).a)) {\n\t\t\t\twhile(r < base()) {\n\t\t\t\t\tr = r * 2 + 1;\n\t\t\t\t\t\
    if(f(value_type::operation(data[r], acc).a)) {\n\t\t\t\t\t\tacc = value_type::operation(data[r],\
    \ acc);\n\t\t\t\t\t\tr -= 1;\n\t\t\t\t\t}\n\t\t\t\t}\n\t\t\t\treturn r + 1 - base();\n\
    \t\t\t}\n\t\t\tacc = value_type::operation(data[r], acc);\n\t\t} while((r & -r)\
    \ == r);\n\t\treturn 0;\n\t}\n};\n}\n\n// @docs docs/segment_tree.md\n"
  code: "#pragma once\n\n#include <vector>\n#include <cstdint>\n\n#include \"../data_structure/monoid.hpp\"\
    \n\nnamespace cplib {\ntemplate<class Monoid> class segment_tree {\npublic:\n\t\
    using value_type = Monoid;\n\tusing T = typename value_type::value_type;\n\tusing\
    \ usize = std::uint_fast32_t;\n\nprivate:\n\tint n;\n\tstd::vector<value_type>\
    \ data;\n\nprivate:\n\tusize base() const { return data.size() >> 1; }\n\npublic:\n\
    \tsegment_tree() = default;\n\texplicit segment_tree(usize n): n(n) {\n\t\tusize\
    \ size = 1;\n\t\twhile(size <= n) size <<= 1;\n\t\tdata.assign(size << 1, value_type::identity());\n\
    \t}\n\ttemplate<class InputIt> explicit segment_tree(InputIt first, InputIt last)\n\
    \t: segment_tree(std::distance(first, last)) {\n\t\tfor(int index = 0; first !=\
    \ last; first++, index++) set(index, *first);\n\t\tbuild();\n\t}\n\n\tusize size()\
    \ const { return n; }\n\tbool empty() const { return size() == 0; }\n\tvoid clear()\
    \ {\n\t\tn = 0;\n\t\tdata.clear();\n\t}\n\tvoid swap(segment_tree& r) {\n\t\t\
    std::swap(n, r.n);\n\t\tdata.swap(r.data);\n\t}\n\n\tT get(usize i) const { return\
    \ data[i + base()].a; }\n\tvoid set(usize i, const value_type& x) { data[i + base()]\
    \ = x; }\n\n\tvoid build() {\n\t\tfor(usize i = (int)base() - 1; i > 0; i--)\n\
    \t\t\tdata[i] = value_type::operation(data[i * 2 + 0], data[i * 2 + 1]);\n\t}\n\
    \tvoid change(usize i, const value_type& x) {\n\t\tdata[i += base()] = x;\n\t\t\
    while(i >>= 1) data[i] = value_type::operation(data[i * 2 + 0], data[i * 2 + 1]);\n\
    \t}\n\tvoid update(usize i, const value_type& x) { change(i, value_type::operation(get(i),\
    \ x)); }\n\n\tT fold(usize first, usize last) const {\n\t\tfirst += base();\n\t\
    \tlast += base();\n\n\t\tvalue_type lval = value_type::identity();\n\t\tvalue_type\
    \ rval = value_type::identity();\n\t\twhile(first != last) {\n\t\t\tif(first &\
    \ 1) lval = value_type::operation(lval, data[first++]);\n\t\t\tif(last  & 1) rval\
    \ = value_type::operation(data[--last], rval);\n\t\t\tfirst >>= 1;\n\t\t\tlast\
    \  >>= 1;\n\t\t}\n\t\treturn value_type::operation(lval, rval).a;\n\t}\n\tT fold_all()\
    \ const { return data[1].a; }\n\n\t// return max{r | f(fold(l, r - 1)) = true}\n\
    \ttemplate<class F> usize search_right(int l, const F& f) const {\n\t\tif(l ==\
    \ size()) return base();\n\n\t\tl += base();\n\t\tvalue_type acc = value_type::identity();\n\
    \t\tdo {\n\t\t\twhile(l % 2 == 0) l >>= 1;\n\t\t\tif(!f(value_type::operation(acc,\
    \ data[l]).a)) {\n\t\t\t\twhile(l < base()) {\n\t\t\t\t\tl = l << 1;\n\t\t\t\t\
    \tif(f(value_type::operation(acc, data[l]).a)) {\n\t\t\t\t\t\tacc = value_type::operation(acc,\
    \ data[l]);\n\t\t\t\t\t\tl += 1;\n\t\t\t\t\t}\n\t\t\t\t}\n\t\t\t\treturn l - base();\n\
    \t\t\t}\n\t\t\tacc = value_type::operation(acc, data[l]);\n\t\t\tl += 1;\n\t\t\
    } while((l & -l) != l);\n\t\treturn size();\n\t}\n\n\t// return min{l | f(fold(l,\
    \ r - 1) = true}\n\ttemplate<class F> usize search_left(int r, const F& f) const\
    \ {\n\t\tif(r == 0) return 0;\n\n\t\tr += base();\n\t\tvalue_type acc = value_type::identity();\n\
    \t\tdo {\n\t\t\tr--;\n\t\t\twhile(r > 1 and (r % 2)) r >>= 1;\n\t\t\tif(!f(value_type::operation(data[r],\
    \ acc).a)) {\n\t\t\t\twhile(r < base()) {\n\t\t\t\t\tr = r * 2 + 1;\n\t\t\t\t\t\
    if(f(value_type::operation(data[r], acc).a)) {\n\t\t\t\t\t\tacc = value_type::operation(data[r],\
    \ acc);\n\t\t\t\t\t\tr -= 1;\n\t\t\t\t\t}\n\t\t\t\t}\n\t\t\t\treturn r + 1 - base();\n\
    \t\t\t}\n\t\t\tacc = value_type::operation(data[r], acc);\n\t\t} while((r & -r)\
    \ == r);\n\t\treturn 0;\n\t}\n};\n}\n\n// @docs docs/segment_tree.md\n"
  dependsOn:
  - data_structure/monoid.hpp
  - data_structure/affine.hpp
  isVerificationFile: false
  path: data_structure/segment_tree.hpp
  requiredBy: []
  timestamp: '2020-09-27 04:15:30+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/yosupo/point_set_range_composite.segment_tree.test.cpp
  - test/yosupo/point_add_range_sum.segment_tree.test.cpp
  - test/yosupo/vertex_add_path_sum.test.cpp
  - test/yosupo/vertex_add_subtree_sum.test.cpp
documentation_of: data_structure/segment_tree.hpp
layout: document
redirect_from:
- /library/data_structure/segment_tree.hpp
- /library/data_structure/segment_tree.hpp.html
title: data_structure/segment_tree.hpp
---
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