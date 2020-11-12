---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"graph/weisfeiler_lehman_graph_kernel.hpp\"\n\n#include <algorithm>\n\
    #include <vector>\n#include <cstdint>\n#include <numeric>\n\nnamespace wl_kernel\
    \ {\nclass graph_t {\npublic:\n\tstruct edge_t {\n\t\tsize_t u, v;\n\n\t\tsize_t\
    \ opposite(int x) { return u ^ v ^ x; }\n\t\tvoid swap(edge_t& r) {\n\t\t\tstd::swap(u,\
    \ r.u);\n\t\t\tstd::swap(v, r.v);\n\t\t}\n\t};\n\nprotected:\n\tstd::vector<std::vector<size_t>>\
    \ graph;\n\tstd::vector<size_t> label;\n\tstd::vector<edge_t> edge;\n\npublic:\n\
    \tgraph_t(size_t n): label(n), graph(n) {}\n\ttemplate<class InputIt> graph_t(InputIt\
    \ first, InputIt last)\n\t\t: graph_t(std::distance(first, last)) {\n\n\t\tfor(int\
    \ i = 0; i < graph.size(); i++) {\n\t\t\tlabel[i] = *first;\n\t\t\tfirst++;\n\t\
    \t}\n\t}\n\n\tvoid add_edge(size_t u, size_t v) {\n\t\tgraph[u].push_back(v);\n\
    \t\tgraph[v].push_back(u);\n\t\tedge.push_back(edge_t{u, v});\n\t}\n\n\tsize_t\
    \ size() { return graph.size(); }\n\tsize_t edge_size() { return edge.size();\
    \ }\n\tsize_t degree(size_t x) { return graph[x].size(); }\n\n\tstd::vector<edge_t>\
    \ get_edge() { return edge; }\n\n\tvoid clear() {\n\t\tgraph.clear();\n\t\tlabel.clear();\n\
    \t\tedge.clear();\n\t}\n\tvoid swap(graph_t& r) {\n\t\tgraph.swap(r.graph);\n\t\
    \tlabel.swap(r.label);\n\t\tedge.swap(r.edge);\n\t}\n};\n\nclass wl_kernel: public\
    \ graph_t {\n\tstd::vector<std::vector<size_t>> histogram;\n\tsize_t lower;\n\n\
    public:\n\twl_kernel(size_t n): graph_t(n) {\n\t\tlower = 0;\n\t\thistogram.resize(1);\n\
    \t\tfor(size_t i = 0; i < n; i++) histogram[0].push_back(i);\n\t}\n\ttemplate<class\
    \ InputIt> wl_kernel(InputIt first, InputIt last)\n\t: graph_t(first, last) {\n\
    \t\tlower = 0;\n\t\thistogram.resize(*std::max_element(begin(label), end(label)));\n\
    \t\tfor(size_t i = 0; i < size(); i++) histogram[label[i]].push_back(i);\n\t}\n\
    \npublic:\n\tvoid iterate() {\n\t\tstd::vector<std::vector<size_t>> vec(size());\n\
    \t\tfor(size_t k = lower; k < histogram.size(); k++)\n\t\t\tfor(size_t v: histogram[k])\n\
    \t\t\t\tfor(size_t u: graph[v]) vec[u].push_back(k);\n\n\t\tstd::vector<size_t>\
    \ order(size());\n\t\tstd::iota(begin(order), end(order), 0);\n\t\tstd::sort(begin(order),\
    \ end(order), [&](size_t i, size_t j) { return vec[i] < vec[j]; });\n\n\t\t//\
    \ std::vector<size_t> order = counting_sort(vec);\n\n\t\thistogram.push_back(std::vector<size_t>());\n\
    \t\tfor(size_t i = 0; i < size(); i++) {\n\t\t\tif(i != 0 and vec[order[i - 1]]\
    \ != vec[order[i]]) {\n\t\t\t\thistogram.push_back(std::vector<size_t>());\n\t\
    \t\t}\n\t\t\thistogram.back().push_back(order[i]);\n\t\t}\n\t\tlower = histogram.size();\n\
    \t}\n\tvoid iterate(size_t k) { while(k--) iterate(); }\n\n\tstd::vector<size_t>\
    \ get_histogram() {\n\t\tstd::vector<size_t> ret(histogram.size());\n\t\tfor(size_t\
    \ i = 0; i < histogram.size(); i++) ret[i] = histogram[i].size();\n\t\treturn\
    \ std::move(ret);\n\t}\n};\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <vector>\n#include <cstdint>\n\
    #include <numeric>\n\nnamespace wl_kernel {\nclass graph_t {\npublic:\n\tstruct\
    \ edge_t {\n\t\tsize_t u, v;\n\n\t\tsize_t opposite(int x) { return u ^ v ^ x;\
    \ }\n\t\tvoid swap(edge_t& r) {\n\t\t\tstd::swap(u, r.u);\n\t\t\tstd::swap(v,\
    \ r.v);\n\t\t}\n\t};\n\nprotected:\n\tstd::vector<std::vector<size_t>> graph;\n\
    \tstd::vector<size_t> label;\n\tstd::vector<edge_t> edge;\n\npublic:\n\tgraph_t(size_t\
    \ n): label(n), graph(n) {}\n\ttemplate<class InputIt> graph_t(InputIt first,\
    \ InputIt last)\n\t\t: graph_t(std::distance(first, last)) {\n\n\t\tfor(int i\
    \ = 0; i < graph.size(); i++) {\n\t\t\tlabel[i] = *first;\n\t\t\tfirst++;\n\t\t\
    }\n\t}\n\n\tvoid add_edge(size_t u, size_t v) {\n\t\tgraph[u].push_back(v);\n\t\
    \tgraph[v].push_back(u);\n\t\tedge.push_back(edge_t{u, v});\n\t}\n\n\tsize_t size()\
    \ { return graph.size(); }\n\tsize_t edge_size() { return edge.size(); }\n\tsize_t\
    \ degree(size_t x) { return graph[x].size(); }\n\n\tstd::vector<edge_t> get_edge()\
    \ { return edge; }\n\n\tvoid clear() {\n\t\tgraph.clear();\n\t\tlabel.clear();\n\
    \t\tedge.clear();\n\t}\n\tvoid swap(graph_t& r) {\n\t\tgraph.swap(r.graph);\n\t\
    \tlabel.swap(r.label);\n\t\tedge.swap(r.edge);\n\t}\n};\n\nclass wl_kernel: public\
    \ graph_t {\n\tstd::vector<std::vector<size_t>> histogram;\n\tsize_t lower;\n\n\
    public:\n\twl_kernel(size_t n): graph_t(n) {\n\t\tlower = 0;\n\t\thistogram.resize(1);\n\
    \t\tfor(size_t i = 0; i < n; i++) histogram[0].push_back(i);\n\t}\n\ttemplate<class\
    \ InputIt> wl_kernel(InputIt first, InputIt last)\n\t: graph_t(first, last) {\n\
    \t\tlower = 0;\n\t\thistogram.resize(*std::max_element(begin(label), end(label)));\n\
    \t\tfor(size_t i = 0; i < size(); i++) histogram[label[i]].push_back(i);\n\t}\n\
    \npublic:\n\tvoid iterate() {\n\t\tstd::vector<std::vector<size_t>> vec(size());\n\
    \t\tfor(size_t k = lower; k < histogram.size(); k++)\n\t\t\tfor(size_t v: histogram[k])\n\
    \t\t\t\tfor(size_t u: graph[v]) vec[u].push_back(k);\n\n\t\tstd::vector<size_t>\
    \ order(size());\n\t\tstd::iota(begin(order), end(order), 0);\n\t\tstd::sort(begin(order),\
    \ end(order), [&](size_t i, size_t j) { return vec[i] < vec[j]; });\n\n\t\t//\
    \ std::vector<size_t> order = counting_sort(vec);\n\n\t\thistogram.push_back(std::vector<size_t>());\n\
    \t\tfor(size_t i = 0; i < size(); i++) {\n\t\t\tif(i != 0 and vec[order[i - 1]]\
    \ != vec[order[i]]) {\n\t\t\t\thistogram.push_back(std::vector<size_t>());\n\t\
    \t\t}\n\t\t\thistogram.back().push_back(order[i]);\n\t\t}\n\t\tlower = histogram.size();\n\
    \t}\n\tvoid iterate(size_t k) { while(k--) iterate(); }\n\n\tstd::vector<size_t>\
    \ get_histogram() {\n\t\tstd::vector<size_t> ret(histogram.size());\n\t\tfor(size_t\
    \ i = 0; i < histogram.size(); i++) ret[i] = histogram[i].size();\n\t\treturn\
    \ std::move(ret);\n\t}\n};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/weisfeiler_lehman_graph_kernel.hpp
  requiredBy: []
  timestamp: '2020-11-13 00:12:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/weisfeiler_lehman_graph_kernel.hpp
layout: document
redirect_from:
- /library/graph/weisfeiler_lehman_graph_kernel.hpp
- /library/graph/weisfeiler_lehman_graph_kernel.hpp.html
title: graph/weisfeiler_lehman_graph_kernel.hpp
---
