---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: data_structure/fenwick_tree.hpp
    title: data_structure/fenwick_tree.hpp
  - icon: ':warning:'
    path: data_structure/lazy_segment_tree.hpp
    title: data_structure/lazy_segment_tree.hpp
  - icon: ':question:'
    path: data_structure/monoid.hpp
    title: data_structure/monoid.hpp
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
  bundledCode: "#line 2 \"data_structure/affine.hpp\"\n\n#include <algorithm>\n\n\
    namespace cplib {\ntemplate<class T> struct affine {\n\tusing value_type = T;\n\
    \n\tvalue_type a;\n\tvalue_type b;\n\n\tconstexpr affine(const value_type& a =\
    \ 1, const value_type& b = 0): a(a), b(b) {}\n\tconstexpr affine operator+(const\
    \ affine& r) const { return affine{a + r.a, b + r.b}; }\n\tconstexpr affine composite(const\
    \ affine& r) const { return affine{a * r.a, a * r.b + b}; }\n\n\tconstexpr value_type\
    \ evaluate(const value_type& x) { return a * x + b; }\n};\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n\nnamespace cplib {\ntemplate<class\
    \ T> struct affine {\n\tusing value_type = T;\n\n\tvalue_type a;\n\tvalue_type\
    \ b;\n\n\tconstexpr affine(const value_type& a = 1, const value_type& b = 0):\
    \ a(a), b(b) {}\n\tconstexpr affine operator+(const affine& r) const { return\
    \ affine{a + r.a, b + r.b}; }\n\tconstexpr affine composite(const affine& r) const\
    \ { return affine{a * r.a, a * r.b + b}; }\n\n\tconstexpr value_type evaluate(const\
    \ value_type& x) { return a * x + b; }\n};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/affine.hpp
  requiredBy:
  - data_structure/monoid.hpp
  - data_structure/fenwick_tree.hpp
  - data_structure/segment_tree.hpp
  - data_structure/lazy_segment_tree.hpp
  timestamp: '2020-09-21 08:15:08+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/yosupo/point_set_range_composite.segment_tree.test.cpp
  - test/yosupo/point_add_range_sum.segment_tree.test.cpp
  - test/yosupo/vertex_add_path_sum.test.cpp
  - test/yosupo/vertex_add_subtree_sum.test.cpp
  - test/yosupo/point_add_range_sum.fenwick_tree.test.cpp
documentation_of: data_structure/affine.hpp
layout: document
redirect_from:
- /library/data_structure/affine.hpp
- /library/data_structure/affine.hpp.html
title: data_structure/affine.hpp
---
