---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/point_add_range_sum.fenwick_tree.test.cpp
    title: test/yosupo/point_add_range_sum.fenwick_tree.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"data_structure/fenwick_tree.hpp\"\n\n\n\n#include <functional>\n\
    #include <vector>\n\ntemplate<class CommutativeMonoid>\nclass fenwick_tree {\n\
    public:\n\tusing T = typename CommutativeMonoid::value_type;\n\tusing size_type\
    \ = std::uint_fast32_t;\n\n\tusing checker = std::function<bool(T)>;\n\n\tstd::vector<T>\
    \ data;\n\t\nprivate:\n\tsize_type get_lsb(size_type i) const { return i & (~i\
    \ + 1); }\n\t\npublic:\n\tfenwick_tree() = default;\n\tfenwick_tree(const fenwick_tree\
    \ &) = default;\n\tfenwick_tree(fenwick_tree &&) = default;\n\n\tfenwick_tree(size_type\
    \ size): data(size + 1, T{}) {}\n\n\ttemplate<class InputIt>\n\tfenwick_tree(InputIt\
    \ first, InputIt last) : fenwick_tree(std::distance(first, last)) {\n\t\tfor(int\
    \ index = 0; first != last; first++, index++) add(index, *first);\n\t}\n\t\n\t\
    fenwick_tree & operator=(const fenwick_tree &) = default;\n\tfenwick_tree & operator=(fenwick_tree\
    \ &&) = default;\n\n\tT fold(size_type last) const {\n\t\tT acc{};\n\t\twhile(last)\
    \ {\n\t\t\tacc = CommutativeMonoid::operation(data[last], acc);\n\n\t\t\tlast\
    \ -= get_lsb(last);\n\t\t}\n\t\t\n\t\treturn acc;\n\t}\n\tT fold(size_type first,\
    \ size_type last) const {\n\t\tT acc{};\n\t\twhile(first < last) {\n\t\t\tacc\
    \ = CommutativeMonoid::operation(data[last], acc);\n\n\t\t\tlast -= get_lsb(last);\n\
    \t\t}\n\n\t\twhile(last < first) {\n\t\t\tacc = CommutativeMonoid::operation(CommutativeMonoid::inverse(data[first]),\
    \ acc);\n\n\t\t\tfirst -= get_lsb(first);\n\t\t}\n\t\t\n\t\treturn acc;\n\t}\n\
    \tvoid update(size_type index, const T& value) {\n\t\tfor(++index; index < data.size();\
    \ index += get_lsb(index)) {\n\t\t\tdata[index] = CommutativeMonoid::operation(data[index],\
    \ value);\n\t\t}\n\t}\n\tvoid change(size_type index, const T& value) {\n\t\t\
    update(index, CommutativeMonoid::operation(CommutativeMonoid::inverse((*this)[index]),\
    \ value));\n\t}\n\n\t// min{x | f(fold(x)) = true}\n\ttemplate<class F>\n\tsize_type\
    \ search(const F & f) {\n\t\tif(f(T{})) return 0;\n\n\t\tT acc{};\n\t\tsize_type\
    \ i = 0, k = data.size();\n\t\twhile(k >>= 1) {\n\t\t\tif((i | k) < data.size()\
    \ and !f(CommutativeMonoid::operation(acc, data[i | k]))) {\n\t\t\t\tacc = CommutativeMonoid::operation(acc,\
    \ data[i | k]);\n\t\t\t\ti |= k;\n\t\t\t}\n\t\t}\n\t\treturn i + 1;\n\t}\n\n\t\
    T operator[](const size_type& k) const { return fold(k, k + 1); };\n\n\tbool empty()\
    \ const { return size() == 0; }\n\tsize_type size() const { return data.size()\
    \ - 1; }\n\tvoid swap(fenwick_tree & r) { data.swap(r.data); }\n};\n\ntemplate<class\
    \ T>\nstruct monoid {\n\tusing value_type = T;\n\n\tstatic value_type operation(const\
    \ value_type& a, const value_type& b) { return a + b; };\n\tstatic value_type\
    \ inverse(const value_type& x) { return -x; }\n};\n\n\n"
  code: "#ifndef INCLUDED_FENWICK_TREE_HPP\n#define INCLUDED_FENWICK_TREE_HPP\n\n\
    #include <functional>\n#include <vector>\n\ntemplate<class CommutativeMonoid>\n\
    class fenwick_tree {\npublic:\n\tusing T = typename CommutativeMonoid::value_type;\n\
    \tusing size_type = std::uint_fast32_t;\n\n\tusing checker = std::function<bool(T)>;\n\
    \n\tstd::vector<T> data;\n\t\nprivate:\n\tsize_type get_lsb(size_type i) const\
    \ { return i & (~i + 1); }\n\t\npublic:\n\tfenwick_tree() = default;\n\tfenwick_tree(const\
    \ fenwick_tree &) = default;\n\tfenwick_tree(fenwick_tree &&) = default;\n\n\t\
    fenwick_tree(size_type size): data(size + 1, T{}) {}\n\n\ttemplate<class InputIt>\n\
    \tfenwick_tree(InputIt first, InputIt last) : fenwick_tree(std::distance(first,\
    \ last)) {\n\t\tfor(int index = 0; first != last; first++, index++) add(index,\
    \ *first);\n\t}\n\t\n\tfenwick_tree & operator=(const fenwick_tree &) = default;\n\
    \tfenwick_tree & operator=(fenwick_tree &&) = default;\n\n\tT fold(size_type last)\
    \ const {\n\t\tT acc{};\n\t\twhile(last) {\n\t\t\tacc = CommutativeMonoid::operation(data[last],\
    \ acc);\n\n\t\t\tlast -= get_lsb(last);\n\t\t}\n\t\t\n\t\treturn acc;\n\t}\n\t\
    T fold(size_type first, size_type last) const {\n\t\tT acc{};\n\t\twhile(first\
    \ < last) {\n\t\t\tacc = CommutativeMonoid::operation(data[last], acc);\n\n\t\t\
    \tlast -= get_lsb(last);\n\t\t}\n\n\t\twhile(last < first) {\n\t\t\tacc = CommutativeMonoid::operation(CommutativeMonoid::inverse(data[first]),\
    \ acc);\n\n\t\t\tfirst -= get_lsb(first);\n\t\t}\n\t\t\n\t\treturn acc;\n\t}\n\
    \tvoid update(size_type index, const T& value) {\n\t\tfor(++index; index < data.size();\
    \ index += get_lsb(index)) {\n\t\t\tdata[index] = CommutativeMonoid::operation(data[index],\
    \ value);\n\t\t}\n\t}\n\tvoid change(size_type index, const T& value) {\n\t\t\
    update(index, CommutativeMonoid::operation(CommutativeMonoid::inverse((*this)[index]),\
    \ value));\n\t}\n\n\t// min{x | f(fold(x)) = true}\n\ttemplate<class F>\n\tsize_type\
    \ search(const F & f) {\n\t\tif(f(T{})) return 0;\n\n\t\tT acc{};\n\t\tsize_type\
    \ i = 0, k = data.size();\n\t\twhile(k >>= 1) {\n\t\t\tif((i | k) < data.size()\
    \ and !f(CommutativeMonoid::operation(acc, data[i | k]))) {\n\t\t\t\tacc = CommutativeMonoid::operation(acc,\
    \ data[i | k]);\n\t\t\t\ti |= k;\n\t\t\t}\n\t\t}\n\t\treturn i + 1;\n\t}\n\n\t\
    T operator[](const size_type& k) const { return fold(k, k + 1); };\n\n\tbool empty()\
    \ const { return size() == 0; }\n\tsize_type size() const { return data.size()\
    \ - 1; }\n\tvoid swap(fenwick_tree & r) { data.swap(r.data); }\n};\n\ntemplate<class\
    \ T>\nstruct monoid {\n\tusing value_type = T;\n\n\tstatic value_type operation(const\
    \ value_type& a, const value_type& b) { return a + b; };\n\tstatic value_type\
    \ inverse(const value_type& x) { return -x; }\n};\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/fenwick_tree.hpp
  requiredBy: []
  timestamp: '2020-03-19 17:03:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/point_add_range_sum.fenwick_tree.test.cpp
documentation_of: data_structure/fenwick_tree.hpp
layout: document
redirect_from:
- /library/data_structure/fenwick_tree.hpp
- /library/data_structure/fenwick_tree.hpp.html
title: data_structure/fenwick_tree.hpp
---
