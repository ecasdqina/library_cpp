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
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"data_structure/lazy_segment_tree.hpp\"\n\n#include <vector>\n\
    #include <stack>\n#include <cstdint>\n\n#line 2 \"data_structure/monoid.hpp\"\n\
    \n#include <algorithm>\n#include <limits>\n#line 2 \"data_structure/affine.hpp\"\
    \n\n#line 4 \"data_structure/affine.hpp\"\n\nnamespace cplib {\ntemplate<class\
    \ T> struct affine {\n\tusing value_type = T;\n\n\tvalue_type a;\n\tvalue_type\
    \ b;\n\n\tconstexpr affine(const value_type& a = 1, const value_type& b = 0):\
    \ a(a), b(b) {}\n\tconstexpr affine operator+(const affine& r) const { return\
    \ affine{a + r.a, b + r.b}; }\n\tconstexpr affine composite(const affine& r) const\
    \ { return affine{a * r.a, a * r.b + b}; }\n\n\tconstexpr value_type evaluate(const\
    \ value_type& x) { return a * x + b; }\n};\n}\n#line 6 \"data_structure/monoid.hpp\"\
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
    \t}\n};\n}\n#line 8 \"data_structure/lazy_segment_tree.hpp\"\n\nnamespace cplib\
    \ {\ntemplate<class M, class E, class operation> class lazy_segment_tree {\npublic:\n\
    \tusing value_type \t= M;\n\tusing T \t\t\t= typename value_type::value_type;\n\
    \tusing operator_type = E;\n\tusing usize \t\t= std::uint_fast32_t;\n\n\tstruct\
    \ node_type {\n\t\tvalue_type value;\n\t\toperator_type lazy;\n\n\t\tnode_type(const\
    \ value_type& value, const operator_type& lazy): value(value), lazy(lazy) {}\n\
    \t};\n\nprivate:\n\tstd::vector<node_type> data;\n\n\tvalue_type value(const node_type&\
    \ x) const { return value_type{operation()(x.value.a, x.lazy.a)}; }\n\tusize countr_zeros(usize\
    \ x) const { return __builtin_ctzll(x); }\n\n\tvoid add(operator_type& l, const\
    \ operator_type& r) { l = operator_type::operation(l, r); }\n\n\tvoid propagate(usize\
    \ idx) {\n\t\tadd(data[idx * 2 + 0].lazy, data[idx].lazy);\n\t\tadd(data[idx *\
    \ 2 + 1].lazy, data[idx].lazy);\n\t\tdata[idx].lazy = operator_type::identity();\n\
    \t}\n\tvoid propagate_bound(usize idx) {\n\t\tif(idx == 0) return;\n\n\t\tstd::stack<usize>\
    \ order;\n\n\t\tidx >>= countr_zeros(idx);\n\t\twhile(idx >>= 1) order.push(idx);\n\
    \t\twhile(!order.empty()){\n\t\t\tpropagate(order.top());\n\t\t\torder.pop();\n\
    \t\t}\n\t}\n\n\tvoid recalc(usize idx) { data[idx].value = value_type::operation(value(data[idx\
    \ * 2 + 0]), value(data[idx * 2 + 1])); }\n\tvoid recalc_bound(usize idx) {\n\t\
    \tif(idx == 0) return;\n\n\t\tidx >>= countr_zeros(idx);\n\t\twhile(idx >>= 1)\
    \ recalc(idx);\n\t}\n\npublic:\n\tlazy_segment_tree() = default;\n\texplicit lazy_segment_tree(usize\
    \ n): data(n << 1, node_type(value_type::identity(), operator_type::identity()))\
    \ {}\n\ttemplate<class InputIt> explicit lazy_segment_tree(InputIt first, InputIt\
    \ last)\n\t: lazy_segment_tree(std::distance(first, last)) {\n\t\tfor(int index\
    \ = 0; first != last; first++, index++) set(index, *first);\n\t\tbuild();\n\t\
    }\n\tvoid build() { for(usize i = size() - 1; i > 0; i--) recalc(i); }\n\n\tusize\
    \ size() { return data.size() >> 1; }\n\tbool empty() { return size() == 0; }\n\
    \tvoid clear() { data.clear(); }\n\tvoid swap(lazy_segment_tree& r) { data.swap(r.data);\
    \ }\n\n\tT get(usize i) { return fold(i, i + 1); }\n\tvoid set(usize i, const\
    \ value_type& x) { data[i + size()].value = x; };\n\n\tvoid change(usize i, const\
    \ value_type& x) {\n\t\ti += size();\n\t\tpropagate_bound(((i >> 1) << 1) + 1);\n\
    \t\tdata[i] = node_type(x, operator_type::identity());\n\t\trecalc_bound(((i >>\
    \ 1) << 1) + 1);\n\t}\n\tvoid update(usize i, const value_type& x) {\n\t\ti +=\
    \ size();\n\t\tpropagate_bound(((i >> 1) << 1) + 1);\n\t\tdata[i] = node_type(value_type::operation(value(data[i]),\
    \ x), operator_type::identity());\n\t\trecalc_bound(((i >> 1) << 1) + 1);\n\t\
    }\n\n\tT fold(usize first, usize last) {\n\t\tfirst += size();\n\t\tlast  += size();\n\
    \t\tpropagate_bound(first);\n\t\trecalc_bound(first);\n\t\tpropagate_bound(last);\n\
    \t\trecalc_bound(last);\n\n\t\tvalue_type lval = value_type::identity();\n\t\t\
    value_type rval = value_type::identity();\n\t\twhile(first != last) {\n\t\t\t\
    if(first & 1) {\n\t\t\t\tlval = value_type::operation(lval, value(data[first]));\n\
    \t\t\t\tfirst++;\n\t\t\t}\n\t\t\tif(last  & 1) {\n\t\t\t\tlast--;\n\t\t\t\trval\
    \ = value_type::operation(value(data[last]), rval);\n\t\t\t}\n\t\t\tfirst >>=\
    \ 1;\n\t\t\tlast  >>= 1;\n\t\t}\n\t\treturn value_type::operation(lval, rval).a;\n\
    \t}\n\n\tvoid update(usize first, usize last, const operator_type& x) {\n\t\t\
    first += size();\n\t\tlast  += size();\n\t\tusize first_tmp = first;\n\t\tusize\
    \ last_tmp  = last;\n\t\tpropagate_bound(first);\n\t\tpropagate_bound(last);\n\
    \t\twhile(first != last) {\n\t\t\tif(first & 1) {\n\t\t\t\tadd(data[first].lazy,\
    \ x);\n\t\t\t\tfirst++;\n\t\t\t}\n\t\t\tif(last  & 1) {\n\t\t\t\tlast--;\n\t\t\
    \t\tadd(data[last].lazy, x);\n\t\t\t}\n\t\t\tfirst >>= 1;\n\t\t\tlast >>= 1;\n\
    \t\t}\n\t\trecalc_bound(first_tmp);\n\t\trecalc_bound(last_tmp);\n\t}\n};\n}\n"
  code: "#pragma once\n\n#include <vector>\n#include <stack>\n#include <cstdint>\n\
    \n#include \"../data_structure/monoid.hpp\"\n\nnamespace cplib {\ntemplate<class\
    \ M, class E, class operation> class lazy_segment_tree {\npublic:\n\tusing value_type\
    \ \t= M;\n\tusing T \t\t\t= typename value_type::value_type;\n\tusing operator_type\
    \ = E;\n\tusing usize \t\t= std::uint_fast32_t;\n\n\tstruct node_type {\n\t\t\
    value_type value;\n\t\toperator_type lazy;\n\n\t\tnode_type(const value_type&\
    \ value, const operator_type& lazy): value(value), lazy(lazy) {}\n\t};\n\nprivate:\n\
    \tstd::vector<node_type> data;\n\n\tvalue_type value(const node_type& x) const\
    \ { return value_type{operation()(x.value.a, x.lazy.a)}; }\n\tusize countr_zeros(usize\
    \ x) const { return __builtin_ctzll(x); }\n\n\tvoid add(operator_type& l, const\
    \ operator_type& r) { l = operator_type::operation(l, r); }\n\n\tvoid propagate(usize\
    \ idx) {\n\t\tadd(data[idx * 2 + 0].lazy, data[idx].lazy);\n\t\tadd(data[idx *\
    \ 2 + 1].lazy, data[idx].lazy);\n\t\tdata[idx].lazy = operator_type::identity();\n\
    \t}\n\tvoid propagate_bound(usize idx) {\n\t\tif(idx == 0) return;\n\n\t\tstd::stack<usize>\
    \ order;\n\n\t\tidx >>= countr_zeros(idx);\n\t\twhile(idx >>= 1) order.push(idx);\n\
    \t\twhile(!order.empty()){\n\t\t\tpropagate(order.top());\n\t\t\torder.pop();\n\
    \t\t}\n\t}\n\n\tvoid recalc(usize idx) { data[idx].value = value_type::operation(value(data[idx\
    \ * 2 + 0]), value(data[idx * 2 + 1])); }\n\tvoid recalc_bound(usize idx) {\n\t\
    \tif(idx == 0) return;\n\n\t\tidx >>= countr_zeros(idx);\n\t\twhile(idx >>= 1)\
    \ recalc(idx);\n\t}\n\npublic:\n\tlazy_segment_tree() = default;\n\texplicit lazy_segment_tree(usize\
    \ n): data(n << 1, node_type(value_type::identity(), operator_type::identity()))\
    \ {}\n\ttemplate<class InputIt> explicit lazy_segment_tree(InputIt first, InputIt\
    \ last)\n\t: lazy_segment_tree(std::distance(first, last)) {\n\t\tfor(int index\
    \ = 0; first != last; first++, index++) set(index, *first);\n\t\tbuild();\n\t\
    }\n\tvoid build() { for(usize i = size() - 1; i > 0; i--) recalc(i); }\n\n\tusize\
    \ size() { return data.size() >> 1; }\n\tbool empty() { return size() == 0; }\n\
    \tvoid clear() { data.clear(); }\n\tvoid swap(lazy_segment_tree& r) { data.swap(r.data);\
    \ }\n\n\tT get(usize i) { return fold(i, i + 1); }\n\tvoid set(usize i, const\
    \ value_type& x) { data[i + size()].value = x; };\n\n\tvoid change(usize i, const\
    \ value_type& x) {\n\t\ti += size();\n\t\tpropagate_bound(((i >> 1) << 1) + 1);\n\
    \t\tdata[i] = node_type(x, operator_type::identity());\n\t\trecalc_bound(((i >>\
    \ 1) << 1) + 1);\n\t}\n\tvoid update(usize i, const value_type& x) {\n\t\ti +=\
    \ size();\n\t\tpropagate_bound(((i >> 1) << 1) + 1);\n\t\tdata[i] = node_type(value_type::operation(value(data[i]),\
    \ x), operator_type::identity());\n\t\trecalc_bound(((i >> 1) << 1) + 1);\n\t\
    }\n\n\tT fold(usize first, usize last) {\n\t\tfirst += size();\n\t\tlast  += size();\n\
    \t\tpropagate_bound(first);\n\t\trecalc_bound(first);\n\t\tpropagate_bound(last);\n\
    \t\trecalc_bound(last);\n\n\t\tvalue_type lval = value_type::identity();\n\t\t\
    value_type rval = value_type::identity();\n\t\twhile(first != last) {\n\t\t\t\
    if(first & 1) {\n\t\t\t\tlval = value_type::operation(lval, value(data[first]));\n\
    \t\t\t\tfirst++;\n\t\t\t}\n\t\t\tif(last  & 1) {\n\t\t\t\tlast--;\n\t\t\t\trval\
    \ = value_type::operation(value(data[last]), rval);\n\t\t\t}\n\t\t\tfirst >>=\
    \ 1;\n\t\t\tlast  >>= 1;\n\t\t}\n\t\treturn value_type::operation(lval, rval).a;\n\
    \t}\n\n\tvoid update(usize first, usize last, const operator_type& x) {\n\t\t\
    first += size();\n\t\tlast  += size();\n\t\tusize first_tmp = first;\n\t\tusize\
    \ last_tmp  = last;\n\t\tpropagate_bound(first);\n\t\tpropagate_bound(last);\n\
    \t\twhile(first != last) {\n\t\t\tif(first & 1) {\n\t\t\t\tadd(data[first].lazy,\
    \ x);\n\t\t\t\tfirst++;\n\t\t\t}\n\t\t\tif(last  & 1) {\n\t\t\t\tlast--;\n\t\t\
    \t\tadd(data[last].lazy, x);\n\t\t\t}\n\t\t\tfirst >>= 1;\n\t\t\tlast >>= 1;\n\
    \t\t}\n\t\trecalc_bound(first_tmp);\n\t\trecalc_bound(last_tmp);\n\t}\n};\n}\n"
  dependsOn:
  - data_structure/monoid.hpp
  - data_structure/affine.hpp
  isVerificationFile: false
  path: data_structure/lazy_segment_tree.hpp
  requiredBy: []
  timestamp: '2020-10-30 00:31:11+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/lazy_segment_tree.hpp
layout: document
redirect_from:
- /library/data_structure/lazy_segment_tree.hpp
- /library/data_structure/lazy_segment_tree.hpp.html
title: data_structure/lazy_segment_tree.hpp
---
