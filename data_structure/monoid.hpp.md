---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: data_structure/affine.hpp
    title: data_structure/affine.hpp
  _extendedRequiredBy:
  - icon: ':x:'
    path: data_structure/fenwick_tree.hpp
    title: data_structure/fenwick_tree.hpp
  - icon: ':warning:'
    path: data_structure/lazy_segment_tree.hpp
    title: data_structure/lazy_segment_tree.hpp
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree.hpp
    title: data_structure/segment_tree.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo/point_add_range_sum.fenwick_tree.test.cpp
    title: test/yosupo/point_add_range_sum.fenwick_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/point_add_range_sum.segment_tree.test.cpp
    title: test/yosupo/point_add_range_sum.segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
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
    links: []
  bundledCode: "#line 2 \"data_structure/monoid.hpp\"\n\n#include <algorithm>\n#include\
    \ <limits>\n#line 2 \"data_structure/affine.hpp\"\n\n#line 4 \"data_structure/affine.hpp\"\
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
    \t}\n};\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <limits>\n#include \"../data_structure/affine.hpp\"\
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
    \t}\n};\n}\n"
  dependsOn:
  - data_structure/affine.hpp
  isVerificationFile: false
  path: data_structure/monoid.hpp
  requiredBy:
  - data_structure/fenwick_tree.hpp
  - data_structure/segment_tree.hpp
  - data_structure/lazy_segment_tree.hpp
  timestamp: '2020-09-27 04:15:30+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/yosupo/point_set_range_composite.segment_tree.test.cpp
  - test/yosupo/point_add_range_sum.segment_tree.test.cpp
  - test/yosupo/vertex_add_path_sum.test.cpp
  - test/yosupo/vertex_add_subtree_sum.test.cpp
  - test/yosupo/point_add_range_sum.fenwick_tree.test.cpp
documentation_of: data_structure/monoid.hpp
layout: document
redirect_from:
- /library/data_structure/monoid.hpp
- /library/data_structure/monoid.hpp.html
title: data_structure/monoid.hpp
---
