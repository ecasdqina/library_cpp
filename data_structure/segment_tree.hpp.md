---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo/point_set_range_composite.segment_tree.test.cpp
    title: test/yosupo/point_set_range_composite.segment_tree.test.cpp
  - icon: ':x:'
    path: test/yosupo/vertex_add_path_sum.test.cpp
    title: test/yosupo/vertex_add_path_sum.test.cpp
  - icon: ':x:'
    path: test/yosupo/point_add_range_sum.segment_tree.test.cpp
    title: test/yosupo/point_add_range_sum.segment_tree.test.cpp
  - icon: ':x:'
    path: test/yosupo/vertex_add_subtree_sum.test.cpp
    title: test/yosupo/vertex_add_subtree_sum.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    _deprecated_at_docs: docs/segment_tree.md
    links: []
  bundledCode: "#line 2 \"data_structure/segment_tree.hpp\"\n\n#include <vector>\n\
    #include <cstdint>\n\nnamespace cplib {\n\ttemplate<class Monoid> class segment_tree\
    \ {\n\tpublic:\n\t\tusing value_type = Monoid;\n\t\tusing usize = std::uint_fast32_t;\n\
    \n\tprivate:\n\t\tint n;\n\t\tstd::vector<value_type> data;\n\n\tprivate:\n\t\t\
    usize base() const { return data.size() >> 1; }\n\n\tpublic:\n\t\tsegment_tree()\
    \ = default;\n\t\texplicit segment_tree(usize n): n(n) {\n\t\t\tusize size = 1;\n\
    \t\t\twhile(size <= n) size <<= 1;\n\t\t\tdata.assign(size << 1, value_type::identity);\n\
    \t\t}\n\t\texplicit segment_tree(const std::vector<value_type>& vec): segment_tree(vec.size())\
    \ {\n\t\t\tfor(usize i = 0; i < vec.size(); i++) set(i, vec[i]);\n\t\t\tbuild();\n\
    \t\t}\n\n\t\tusize size() const { return n; }\n\t\tvalue_type get(usize i) const\
    \ { return data[i + base()]; }\n\t\tvoid set(usize i, const value_type& x) { data[i\
    \ + base()] = x; }\n\n\t\tvoid build() {\n\t\t\tfor(usize i = (int)base() - 1;\
    \ i > 0; i--)\n\t\t\t\tdata[i] = value_type::operation(data[i * 2 + 0], data[i\
    \ * 2 + 1]);\n\t\t}\n\t\tvoid change(usize i, const value_type& x) {\n\t\t\tdata[i\
    \ += base()] = x;\n\t\t\twhile(i >>= 1) data[i] = value_type::operation(data[i\
    \ * 2 + 0], data[i * 2 + 1]);\n\t\t}\n\t\tvoid update(usize i, const value_type&\
    \ x) { change(i, value_type::operation(get(i), x)); }\n\n\t\tvalue_type fold(usize\
    \ first, usize last) const {\n\t\t\tfirst += base();\n\t\t\tlast += base();\n\n\
    \t\t\tvalue_type lval = value_type::identity;\n\t\t\tvalue_type rval = value_type::identity;\n\
    \t\t\twhile(first != last) {\n\t\t\t\tif(first & 1) lval = value_type::operation(lval,\
    \ data[first++]);\n\t\t\t\tif(last  & 1) rval = value_type::operation(data[--last],\
    \ rval);\n\t\t\t\tfirst >>= 1;\n\t\t\t\tlast  >>= 1;\n\t\t\t}\n\t\t\treturn value_type::operation(lval,\
    \ rval);\n\t\t}\n\t\tvalue_type fold_all() const { return data[1]; }\n\n\t\t//\
    \ return max{r | f(fold(l, r - 1)) = true}\n\t\ttemplate<class F> usize search_right(int\
    \ l, const F& f) const {\n\t\t\tif(l == size()) return base();\n\n\t\t\tl += base();\n\
    \t\t\tvalue_type acc = value_type::identity;\n\t\t\tdo {\n\t\t\t\twhile(l % 2\
    \ == 0) l >>= 1;\n\t\t\t\tif(!f(value_type::operation(acc, data[l]))) {\n\t\t\t\
    \t\twhile(l < base()) {\n\t\t\t\t\t\tl = l << 1;\n\t\t\t\t\t\tif(f(value_type::operation(acc,\
    \ data[l]))) {\n\t\t\t\t\t\t\tacc = value_type::operation(acc, data[l]);\n\t\t\
    \t\t\t\t\tl += 1;\n\t\t\t\t\t\t}\n\t\t\t\t\t}\n\t\t\t\t\treturn l - base();\n\t\
    \t\t\t}\n\t\t\t\tacc = value_type::operation(acc, data[l]);\n\t\t\t\tl += 1;\n\
    \t\t\t} while((l & -l) != l);\n\t\t\treturn size();\n\t\t}\n\n\t\t// return min{l\
    \ | f(fold(l, r - 1) = true}\n\t\ttemplate<class F> usize search_left(int r, const\
    \ F& f) const {\n\t\t\tif(r == 0) return 0;\n\n\t\t\tr += base();\n\t\t\tvalue_type\
    \ acc = value_type::identity;\n\t\t\tdo {\n\t\t\t\tr--;\n\t\t\t\twhile(r > 1 and\
    \ (r % 2)) r >>= 1;\n\t\t\t\tif(!f(value_type::operation(data[r], acc))) {\n\t\
    \t\t\t\twhile(r < base()) {\n\t\t\t\t\t\tr = r * 2 + 1;\n\t\t\t\t\t\tif(f(value_type::operation(data[r],\
    \ acc))) {\n\t\t\t\t\t\t\tacc = value_type::operation(data[r], acc);\n\t\t\t\t\
    \t\t\tr -= 1;\n\t\t\t\t\t\t}\n\t\t\t\t\t}\n\t\t\t\t\treturn r + 1 - base();\n\t\
    \t\t\t}\n\t\t\t\tacc = value_type::operation(data[r], acc);\n\t\t\t} while((r\
    \ & -r) == r);\n\t\t\treturn 0;\n\t\t}\n\t};\n\n\ttemplate<class T, T id = T{}>\n\
    \tstruct add_monoid {\n\t\tT a;\n\n\t\tstatic constexpr add_monoid operation(const\
    \ add_monoid& l, const add_monoid& r) { return add_monoid{l.a + r.a}; }\n\t\t\
    static constexpr add_monoid identity{id};\n\t};\n\n\ttemplate<class T, T id =\
    \ T{1}>\n\tstruct mul_monoid {\n\t\tT a;\n\n\t\tstatic constexpr mul_monoid operation(const\
    \ mul_monoid& l, const mul_monoid& r) { return mul_monoid{l.a * r.a}; }\n\t\t\
    static constexpr mul_monoid identity{id};\n\t};\n\n\ttemplate<class T, T id =\
    \ T{}>\n\tstruct max_monoid {\n\t\tT a;\n\n\t\tstatic constexpr max_monoid operation(const\
    \ max_monoid& l, const max_monoid& r) { return max_monoid{std::max(l.a, r.a)};\
    \ }\n\t\tstatic constexpr max_monoid identity{id};\n\t};\n\n\ttemplate<class T,\
    \ T id = T{}>\n\tstruct min_monoid {\n\t\tT a;\n\n\t\tstatic constexpr min_monoid\
    \ operation(const min_monoid& l, const min_monoid& r) { return min_monoid{std::min(l.a,\
    \ r.a)}; }\n\t\tstatic constexpr min_monoid identity{id};\n\t};\n}\n\n// @docs\
    \ docs/segment_tree.md\n"
  code: "#pragma once\n\n#include <vector>\n#include <cstdint>\n\nnamespace cplib\
    \ {\n\ttemplate<class Monoid> class segment_tree {\n\tpublic:\n\t\tusing value_type\
    \ = Monoid;\n\t\tusing usize = std::uint_fast32_t;\n\n\tprivate:\n\t\tint n;\n\
    \t\tstd::vector<value_type> data;\n\n\tprivate:\n\t\tusize base() const { return\
    \ data.size() >> 1; }\n\n\tpublic:\n\t\tsegment_tree() = default;\n\t\texplicit\
    \ segment_tree(usize n): n(n) {\n\t\t\tusize size = 1;\n\t\t\twhile(size <= n)\
    \ size <<= 1;\n\t\t\tdata.assign(size << 1, value_type::identity);\n\t\t}\n\t\t\
    explicit segment_tree(const std::vector<value_type>& vec): segment_tree(vec.size())\
    \ {\n\t\t\tfor(usize i = 0; i < vec.size(); i++) set(i, vec[i]);\n\t\t\tbuild();\n\
    \t\t}\n\n\t\tusize size() const { return n; }\n\t\tvalue_type get(usize i) const\
    \ { return data[i + base()]; }\n\t\tvoid set(usize i, const value_type& x) { data[i\
    \ + base()] = x; }\n\n\t\tvoid build() {\n\t\t\tfor(usize i = (int)base() - 1;\
    \ i > 0; i--)\n\t\t\t\tdata[i] = value_type::operation(data[i * 2 + 0], data[i\
    \ * 2 + 1]);\n\t\t}\n\t\tvoid change(usize i, const value_type& x) {\n\t\t\tdata[i\
    \ += base()] = x;\n\t\t\twhile(i >>= 1) data[i] = value_type::operation(data[i\
    \ * 2 + 0], data[i * 2 + 1]);\n\t\t}\n\t\tvoid update(usize i, const value_type&\
    \ x) { change(i, value_type::operation(get(i), x)); }\n\n\t\tvalue_type fold(usize\
    \ first, usize last) const {\n\t\t\tfirst += base();\n\t\t\tlast += base();\n\n\
    \t\t\tvalue_type lval = value_type::identity;\n\t\t\tvalue_type rval = value_type::identity;\n\
    \t\t\twhile(first != last) {\n\t\t\t\tif(first & 1) lval = value_type::operation(lval,\
    \ data[first++]);\n\t\t\t\tif(last  & 1) rval = value_type::operation(data[--last],\
    \ rval);\n\t\t\t\tfirst >>= 1;\n\t\t\t\tlast  >>= 1;\n\t\t\t}\n\t\t\treturn value_type::operation(lval,\
    \ rval);\n\t\t}\n\t\tvalue_type fold_all() const { return data[1]; }\n\n\t\t//\
    \ return max{r | f(fold(l, r - 1)) = true}\n\t\ttemplate<class F> usize search_right(int\
    \ l, const F& f) const {\n\t\t\tif(l == size()) return base();\n\n\t\t\tl += base();\n\
    \t\t\tvalue_type acc = value_type::identity;\n\t\t\tdo {\n\t\t\t\twhile(l % 2\
    \ == 0) l >>= 1;\n\t\t\t\tif(!f(value_type::operation(acc, data[l]))) {\n\t\t\t\
    \t\twhile(l < base()) {\n\t\t\t\t\t\tl = l << 1;\n\t\t\t\t\t\tif(f(value_type::operation(acc,\
    \ data[l]))) {\n\t\t\t\t\t\t\tacc = value_type::operation(acc, data[l]);\n\t\t\
    \t\t\t\t\tl += 1;\n\t\t\t\t\t\t}\n\t\t\t\t\t}\n\t\t\t\t\treturn l - base();\n\t\
    \t\t\t}\n\t\t\t\tacc = value_type::operation(acc, data[l]);\n\t\t\t\tl += 1;\n\
    \t\t\t} while((l & -l) != l);\n\t\t\treturn size();\n\t\t}\n\n\t\t// return min{l\
    \ | f(fold(l, r - 1) = true}\n\t\ttemplate<class F> usize search_left(int r, const\
    \ F& f) const {\n\t\t\tif(r == 0) return 0;\n\n\t\t\tr += base();\n\t\t\tvalue_type\
    \ acc = value_type::identity;\n\t\t\tdo {\n\t\t\t\tr--;\n\t\t\t\twhile(r > 1 and\
    \ (r % 2)) r >>= 1;\n\t\t\t\tif(!f(value_type::operation(data[r], acc))) {\n\t\
    \t\t\t\twhile(r < base()) {\n\t\t\t\t\t\tr = r * 2 + 1;\n\t\t\t\t\t\tif(f(value_type::operation(data[r],\
    \ acc))) {\n\t\t\t\t\t\t\tacc = value_type::operation(data[r], acc);\n\t\t\t\t\
    \t\t\tr -= 1;\n\t\t\t\t\t\t}\n\t\t\t\t\t}\n\t\t\t\t\treturn r + 1 - base();\n\t\
    \t\t\t}\n\t\t\t\tacc = value_type::operation(data[r], acc);\n\t\t\t} while((r\
    \ & -r) == r);\n\t\t\treturn 0;\n\t\t}\n\t};\n\n\ttemplate<class T, T id = T{}>\n\
    \tstruct add_monoid {\n\t\tT a;\n\n\t\tstatic constexpr add_monoid operation(const\
    \ add_monoid& l, const add_monoid& r) { return add_monoid{l.a + r.a}; }\n\t\t\
    static constexpr add_monoid identity{id};\n\t};\n\n\ttemplate<class T, T id =\
    \ T{1}>\n\tstruct mul_monoid {\n\t\tT a;\n\n\t\tstatic constexpr mul_monoid operation(const\
    \ mul_monoid& l, const mul_monoid& r) { return mul_monoid{l.a * r.a}; }\n\t\t\
    static constexpr mul_monoid identity{id};\n\t};\n\n\ttemplate<class T, T id =\
    \ T{}>\n\tstruct max_monoid {\n\t\tT a;\n\n\t\tstatic constexpr max_monoid operation(const\
    \ max_monoid& l, const max_monoid& r) { return max_monoid{std::max(l.a, r.a)};\
    \ }\n\t\tstatic constexpr max_monoid identity{id};\n\t};\n\n\ttemplate<class T,\
    \ T id = T{}>\n\tstruct min_monoid {\n\t\tT a;\n\n\t\tstatic constexpr min_monoid\
    \ operation(const min_monoid& l, const min_monoid& r) { return min_monoid{std::min(l.a,\
    \ r.a)}; }\n\t\tstatic constexpr min_monoid identity{id};\n\t};\n}\n\n// @docs\
    \ docs/segment_tree.md\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/segment_tree.hpp
  requiredBy: []
  timestamp: '2020-09-17 06:15:17+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo/point_set_range_composite.segment_tree.test.cpp
  - test/yosupo/vertex_add_path_sum.test.cpp
  - test/yosupo/point_add_range_sum.segment_tree.test.cpp
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