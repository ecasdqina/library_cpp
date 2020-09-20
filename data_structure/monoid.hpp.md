---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: data_structure/lazy_segment_tree.hpp
    title: data_structure/lazy_segment_tree.hpp
  - icon: ':question:'
    path: data_structure/segment_tree.hpp
    title: data_structure/segment_tree.hpp
  - icon: ':x:'
    path: data_structure/fenwick_tree.hpp
    title: data_structure/fenwick_tree.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/point_set_range_composite.segment_tree.test.cpp
    title: test/yosupo/point_set_range_composite.segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/vertex_add_path_sum.test.cpp
    title: test/yosupo/vertex_add_path_sum.test.cpp
  - icon: ':x:'
    path: test/yosupo/point_add_range_sum.segment_tree.test.cpp
    title: test/yosupo/point_add_range_sum.segment_tree.test.cpp
  - icon: ':x:'
    path: test/yosupo/point_add_range_sum.fenwick_tree.test.cpp
    title: test/yosupo/point_add_range_sum.fenwick_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/vertex_add_subtree_sum.test.cpp
    title: test/yosupo/vertex_add_subtree_sum.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"data_structure/monoid.hpp\"\n\n#include <algorithm>\n\n\
    namespace cplib {\ntemplate<class T, T id = T{}> struct add_monoid {\n\tusing\
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
    \ id = T{}> struct min_monoid {\n\tusing value_type = T;\n\n\tT a;\n\n\tconstexpr\
    \ min_monoid(T a): a(a) {}\n\tstatic constexpr min_monoid operation(const min_monoid&\
    \ l, const min_monoid& r) { return min_monoid{std::min(l.a, r.a)}; }\n\tstatic\
    \ constexpr min_monoid identity() { return min_monoid{id}; };\n};\n\ntemplate<class\
    \ T, T& id> struct monoid {\n\tusing value_type = T;\n\n\tT a;\n\n\tconstexpr\
    \ monoid(T a): a(a) {}\n\tstatic constexpr monoid operation(const monoid& l, const\
    \ monoid& r) { return monoid{l.a + r.a}; }\n\tstatic constexpr monoid identity()\
    \ { return monoid{id}; }\n\tstatic constexpr monoid inverse(const monoid& x) {\
    \ return monoid{x.a.inverse()}; }\n};\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n\nnamespace cplib {\ntemplate<class\
    \ T, T id = T{}> struct add_monoid {\n\tusing value_type = T;\n\n\tT a;\n\n\t\
    constexpr add_monoid(T a): a(a) {}\n\tstatic constexpr add_monoid operation(const\
    \ add_monoid& l, const add_monoid& r) { return add_monoid{l.a + r.a}; }\n\tstatic\
    \ constexpr add_monoid identity() { return add_monoid{id}; };\n\tstatic constexpr\
    \ add_monoid inverse(const add_monoid& x) { return add_monoid{-x.a}; }\n};\n\n\
    template<class T, T id = T{1}> struct mul_monoid {\n\tusing value_type = T;\n\n\
    \tT a;\n\n\tconstexpr mul_monoid(T a): a(a) {}\n\tstatic constexpr mul_monoid\
    \ operation(const mul_monoid& l, const mul_monoid& r) { return mul_monoid{l.a\
    \ * r.a}; }\n\tstatic constexpr mul_monoid identity() { return mul_monoid{id};\
    \ };\n};\n\ntemplate<class T, T id = T{}> struct max_monoid {\n\tusing value_type\
    \ = T;\n\n\tT a;\n\n\tconstexpr max_monoid(T a): a(a) {}\n\tstatic constexpr max_monoid\
    \ operation(const max_monoid& l, const max_monoid& r) { return max_monoid{std::max(l.a,\
    \ r.a)}; }\n\tstatic constexpr max_monoid identity() { return max_monoid{id};\
    \ };\n};\n\ntemplate<class T, T id = T{}> struct min_monoid {\n\tusing value_type\
    \ = T;\n\n\tT a;\n\n\tconstexpr min_monoid(T a): a(a) {}\n\tstatic constexpr min_monoid\
    \ operation(const min_monoid& l, const min_monoid& r) { return min_monoid{std::min(l.a,\
    \ r.a)}; }\n\tstatic constexpr min_monoid identity() { return min_monoid{id};\
    \ };\n};\n\ntemplate<class T, T& id> struct monoid {\n\tusing value_type = T;\n\
    \n\tT a;\n\n\tconstexpr monoid(T a): a(a) {}\n\tstatic constexpr monoid operation(const\
    \ monoid& l, const monoid& r) { return monoid{l.a + r.a}; }\n\tstatic constexpr\
    \ monoid identity() { return monoid{id}; }\n\tstatic constexpr monoid inverse(const\
    \ monoid& x) { return monoid{x.a.inverse()}; }\n};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/monoid.hpp
  requiredBy:
  - data_structure/lazy_segment_tree.hpp
  - data_structure/segment_tree.hpp
  - data_structure/fenwick_tree.hpp
  timestamp: '2020-09-21 01:52:21+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/yosupo/point_set_range_composite.segment_tree.test.cpp
  - test/yosupo/vertex_add_path_sum.test.cpp
  - test/yosupo/point_add_range_sum.segment_tree.test.cpp
  - test/yosupo/point_add_range_sum.fenwick_tree.test.cpp
  - test/yosupo/vertex_add_subtree_sum.test.cpp
documentation_of: data_structure/monoid.hpp
layout: document
redirect_from:
- /library/data_structure/monoid.hpp
- /library/data_structure/monoid.hpp.html
title: data_structure/monoid.hpp
---
