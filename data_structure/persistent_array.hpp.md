---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/persistent_queue.persistent_array.test.cpp
    title: test/yosupo/persistent_queue.persistent_array.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"data_structure/persistent_array.hpp\"\n\n\n\n#include <cstdint>\n\
    #include <cstring>\n#include <vector>\n#include <algorithm>\n\ntemplate<class\
    \ T, std::uint_fast32_t K = 20>\nclass persistent_array {\n\tusing u32 = std::uint_fast32_t;\n\
    \npublic:\n\tusing value_type = T;\n\tusing size_type = u32;\n\nprivate:\n\tstruct\
    \ node {\n\t\tT data;\n\t\tnode* child[K];\n\n\t\tnode() = default;\n\t};\n\t\
    using node_ptr = node*;\n\tstd::vector<node_ptr> root;\n\n\tvoid change(size_type\
    \ idx, const T& val, node_ptr& t) {\n\t\tif(!t) t = new node();\n\t\t\n\t\tif(!idx)\
    \ t->data = val;\n\t\telse change(idx / K, val, t->child[idx % K]);\n\t}\n\tnode_ptr\
    \ set(size_type idx, const T& val, const node_ptr& t) {\n\t\tnode_ptr ret = new\
    \ node();\n\t\tif(t) {\n\t\t\tstd::memcpy(ret->child, t->child, sizeof(t->child));\n\
    \t\t\tret->data = t->data;\n\t\t}\n\n\t\tif(!idx) ret->data = val;\n\t\telse ret->child[idx\
    \ % K] = set(idx / K, val, ret->child[idx % K]);\n\t\treturn ret;\n\t}\n\tT get(size_type\
    \ idx, const node_ptr& t) const {\n\t\tif(!t) return T{};\n\t\tif(idx == 0) return\
    \ t->data;\n\t\treturn get(idx / K, t->child[idx % K]);\n\t}\n\npublic:\n\tpersistent_array(persistent_array&&)\
    \ = default;\n\tpersistent_array(const persistent_array &) = default;\n\n\tpersistent_array():\
    \ root(1, nullptr) {}\n\n\tvoid change(size_type idx, const T& val, int time =\
    \ -1) {\n\t\tif(time == -1) change(idx, val, root.back());\n\t\telse change(idx,\
    \ val, root[time]);\n\t}\n\tsize_type set(size_type idx, const T& val, int time\
    \ = -1) {\n\t\tif(time == -1) root.push_back(set(idx, val, root.back()));\n\t\t\
    else root.push_back(set(idx, val, root[time]));\n\t\treturn root.size() - 1;\n\
    \t}\n\tT get(size_type idx, int time = -1) const {\n\t\tif(time == -1) return\
    \ get(idx, root.back());\n\t\treturn get(idx, root[time]);\n\t}\n\n\tconst T operator[](size_type\
    \ k) const { return get(k); }\n\tbool empty() const { return (root.size() == 1\
    \ and root[0] == nullptr); }\n\tsize_type now() const { return root.size() - 1;\
    \ }\n\tvoid clear() { root.assign(1, nullptr); }\n\tvoid swap(const persistent_array&\
    \ r) { root.swap(r.root); }\n};\n\n\n"
  code: "#ifndef INCLUDED_PERSISTENT_ARRAY_HPP\n#define INCLUDED_PERSISTENT_ARRAY_HPP\n\
    \n#include <cstdint>\n#include <cstring>\n#include <vector>\n#include <algorithm>\n\
    \ntemplate<class T, std::uint_fast32_t K = 20>\nclass persistent_array {\n\tusing\
    \ u32 = std::uint_fast32_t;\n\npublic:\n\tusing value_type = T;\n\tusing size_type\
    \ = u32;\n\nprivate:\n\tstruct node {\n\t\tT data;\n\t\tnode* child[K];\n\n\t\t\
    node() = default;\n\t};\n\tusing node_ptr = node*;\n\tstd::vector<node_ptr> root;\n\
    \n\tvoid change(size_type idx, const T& val, node_ptr& t) {\n\t\tif(!t) t = new\
    \ node();\n\t\t\n\t\tif(!idx) t->data = val;\n\t\telse change(idx / K, val, t->child[idx\
    \ % K]);\n\t}\n\tnode_ptr set(size_type idx, const T& val, const node_ptr& t)\
    \ {\n\t\tnode_ptr ret = new node();\n\t\tif(t) {\n\t\t\tstd::memcpy(ret->child,\
    \ t->child, sizeof(t->child));\n\t\t\tret->data = t->data;\n\t\t}\n\n\t\tif(!idx)\
    \ ret->data = val;\n\t\telse ret->child[idx % K] = set(idx / K, val, ret->child[idx\
    \ % K]);\n\t\treturn ret;\n\t}\n\tT get(size_type idx, const node_ptr& t) const\
    \ {\n\t\tif(!t) return T{};\n\t\tif(idx == 0) return t->data;\n\t\treturn get(idx\
    \ / K, t->child[idx % K]);\n\t}\n\npublic:\n\tpersistent_array(persistent_array&&)\
    \ = default;\n\tpersistent_array(const persistent_array &) = default;\n\n\tpersistent_array():\
    \ root(1, nullptr) {}\n\n\tvoid change(size_type idx, const T& val, int time =\
    \ -1) {\n\t\tif(time == -1) change(idx, val, root.back());\n\t\telse change(idx,\
    \ val, root[time]);\n\t}\n\tsize_type set(size_type idx, const T& val, int time\
    \ = -1) {\n\t\tif(time == -1) root.push_back(set(idx, val, root.back()));\n\t\t\
    else root.push_back(set(idx, val, root[time]));\n\t\treturn root.size() - 1;\n\
    \t}\n\tT get(size_type idx, int time = -1) const {\n\t\tif(time == -1) return\
    \ get(idx, root.back());\n\t\treturn get(idx, root[time]);\n\t}\n\n\tconst T operator[](size_type\
    \ k) const { return get(k); }\n\tbool empty() const { return (root.size() == 1\
    \ and root[0] == nullptr); }\n\tsize_type now() const { return root.size() - 1;\
    \ }\n\tvoid clear() { root.assign(1, nullptr); }\n\tvoid swap(const persistent_array&\
    \ r) { root.swap(r.root); }\n};\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/persistent_array.hpp
  requiredBy: []
  timestamp: '2020-03-19 17:03:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/persistent_queue.persistent_array.test.cpp
documentation_of: data_structure/persistent_array.hpp
layout: document
redirect_from:
- /library/data_structure/persistent_array.hpp
- /library/data_structure/persistent_array.hpp.html
title: data_structure/persistent_array.hpp
---
