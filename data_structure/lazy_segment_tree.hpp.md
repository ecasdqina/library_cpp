---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: data_structure/monoid.hpp
    title: data_structure/monoid.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"data_structure/lazy_segment_tree.hpp\"\n\n#include <vector>\n\
    #include <cstdint>\n\n#line 2 \"data_structure/monoid.hpp\"\n\n#include <algorithm>\n\
    \nnamespace cplib {\ntemplate<class T, T id = T{}> struct add_monoid {\n\tusing\
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
    \ return monoid{x.a.inverse()}; }\n};\n}\n#line 7 \"data_structure/lazy_segment_tree.hpp\"\
    \n\nnamespace cplib {\nstruct lazy_segment_tree {\npublic:\n\nprivate:\n\tstd::vector<A>\
    \ data;\n\npublic:\n\n\n};\n}\n"
  code: "#pragma once\n\n#include <vector>\n#include <cstdint>\n\n#include \"../data_structure/monoid.hpp\"\
    \n\nnamespace cplib {\nstruct lazy_segment_tree {\npublic:\n\nprivate:\n\tstd::vector<A>\
    \ data;\n\npublic:\n\n\n};\n}\n"
  dependsOn:
  - data_structure/monoid.hpp
  isVerificationFile: false
  path: data_structure/lazy_segment_tree.hpp
  requiredBy: []
  timestamp: '2020-09-21 01:53:43+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/lazy_segment_tree.hpp
layout: document
redirect_from:
- /library/data_structure/lazy_segment_tree.hpp
- /library/data_structure/lazy_segment_tree.hpp.html
title: data_structure/lazy_segment_tree.hpp
---
