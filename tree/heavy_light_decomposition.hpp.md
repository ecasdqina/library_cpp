---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/2667.test.cpp
    title: test/aoj/2667.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yukicoder/901.test.cpp
    title: test/yukicoder/901.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/vertex_add_path_sum.test.cpp
    title: test/yosupo/vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/vertex_add_subtree_sum.test.cpp
    title: test/yosupo/vertex_add_subtree_sum.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"tree/heavy_light_decomposition.hpp\"\n\n\n\n#include <cstdint>\n\
    #include <functional>\n#include <vector>\n\nclass heavy_light_decomposition {\n\
    public:\n\tusing i32 = std::int_fast32_t;\n\tusing u32 = std::uint_fast32_t;\n\
    \n\tusing processor = std::function<void(u32, u32)>;\n\n\tstd::vector<std::vector<u32>>\
    \ g;\n\tstd::vector<u32> edge_u, edge_v, size, et, in, out, head;\n\tstd::vector<i32>\
    \ parent, heavy;\n\nprivate:\n\tvoid calc_size(u32 v) {\n\t\tsize[v] = 1;\n\t\t\
    for(int id: g[v]) {\n\t\t\tint to = edge_u[id] ^ edge_v[id] ^ v;\n\t\t\tif(to\
    \ == parent[v]) continue;\n\t\t\tparent[to] = v;\n\t\t\tcalc_size(to);\n\t\t\t\
    size[v] += size[to];\n\n\t\t\tif(heavy[v] == -1 or size[heavy[v]] < size[to])\
    \ heavy[v] = to;\n\t\t}\n\t}\n\tvoid calc_et(u32 v) {\n\t\tin[v] = et.size();\n\
    \t\tet.push_back(v);\n\t\tif(heavy[v] != -1) {\n\t\t\thead[heavy[v]] = head[v];\n\
    \t\t\tcalc_et(heavy[v]);\n\t\t}\n\t\tfor(int id: g[v]) {\t\n\t\t\tint to = edge_u[id]\
    \ ^ edge_v[id] ^ v;\n\t\t\tif(to == parent[v] or to == heavy[v]) continue;\n\t\
    \t\thead[to] = to;\n\t\t\tcalc_et(to);\n\t\t}\n\t\tout[v] = et.size();\n\t}\n\n\
    \tvoid path(i32 x, i32 y, const processor& process, bool edge) const {\n\t\tstd::vector<std::pair<u32,\
    \ u32>> l, r;\n\t\twhile(true) {\n\t\t\tif(in[x] > in[y]) {\n\t\t\t\tstd::swap(x,\
    \ y);\n\t\t\t\tl.swap(r);\n\t\t\t}\n\n\t\t\tif(head[x] == head[y]) {\n\t\t\t\t\
    l.emplace_back(in[x] + !!edge, in[y] + 1);\n\t\t\t\tbreak;\n\t\t\t}\n\t\t\tl.emplace_back(in[head[y]],\
    \ in[y] + 1);\n\t\t\ty = parent[head[y]];\n\t\t}\n\n\t\tfor(auto e: l) process(e.first,\
    \ e.second);\n\t\tfor(auto e: r) process(e.first, e.second);\n\t}\n\tvoid subtree(u32\
    \ v, const processor& process, bool edge) const {\n\t\tprocess(in[v] + !!edge,\
    \ out[v]);\n\t}\n\npublic:\n\theavy_light_decomposition() = default;\n\theavy_light_decomposition(heavy_light_decomposition&&)\
    \ = default;\n\theavy_light_decomposition(const heavy_light_decomposition &) =\
    \ default;\n\n\theavy_light_decomposition(int n)\n\t\t: g(n), size(n), in(n),\
    \ out(n), parent(n, -1), heavy(n, -1), head(n) {}\n\n\tvoid add_edge(int x, int\
    \ y) {\n\t\tg[x].push_back(edge_u.size());\n\t\tg[y].push_back(edge_v.size());\n\
    \t\tedge_u.push_back(x);\n\t\tedge_v.push_back(y);\n\t}\n\tvoid build(u32 root\
    \ = 0) {\n\t\tcalc_size(root);\n\t\tcalc_et(root);\n\t}\n\n\tu32 lca(u32 x, u32\
    \ y) const {\n\t\twhile(true) {\n\t\t\tif(in[x] > in[y]) std::swap(x, y);\n\t\t\
    \tif(head[x] == head[y]) return x;\n\t\t\ty = parent[head[y]];\n\t\t}\n\t}\n\t\
    \n\tvoid path_node(u32 x, u32 y, const processor& process) const { path(x, y,\
    \ process, false); }\n\tvoid path_edge(u32 x, u32 y, const processor& process)\
    \ const { path(x, y, process, true); }\n\tvoid path(u32 x, u32 y, const processor&\
    \ process) const { path(x, y, process, false); }\n\n\tvoid subtree_node(u32 v,\
    \ const processor& process) const { subtree(v, process, false); }\n\tvoid subtree_edge(u32\
    \ v, const processor& process) const { subtree(v, process, true); }\n\tvoid subtree(u32\
    \ v, const processor& process) const { subtree(v, process, false); }\n\n\tu32\
    \ index_node(u32 v) const { return in[v]; };\n\tu32 index_edge(u32 x, u32 y) const\
    \ { return std::max(in[x], in[y]); };\n\tu32 index(u32 v) const { return in[v];\
    \ };\n\t\n\tconst u32 operator[](u32 k) const { return in[k]; }\n};\n\n\n"
  code: "#ifndef INCLUDED_HEAVY_LIGHT_DECOMPOSITION_HPP\n#define INCLUDED_HEAVY_LIGHT_DECOMPOSITION_HPP\n\
    \n#include <cstdint>\n#include <functional>\n#include <vector>\n\nclass heavy_light_decomposition\
    \ {\npublic:\n\tusing i32 = std::int_fast32_t;\n\tusing u32 = std::uint_fast32_t;\n\
    \n\tusing processor = std::function<void(u32, u32)>;\n\n\tstd::vector<std::vector<u32>>\
    \ g;\n\tstd::vector<u32> edge_u, edge_v, size, et, in, out, head;\n\tstd::vector<i32>\
    \ parent, heavy;\n\nprivate:\n\tvoid calc_size(u32 v) {\n\t\tsize[v] = 1;\n\t\t\
    for(int id: g[v]) {\n\t\t\tint to = edge_u[id] ^ edge_v[id] ^ v;\n\t\t\tif(to\
    \ == parent[v]) continue;\n\t\t\tparent[to] = v;\n\t\t\tcalc_size(to);\n\t\t\t\
    size[v] += size[to];\n\n\t\t\tif(heavy[v] == -1 or size[heavy[v]] < size[to])\
    \ heavy[v] = to;\n\t\t}\n\t}\n\tvoid calc_et(u32 v) {\n\t\tin[v] = et.size();\n\
    \t\tet.push_back(v);\n\t\tif(heavy[v] != -1) {\n\t\t\thead[heavy[v]] = head[v];\n\
    \t\t\tcalc_et(heavy[v]);\n\t\t}\n\t\tfor(int id: g[v]) {\t\n\t\t\tint to = edge_u[id]\
    \ ^ edge_v[id] ^ v;\n\t\t\tif(to == parent[v] or to == heavy[v]) continue;\n\t\
    \t\thead[to] = to;\n\t\t\tcalc_et(to);\n\t\t}\n\t\tout[v] = et.size();\n\t}\n\n\
    \tvoid path(i32 x, i32 y, const processor& process, bool edge) const {\n\t\tstd::vector<std::pair<u32,\
    \ u32>> l, r;\n\t\twhile(true) {\n\t\t\tif(in[x] > in[y]) {\n\t\t\t\tstd::swap(x,\
    \ y);\n\t\t\t\tl.swap(r);\n\t\t\t}\n\n\t\t\tif(head[x] == head[y]) {\n\t\t\t\t\
    l.emplace_back(in[x] + !!edge, in[y] + 1);\n\t\t\t\tbreak;\n\t\t\t}\n\t\t\tl.emplace_back(in[head[y]],\
    \ in[y] + 1);\n\t\t\ty = parent[head[y]];\n\t\t}\n\n\t\tfor(auto e: l) process(e.first,\
    \ e.second);\n\t\tfor(auto e: r) process(e.first, e.second);\n\t}\n\tvoid subtree(u32\
    \ v, const processor& process, bool edge) const {\n\t\tprocess(in[v] + !!edge,\
    \ out[v]);\n\t}\n\npublic:\n\theavy_light_decomposition() = default;\n\theavy_light_decomposition(heavy_light_decomposition&&)\
    \ = default;\n\theavy_light_decomposition(const heavy_light_decomposition &) =\
    \ default;\n\n\theavy_light_decomposition(int n)\n\t\t: g(n), size(n), in(n),\
    \ out(n), parent(n, -1), heavy(n, -1), head(n) {}\n\n\tvoid add_edge(int x, int\
    \ y) {\n\t\tg[x].push_back(edge_u.size());\n\t\tg[y].push_back(edge_v.size());\n\
    \t\tedge_u.push_back(x);\n\t\tedge_v.push_back(y);\n\t}\n\tvoid build(u32 root\
    \ = 0) {\n\t\tcalc_size(root);\n\t\tcalc_et(root);\n\t}\n\n\tu32 lca(u32 x, u32\
    \ y) const {\n\t\twhile(true) {\n\t\t\tif(in[x] > in[y]) std::swap(x, y);\n\t\t\
    \tif(head[x] == head[y]) return x;\n\t\t\ty = parent[head[y]];\n\t\t}\n\t}\n\t\
    \n\tvoid path_node(u32 x, u32 y, const processor& process) const { path(x, y,\
    \ process, false); }\n\tvoid path_edge(u32 x, u32 y, const processor& process)\
    \ const { path(x, y, process, true); }\n\tvoid path(u32 x, u32 y, const processor&\
    \ process) const { path(x, y, process, false); }\n\n\tvoid subtree_node(u32 v,\
    \ const processor& process) const { subtree(v, process, false); }\n\tvoid subtree_edge(u32\
    \ v, const processor& process) const { subtree(v, process, true); }\n\tvoid subtree(u32\
    \ v, const processor& process) const { subtree(v, process, false); }\n\n\tu32\
    \ index_node(u32 v) const { return in[v]; };\n\tu32 index_edge(u32 x, u32 y) const\
    \ { return std::max(in[x], in[y]); };\n\tu32 index(u32 v) const { return in[v];\
    \ };\n\t\n\tconst u32 operator[](u32 k) const { return in[k]; }\n};\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/heavy_light_decomposition.hpp
  requiredBy: []
  timestamp: '2020-03-19 17:03:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/2667.test.cpp
  - test/yukicoder/901.test.cpp
  - test/yosupo/vertex_add_path_sum.test.cpp
  - test/yosupo/vertex_add_subtree_sum.test.cpp
documentation_of: tree/heavy_light_decomposition.hpp
layout: document
redirect_from:
- /library/tree/heavy_light_decomposition.hpp
- /library/tree/heavy_light_decomposition.hpp.html
title: tree/heavy_light_decomposition.hpp
---
