---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/unionfind.union_find.test.cpp
    title: test/yosupo/unionfind.union_find.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"data_structure/union_find.hpp\"\n\n\n\n#include <cstdint>\n\
    #include <vector>\n\nclass union_find {\npublic:\n\tusing size_type = std::int_fast32_t;\n\
    \tusing container = std::vector<size_type>;\n\t\n\tcontainer data;\n\tsize_type\
    \ comp_cnt;\n\nprivate:\n\tconst size_type find(size_type k) {\n\t\tif(data[k]\
    \ < 0) return k;\n\t\treturn data[k] = find(data[k]);\n\t}\n\npublic:\n\tunion_find()\
    \ = default;\n\tunion_find(const union_find &) = default;\n\tunion_find(union_find&&)\
    \ = default;\n\n\tunion_find & operator=(const union_find &) = default;\n\tunion_find\
    \ & operator=(union_find &&) = default;\n\n\tunion_find(size_type N): data(N,\
    \ -1), comp_cnt(N) {}\n\n\tbool unite(size_type x, size_type y) {\n\t\tx = find(x);\
    \ y = find(y);\n\t\tif(x == y) return false;\n\t\tif(data[x] > data[y]) std::swap(x,\
    \ y);\n\t\t\n\t\tdata[x] += data[y];\n\t\tdata[y] = x;\n\t\tcomp_cnt--;\n\t\t\
    return true;\n\t}\n\t\n\tbool is_united(size_type x, size_type y) { return find(x)\
    \ == find(y); }\n\tsize_type size() const { return data.size(); }\n\tsize_type\
    \ size(size_type k) { return -data[find(k)]; }\n\tsize_type comp(size_type k)\
    \ { return find(k); };\n\tsize_type count() const { return comp_cnt; }\n\tsize_type\
    \ operator[](size_type k) { return find(k); }\n\t\n\tvoid swap(union_find & r)\
    \ {\n\t\tdata.swap(r.data);\n\t\tstd::swap(comp_cnt, r.comp_cnt);\n\t}\n};\n\n\
    \n"
  code: "#ifndef INCLUDED_UNION_FIND_HPP\n#define INCLUDED_UNION_FIND_HPP\n\n#include\
    \ <cstdint>\n#include <vector>\n\nclass union_find {\npublic:\n\tusing size_type\
    \ = std::int_fast32_t;\n\tusing container = std::vector<size_type>;\n\t\n\tcontainer\
    \ data;\n\tsize_type comp_cnt;\n\nprivate:\n\tconst size_type find(size_type k)\
    \ {\n\t\tif(data[k] < 0) return k;\n\t\treturn data[k] = find(data[k]);\n\t}\n\
    \npublic:\n\tunion_find() = default;\n\tunion_find(const union_find &) = default;\n\
    \tunion_find(union_find&&) = default;\n\n\tunion_find & operator=(const union_find\
    \ &) = default;\n\tunion_find & operator=(union_find &&) = default;\n\n\tunion_find(size_type\
    \ N): data(N, -1), comp_cnt(N) {}\n\n\tbool unite(size_type x, size_type y) {\n\
    \t\tx = find(x); y = find(y);\n\t\tif(x == y) return false;\n\t\tif(data[x] >\
    \ data[y]) std::swap(x, y);\n\t\t\n\t\tdata[x] += data[y];\n\t\tdata[y] = x;\n\
    \t\tcomp_cnt--;\n\t\treturn true;\n\t}\n\t\n\tbool is_united(size_type x, size_type\
    \ y) { return find(x) == find(y); }\n\tsize_type size() const { return data.size();\
    \ }\n\tsize_type size(size_type k) { return -data[find(k)]; }\n\tsize_type comp(size_type\
    \ k) { return find(k); };\n\tsize_type count() const { return comp_cnt; }\n\t\
    size_type operator[](size_type k) { return find(k); }\n\t\n\tvoid swap(union_find\
    \ & r) {\n\t\tdata.swap(r.data);\n\t\tstd::swap(comp_cnt, r.comp_cnt);\n\t}\n\
    };\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/union_find.hpp
  requiredBy: []
  timestamp: '2020-03-19 17:03:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/unionfind.union_find.test.cpp
documentation_of: data_structure/union_find.hpp
layout: document
redirect_from:
- /library/data_structure/union_find.hpp
- /library/data_structure/union_find.hpp.html
title: data_structure/union_find.hpp
---
