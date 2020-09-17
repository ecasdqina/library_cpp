---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/point_set_range_composite.segment_tree.test.cpp
    title: test/yosupo/point_set_range_composite.segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/vertex_add_path_sum.test.cpp
    title: test/yosupo/vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/point_add_range_sum.segment_tree.test.cpp
    title: test/yosupo/point_add_range_sum.segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/vertex_add_subtree_sum.test.cpp
    title: test/yosupo/vertex_add_subtree_sum.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"data_structure/monoid.hpp\"\n\n#include <algorithm>\n\n\
    namespace cplib {\n\ttemplate<class T, T id = T{}> struct add_monoid {\n\t\tT\
    \ a;\n\n\t\tconstexpr add_monoid(T a): a(a) {}\n\t\tstatic constexpr add_monoid\
    \ operation(const add_monoid& l, const add_monoid& r) { return add_monoid{l.a\
    \ + r.a}; }\n\t\tstatic constexpr add_monoid identity() { return add_monoid{id};\
    \ };\n\t\tconstexpr T value() { return a; }\n\t};\n\n\ttemplate<class T, T id\
    \ = T{1}> struct mul_monoid {\n\t\tT a;\n\n\t\tconstexpr mul_monoid(T a): a(a)\
    \ {}\n\t\tstatic constexpr mul_monoid operation(const mul_monoid& l, const mul_monoid&\
    \ r) { return mul_monoid{l.a * r.a}; }\n\t\tstatic constexpr mul_monoid identity()\
    \ { return mul_monoid{id}; };\n\t\tconstexpr T value() { return a; }\n\t};\n\n\
    \ttemplate<class T, T id = T{}> struct max_monoid {\n\t\tT a;\n\n\t\tconstexpr\
    \ max_monoid(T a): a(a) {}\n\t\tstatic constexpr max_monoid operation(const max_monoid&\
    \ l, const max_monoid& r) { return max_monoid{std::max(l.a, r.a)}; }\n\t\tstatic\
    \ constexpr max_monoid identity() { return max_monoid{id}; };\n\t\tconstexpr T\
    \ value() { return a; }\n\t};\n\n\ttemplate<class T, T id = T{}> struct min_monoid\
    \ {\n\t\tT a;\n\n\t\tconstexpr min_monoid(T a): a(a) {}\n\t\tstatic constexpr\
    \ min_monoid operation(const min_monoid& l, const min_monoid& r) { return min_monoid{std::min(l.a,\
    \ r.a)}; }\n\t\tstatic constexpr min_monoid identity() { return min_monoid{id};\
    \ };\n\t\tconstexpr T value() { return a; }\n\t};\n\n\ttemplate<class T, T& id>\
    \ struct monoid {\n\t\tT a;\n\n\t\tconstexpr monoid(T a): a(a) {}\n\t\tstatic\
    \ constexpr monoid operation(const monoid& l, const monoid& r) { return monoid{l.a\
    \ + r.a}; }\n\t\tstatic constexpr monoid identity() { return monoid{id}; }\n\t\
    \tconstexpr T value() { return a; }\n\t};\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n\nnamespace cplib {\n\ttemplate<class\
    \ T, T id = T{}> struct add_monoid {\n\t\tT a;\n\n\t\tconstexpr add_monoid(T a):\
    \ a(a) {}\n\t\tstatic constexpr add_monoid operation(const add_monoid& l, const\
    \ add_monoid& r) { return add_monoid{l.a + r.a}; }\n\t\tstatic constexpr add_monoid\
    \ identity() { return add_monoid{id}; };\n\t\tconstexpr T value() { return a;\
    \ }\n\t};\n\n\ttemplate<class T, T id = T{1}> struct mul_monoid {\n\t\tT a;\n\n\
    \t\tconstexpr mul_monoid(T a): a(a) {}\n\t\tstatic constexpr mul_monoid operation(const\
    \ mul_monoid& l, const mul_monoid& r) { return mul_monoid{l.a * r.a}; }\n\t\t\
    static constexpr mul_monoid identity() { return mul_monoid{id}; };\n\t\tconstexpr\
    \ T value() { return a; }\n\t};\n\n\ttemplate<class T, T id = T{}> struct max_monoid\
    \ {\n\t\tT a;\n\n\t\tconstexpr max_monoid(T a): a(a) {}\n\t\tstatic constexpr\
    \ max_monoid operation(const max_monoid& l, const max_monoid& r) { return max_monoid{std::max(l.a,\
    \ r.a)}; }\n\t\tstatic constexpr max_monoid identity() { return max_monoid{id};\
    \ };\n\t\tconstexpr T value() { return a; }\n\t};\n\n\ttemplate<class T, T id\
    \ = T{}> struct min_monoid {\n\t\tT a;\n\n\t\tconstexpr min_monoid(T a): a(a)\
    \ {}\n\t\tstatic constexpr min_monoid operation(const min_monoid& l, const min_monoid&\
    \ r) { return min_monoid{std::min(l.a, r.a)}; }\n\t\tstatic constexpr min_monoid\
    \ identity() { return min_monoid{id}; };\n\t\tconstexpr T value() { return a;\
    \ }\n\t};\n\n\ttemplate<class T, T& id> struct monoid {\n\t\tT a;\n\n\t\tconstexpr\
    \ monoid(T a): a(a) {}\n\t\tstatic constexpr monoid operation(const monoid& l,\
    \ const monoid& r) { return monoid{l.a + r.a}; }\n\t\tstatic constexpr monoid\
    \ identity() { return monoid{id}; }\n\t\tconstexpr T value() { return a; }\n\t\
    };\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/monoid.hpp
  requiredBy: []
  timestamp: '2020-09-17 22:59:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/point_set_range_composite.segment_tree.test.cpp
  - test/yosupo/vertex_add_path_sum.test.cpp
  - test/yosupo/point_add_range_sum.segment_tree.test.cpp
  - test/yosupo/vertex_add_subtree_sum.test.cpp
documentation_of: data_structure/monoid.hpp
layout: document
redirect_from:
- /library/data_structure/monoid.hpp
- /library/data_structure/monoid.hpp.html
title: data_structure/monoid.hpp
---
