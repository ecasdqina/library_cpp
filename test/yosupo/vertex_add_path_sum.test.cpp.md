---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: data_structure/segment_tree.hpp
    title: data_structure/segment_tree.hpp
  - icon: ':question:'
    path: data_structure/monoid.hpp
    title: data_structure/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: tree/heavy_light_decomposition.hpp
    title: tree/heavy_light_decomposition.hpp
  - icon: ':question:'
    path: other/fast_io.hpp
    title: other/fast_io.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_path_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_path_sum
  bundledCode: "#line 1 \"test/yosupo/vertex_add_path_sum.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/vertex_add_path_sum\"\n\n#include <stdio.h>\n\
    #line 2 \"data_structure/segment_tree.hpp\"\n\n#include <vector>\n#include <cstdint>\n\
    \n#line 2 \"data_structure/monoid.hpp\"\n\n#include <algorithm>\n\nnamespace cplib\
    \ {\ntemplate<class T, T id = T{}> struct add_monoid {\n\tusing value_type = T;\n\
    \n\tT a;\n\n\tconstexpr add_monoid(T a): a(a) {}\n\tstatic constexpr add_monoid\
    \ operation(const add_monoid& l, const add_monoid& r) { return add_monoid{l.a\
    \ + r.a}; }\n\tstatic constexpr add_monoid identity() { return add_monoid{id};\
    \ };\n\tconstexpr add_monoid inverse() { return add_monoid{-a}; }\n\tconstexpr\
    \ T value() { return a; }\n};\n\ntemplate<class T, T id = T{1}> struct mul_monoid\
    \ {\n\tusing value_type = T;\n\n\tT a;\n\n\tconstexpr mul_monoid(T a): a(a) {}\n\
    \tstatic constexpr mul_monoid operation(const mul_monoid& l, const mul_monoid&\
    \ r) { return mul_monoid{l.a * r.a}; }\n\tstatic constexpr mul_monoid identity()\
    \ { return mul_monoid{id}; };\n\tconstexpr T value() { return a; }\n};\n\ntemplate<class\
    \ T, T id = T{}> struct max_monoid {\n\tusing value_type = T;\n\n\tT a;\n\n\t\
    constexpr max_monoid(T a): a(a) {}\n\tstatic constexpr max_monoid operation(const\
    \ max_monoid& l, const max_monoid& r) { return max_monoid{std::max(l.a, r.a)};\
    \ }\n\tstatic constexpr max_monoid identity() { return max_monoid{id}; };\n\t\
    constexpr T value() { return a; }\n};\n\ntemplate<class T, T id = T{}> struct\
    \ min_monoid {\n\tusing value_type = T;\n\n\tT a;\n\n\tconstexpr min_monoid(T\
    \ a): a(a) {}\n\tstatic constexpr min_monoid operation(const min_monoid& l, const\
    \ min_monoid& r) { return min_monoid{std::min(l.a, r.a)}; }\n\tstatic constexpr\
    \ min_monoid identity() { return min_monoid{id}; };\n\tconstexpr T value() { return\
    \ a; }\n};\n\ntemplate<class T, T& id> struct monoid {\n\tusing value_type = T;\n\
    \n\tT a;\n\n\tconstexpr monoid(T a): a(a) {}\n\tstatic constexpr monoid operation(const\
    \ monoid& l, const monoid& r) { return monoid{l.a + r.a}; }\n\tstatic constexpr\
    \ monoid identity() { return monoid{id}; }\n\tconstexpr monoid inverse() { return\
    \ monoid{id.inverse()}; }\n\tconstexpr T value() { return a; }\n};\n}\n#line 7\
    \ \"data_structure/segment_tree.hpp\"\n\nnamespace cplib {\ntemplate<class Monoid>\
    \ class segment_tree {\npublic:\n\tusing value_type = Monoid;\n\tusing T = typename\
    \ value_type::value_type;\n\tusing usize = std::uint_fast32_t;\n\nprivate:\n\t\
    int n;\n\tstd::vector<value_type> data;\n\nprivate:\n\tusize base() const { return\
    \ data.size() >> 1; }\n\npublic:\n\tsegment_tree() = default;\n\texplicit segment_tree(usize\
    \ n): n(n) {\n\t\tusize size = 1;\n\t\twhile(size <= n) size <<= 1;\n\t\tdata.assign(size\
    \ << 1, value_type::identity());\n\t}\n\ttemplate<class InputIt> explicit segment_tree(InputIt\
    \ first, InputIt last)\n\t: segment_tree(std::distance(first, last)) {\n\t\tfor(int\
    \ index = 0; first != last; first++, index++) set(index, *first);\n\t\tbuild();\n\
    \t}\n\n\tusize size() const { return n; }\n\tbool empty() const { return size()\
    \ == 0; }\n\tvoid clear() {\n\t\tn = 0;\n\t\tdata.clear();\n\t}\n\tvoid swap(segment_tree&\
    \ r) {\n\t\tstd::swap(n, r.n);\n\t\tdata.swap(r.data);\n\t}\n\n\tT get(usize i)\
    \ const { return data[i + base()].a; }\n\tvoid set(usize i, const value_type&\
    \ x) { data[i + base()] = x; }\n\n\tvoid build() {\n\t\tfor(usize i = (int)base()\
    \ - 1; i > 0; i--)\n\t\t\tdata[i] = value_type::operation(data[i * 2 + 0], data[i\
    \ * 2 + 1]);\n\t}\n\tvoid change(usize i, const value_type& x) {\n\t\tdata[i +=\
    \ base()] = x;\n\t\twhile(i >>= 1) data[i] = value_type::operation(data[i * 2\
    \ + 0], data[i * 2 + 1]);\n\t}\n\tvoid update(usize i, const value_type& x) {\
    \ change(i, value_type::operation(get(i), x)); }\n\n\tT fold(usize first, usize\
    \ last) const {\n\t\tfirst += base();\n\t\tlast += base();\n\n\t\tvalue_type lval\
    \ = value_type::identity();\n\t\tvalue_type rval = value_type::identity();\n\t\
    \twhile(first != last) {\n\t\t\tif(first & 1) lval = value_type::operation(lval,\
    \ data[first++]);\n\t\t\tif(last  & 1) rval = value_type::operation(data[--last],\
    \ rval);\n\t\t\tfirst >>= 1;\n\t\t\tlast  >>= 1;\n\t\t}\n\t\treturn value_type::operation(lval,\
    \ rval).a;\n\t}\n\tT fold_all() const { return data[1].a; }\n\n\t// return max{r\
    \ | f(fold(l, r - 1)) = true}\n\ttemplate<class F> usize search_right(int l, const\
    \ F& f) const {\n\t\tif(l == size()) return base();\n\n\t\tl += base();\n\t\t\
    value_type acc = value_type::identity();\n\t\tdo {\n\t\t\twhile(l % 2 == 0) l\
    \ >>= 1;\n\t\t\tif(!f(value_type::operation(acc, data[l]))) {\n\t\t\t\twhile(l\
    \ < base()) {\n\t\t\t\t\tl = l << 1;\n\t\t\t\t\tif(f(value_type::operation(acc,\
    \ data[l]))) {\n\t\t\t\t\t\tacc = value_type::operation(acc, data[l]);\n\t\t\t\
    \t\t\tl += 1;\n\t\t\t\t\t}\n\t\t\t\t}\n\t\t\t\treturn l - base();\n\t\t\t}\n\t\
    \t\tacc = value_type::operation(acc, data[l]);\n\t\t\tl += 1;\n\t\t} while((l\
    \ & -l) != l);\n\t\treturn size();\n\t}\n\n\t// return min{l | f(fold(l, r - 1)\
    \ = true}\n\ttemplate<class F> usize search_left(int r, const F& f) const {\n\t\
    \tif(r == 0) return 0;\n\n\t\tr += base();\n\t\tvalue_type acc = value_type::identity();\n\
    \t\tdo {\n\t\t\tr--;\n\t\t\twhile(r > 1 and (r % 2)) r >>= 1;\n\t\t\tif(!f(value_type::operation(data[r],\
    \ acc))) {\n\t\t\t\twhile(r < base()) {\n\t\t\t\t\tr = r * 2 + 1;\n\t\t\t\t\t\
    if(f(value_type::operation(data[r], acc))) {\n\t\t\t\t\t\tacc = value_type::operation(data[r],\
    \ acc);\n\t\t\t\t\t\tr -= 1;\n\t\t\t\t\t}\n\t\t\t\t}\n\t\t\t\treturn r + 1 - base();\n\
    \t\t\t}\n\t\t\tacc = value_type::operation(data[r], acc);\n\t\t} while((r & -r)\
    \ == r);\n\t\treturn 0;\n\t}\n};\n}\n\n// @docs docs/segment_tree.md\n#line 1\
    \ \"tree/heavy_light_decomposition.hpp\"\n\n\n\n#line 5 \"tree/heavy_light_decomposition.hpp\"\
    \n#include <functional>\n#line 7 \"tree/heavy_light_decomposition.hpp\"\n\nclass\
    \ heavy_light_decomposition {\npublic:\n\tusing i32 = std::int_fast32_t;\n\tusing\
    \ u32 = std::uint_fast32_t;\n\n\tusing processor = std::function<void(u32, u32)>;\n\
    \n\tstd::vector<std::vector<u32>> g;\n\tstd::vector<u32> edge_u, edge_v, size,\
    \ et, in, out, head;\n\tstd::vector<i32> parent, heavy;\n\nprivate:\n\tvoid calc_size(u32\
    \ v) {\n\t\tsize[v] = 1;\n\t\tfor(int id: g[v]) {\n\t\t\tint to = edge_u[id] ^\
    \ edge_v[id] ^ v;\n\t\t\tif(to == parent[v]) continue;\n\t\t\tparent[to] = v;\n\
    \t\t\tcalc_size(to);\n\t\t\tsize[v] += size[to];\n\n\t\t\tif(heavy[v] == -1 or\
    \ size[heavy[v]] < size[to]) heavy[v] = to;\n\t\t}\n\t}\n\tvoid calc_et(u32 v)\
    \ {\n\t\tin[v] = et.size();\n\t\tet.push_back(v);\n\t\tif(heavy[v] != -1) {\n\t\
    \t\thead[heavy[v]] = head[v];\n\t\t\tcalc_et(heavy[v]);\n\t\t}\n\t\tfor(int id:\
    \ g[v]) {\t\n\t\t\tint to = edge_u[id] ^ edge_v[id] ^ v;\n\t\t\tif(to == parent[v]\
    \ or to == heavy[v]) continue;\n\t\t\thead[to] = to;\n\t\t\tcalc_et(to);\n\t\t\
    }\n\t\tout[v] = et.size();\n\t}\n\n\tvoid path(i32 x, i32 y, const processor&\
    \ process, bool edge) const {\n\t\tstd::vector<std::pair<u32, u32>> l, r;\n\t\t\
    while(true) {\n\t\t\tif(in[x] > in[y]) {\n\t\t\t\tstd::swap(x, y);\n\t\t\t\tl.swap(r);\n\
    \t\t\t}\n\n\t\t\tif(head[x] == head[y]) {\n\t\t\t\tl.emplace_back(in[x] + !!edge,\
    \ in[y] + 1);\n\t\t\t\tbreak;\n\t\t\t}\n\t\t\tl.emplace_back(in[head[y]], in[y]\
    \ + 1);\n\t\t\ty = parent[head[y]];\n\t\t}\n\n\t\tfor(auto e: l) process(e.first,\
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
    \ };\n\t\n\tconst u32 operator[](u32 k) const { return in[k]; }\n};\n\n\n#line\
    \ 1 \"other/fast_io.hpp\"\n\n\n\n#include <cstdio>\n#line 6 \"other/fast_io.hpp\"\
    \n#include <cstddef>\n#include <cstring>\n#include <limits>\n#include <string>\n\
    #include <type_traits>\n#include <utility>\n#line 13 \"other/fast_io.hpp\"\n\n\
    namespace fast_io {\n\t// fast I/O by rsk0315 (update: 2020-03-02 01:10:54).\n\
    \tstatic size_t constexpr buf_size = 1 << 17;\n\tstatic size_t constexpr margin\
    \ = 1;\n\tstatic char inbuf[buf_size + margin] = {};\n\tstatic char outbuf[buf_size\
    \ + margin] = {};\n\tstatic __attribute__((aligned(8))) char minibuf[32];\n\t\
    static size_t constexpr int_digits = 20;\t// 18446744073709551615\n\tstatic uintmax_t\
    \ constexpr digit_mask = 0x3030303030303030;\n\tstatic uintmax_t constexpr first_mask\
    \ = 0x00FF00FF00FF00FF;\n\tstatic uintmax_t constexpr second_mask = 0x0000FFFF0000FFFF;\n\
    \tstatic uintmax_t constexpr third_mask = 0x00000000FFFFFFFF;\n\tstatic uintmax_t\
    \ constexpr tenpow[] = {\n\t\t1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,\
    \ 100000000\n\t};\n\ttemplate <typename Tp>\n\tusing enable_if_integral = std::enable_if<std::is_integral<Tp>::value,\
    \ Tp>;\n\n\tclass scanner {\n\t\tchar* pos = inbuf;\n\t\tchar* endpos = inbuf\
    \ + buf_size;\n\n\t\tvoid M_read_from_stdin() {\n\t\t\tendpos = inbuf + fread(pos,\
    \ 1, buf_size, stdin);\n\t\t}\n\t\tvoid M_reread_from_stdin() {\n\t\t\tptrdiff_t\
    \ len = endpos - pos;\n\t\t\tif (!(inbuf + len <= pos)) return;\n\t\t\tmemcpy(inbuf,\
    \ pos, len);\n\t\t\tchar* tmp = inbuf + len;\n\t\t\tendpos = tmp + fread(tmp,\
    \ 1, buf_size-len, stdin);\n\t\t\t*endpos = 0;\n\t\t\tpos = inbuf;\n\t\t}\n\n\t\
    public:\n\t\tscanner() { M_read_from_stdin(); }\n\n\t\ttemplate <typename Integral,\n\
    \t\t\t\t\t\t\ttypename enable_if_integral<Integral>::type* = nullptr>\n\t\tvoid\
    \ scan_parallel(Integral& x) {\n\t\t\t// See https://qiita.com/rsk0315_h4x/items/17a9cb12e0de5fd918f4\n\
    \t\t\tif (__builtin_expect(endpos <= pos + int_digits, 0))\n\t\t\t\tM_reread_from_stdin();\n\
    \t\t\tbool ends = false;\n\t\t\ttypename std::make_unsigned<Integral>::type y\
    \ = 0;\n\t\t\tbool neg = false;\n\t\t\tif (std::is_signed<Integral>::value &&\
    \ *pos == '-') {\n\t\t\t\tneg = true;\n\t\t\t\t++pos;\n\t\t\t}\n\t\t\tdo {\n\t\
    \t\t\tmemcpy(minibuf, pos, 8);\n\t\t\t\tlong c = *(long*)minibuf;\n\t\t\t\tlong\
    \ d = (c & digit_mask) ^ digit_mask;\n\t\t\t\tint skip = 8;\n\t\t\t\tint shift\
    \ = 8;\n\t\t\t\tif (d) {\n\t\t\t\t\tint ctz = __builtin_ctzl(d);\n\t\t\t\t\tif\
    \ (ctz == 4) break;\n\t\t\t\t\tc &= (1L << (ctz-5)) - 1;\n\t\t\t\t\tint discarded\
    \ = (68-ctz) / 8;\n\t\t\t\t\tshift -= discarded;\n\t\t\t\t\tc <<= discarded *\
    \ 8;\n\t\t\t\t\tskip -= discarded;\n\t\t\t\t\tends = true;\n\t\t\t\t}\n\t\t\t\t\
    c |= digit_mask;\n\t\t\t\tc ^= digit_mask;\n\t\t\t\tc = ((c >> 8) + c*10) & first_mask;\n\
    \t\t\t\tc = ((c >> 16) + c*100) & second_mask;\n\t\t\t\tc = ((c >> 32) + c*10000)\
    \ & third_mask;\n\t\t\t\ty = y*tenpow[shift] + c;\n\t\t\t\tpos += skip;\n\t\t\t\
    } while (!ends);\n\t\t\tx = (neg? -y: y);\n\t\t\t++pos;\n\t\t}\n\n\t\ttemplate\
    \ <typename Integral,\n\t\t\t\t\t\t\ttypename enable_if_integral<Integral>::type*\
    \ = nullptr>\n\t\tvoid scan_serial(Integral& x) {\n\t\t\tif (__builtin_expect(endpos\
    \ <= pos + int_digits, 0))\n\t\t\t\tM_reread_from_stdin();\n\t\t\tbool neg = false;\n\
    \t\t\tif (std::is_signed<Integral>::value && *pos == '-') {\n\t\t\t\tneg = true;\n\
    \t\t\t\t++pos;\n\t\t\t}\n\t\t\ttypename std::make_unsigned<Integral>::type y =\
    \ *pos-'0';\n\t\t\twhile (*++pos >= '0') y = 10*y + *pos-'0';\n\t\t\tx = (neg?\
    \ -y: y);\n\t\t\t++pos;\n\t\t}\n\n\t\ttemplate <typename Integral,\n\t\t\t\t\t\
    \t\ttypename enable_if_integral<Integral>::type* = nullptr>\n\t\t// Use scan_parallel(x)\
    \ only when x may be too large (about 10^12).\n\t\t// Otherwise, even when x <=\
    \ 10^9, scan_serial(x) may be faster.\n\t\tvoid scan(Integral& x) { scan_parallel(x);\
    \ }\n\n\t\tvoid scan_serial(std::string& s) {\n\t\t\t// until first whitespace\n\
    \t\t\ts = \"\";\n\t\t\tdo {\n\t\t\t\tchar* startpos = pos;\n\t\t\t\twhile (*pos\
    \ > ' ') ++pos;\n\t\t\t\ts += std::string(startpos, pos);\n\t\t\t\tif (*pos !=\
    \ 0) {\n\t\t\t\t\t++pos;\t// skip the space\n\t\t\t\t\tbreak;\n\t\t\t\t}\n\t\t\
    \t\tM_reread_from_stdin();\n\t\t\t} while (true);\n\t\t}\n\n\t\tvoid scan(std::string&\
    \ s) { scan_serial(s); }\n\n\t\tvoid scan(char& c) {\n\t\t\tif (__builtin_expect(endpos\
    \ <= pos + 2, 0))\n\t\t\t\tM_reread_from_stdin();\n\t\t\tc = *pos++;\n\t\t\t++pos;\n\
    \t\t}\n\n\t\ttemplate<class H, class... T>\n\t\tvoid scan(H& h, T&... t) {\n\t\
    \t\tscan(h);\n\t\t\tscan(t...);\n\t\t}\n\t};\n\n\tclass printer {\n\t\tchar* pos\
    \ = outbuf;\n\n\t\tvoid M_flush_stdout() {\n\t\t\tfwrite(outbuf, 1, pos-outbuf,\
    \ stdout);\n\t\t\tpos = outbuf;\n\t\t}\n\n\t\ttemplate <typename ... Args>\n\t\
    \tchar* format(const std::string& fmt, Args ... args ) {\n\t\t\tsize_t len = std::snprintf(\
    \ nullptr, 0, fmt.c_str(), args ... );\n\t\t\tchar* buf = new char[len + 1];\n\
    \t\t\tstd::snprintf(&buf[0], len + 1, fmt.c_str(), args ... );\n\t\t\treturn std::move(buf);\n\
    \t\t}\n\n\tpublic:\n\t\tprinter() = default;\n\t\t~printer() { M_flush_stdout();\
    \ }\n\n\t\tvoid print(char c) {\n\t\t\tif (__builtin_expect(pos + 1 >= outbuf\
    \ + buf_size, 0)) M_flush_stdout();\n\t\t\t*pos++ = c;\n\t\t}\n\n\t\ttemplate\
    \ <size_t N>\n\t\tvoid print(char const(&s)[N]) {\n\t\t\tif (__builtin_expect(pos\
    \ + N >= outbuf + buf_size, 0)) M_flush_stdout();\n\t\t\tmemcpy(pos, s, N-1);\n\
    \t\t\tpos += N-1;\n\t\t}\n\t\t\n\t\tvoid print(char const* s) {\n\t\t\twhile (*s\
    \ != 0) {\n\t\t\t\t*pos++ = *s++;\n\t\t\t\tif (pos == outbuf + buf_size) M_flush_stdout();\n\
    \t\t\t}\n\t\t}\n\n\t\tvoid print(const std::string& s) { print(s.c_str()); }\n\
    \t\t\n\t\tvoid print(const bool& x) {\n\t\t\tif(x) print(1);\n\t\t\telse print(0);\n\
    \t\t}\n\n\t\ttemplate <typename Integral,\n\t\t\t\t\t\t\ttypename enable_if_integral<Integral>::type*\
    \ = nullptr>\n\t\tvoid print(Integral x) {\n\t\t\tif (__builtin_expect(pos + int_digits\
    \ >= outbuf + buf_size, 0))\n\t\t\t\tM_flush_stdout();\n\t\t\tif (x == 0) {\n\t\
    \t\t\t*pos++ = '0';\n\t\t\t\treturn;\n\t\t\t}\n\t\t\tif (x < 0) {\n\t\t\t\t*pos++\
    \ = '-';\n\t\t\t\tif (__builtin_expect(x == std::numeric_limits<Integral>::min(),\
    \ 0)) {\n\t\t\t\t\tswitch (sizeof x) {\n\t\t\t\t\tcase 2: print(\"32768\"); return;\n\
    \t\t\t\t\tcase 4: print(\"2147483648\"); return;\n\t\t\t\t\tcase 8: print(\"9223372036854775808\"\
    ); return;\n\t\t\t\t\t}\n\t\t\t\t}\n\t\t\t\tx = -x;\n\t\t\t}\n\t\t\tchar* mp =\
    \ minibuf + sizeof minibuf;\n\t\t\t*--mp = x % 10 + '0';\n\t\t\tsize_t len = 1;\n\
    \t\t\ttypename std::make_unsigned<Integral>::type y = x / 10;\n\t\t\twhile (y\
    \ > 0) {\n\t\t\t\t*--mp = y % 10 + '0';\n\t\t\t\ty /= 10;\n\t\t\t\t++len;\n\t\t\
    \t}\n\t\t\tmemcpy(pos, mp, len);\n\t\t\tpos += len;\n\t\t}\n\n\t\ttemplate <typename\
    \ Tp>\n\t\tvoid println(Tp const& x) { print(x), print('\\n'); }\n\t\t\n\t\ttemplate<class\
    \ H, class... T>\n\t\tvoid print(const H& h, const T&... t) {\n\t\t\tprint(h);\n\
    \t\t\tprint(' ');\n\t\t\tprint(t...);\n\t\t}\n\t\ttemplate<class T>\n\t\tvoid\
    \ print(const std::vector<T>& t) {\n\t\t\tfor(size_t i = 0; i < t.size(); i++)\
    \ {\n\t\t\t\tprint(t[i]);\n\t\t\t\tif(i + 1 != t.size()) print(' ');\n\t\t\t}\n\
    \t\t}\n\t\ttemplate<class... T>\n\t\tvoid println(const T&... t) { print(t...);\
    \ print('\\n'); }\n\t\ttemplate<class T>\n\t\tvoid println(const std::vector<T>&\
    \ t) { print(t); print('\\n'); }\n\t\tvoid println() { print('\\n'); }\n\t};\n\
    }\nfast_io::scanner fin;\nfast_io::printer fout;\n\n// @docs docs/fast_io.md\n\
    \n\n#line 7 \"test/yosupo/vertex_add_path_sum.test.cpp\"\n\nusing i64 = std::int_fast64_t;\n\
    \nint main() {\n\tint n, q; fin.scan(n, q); std::vector<int> a(n);\n\tfor(int\
    \ i = 0; i < n; i++) fin.scan(a[i]);\n\n\theavy_light_decomposition hld(n);\n\t\
    for(int i = 0; i < n - 1; i++) {\n\t\tint a, b; fin.scan(a, b);\n\n\t\thld.add_edge(a,\
    \ b);\n\t}\n\thld.build();\n\n\tcplib::segment_tree<cplib::add_monoid<i64>> seg(n);\n\
    \tfor(int i = 0; i < n; i++) seg.change(hld[i], a[i]);\n\twhile(q--) {\n\t\tint\
    \ type, x, y; fin.scan(type, x, y);\n\n\t\tif(type == 0) seg.update(hld[x], y);\n\
    \t\tif(type == 1) {\n\t\t\ti64 ans = 0;\n\t\t\tauto p = [&](int l, int r) { ans\
    \ += seg.fold(l, r); };\n\t\t\thld.path(x, y, p);\n\n\t\t\tfout.println(ans);\n\
    \t\t}\n\t}\n\treturn 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_path_sum\"\n\
    \n#include <stdio.h>\n#include \"../../data_structure/segment_tree.hpp\"\n#include\
    \ \"../../tree/heavy_light_decomposition.hpp\"\n#include \"../../other/fast_io.hpp\"\
    \n\nusing i64 = std::int_fast64_t;\n\nint main() {\n\tint n, q; fin.scan(n, q);\
    \ std::vector<int> a(n);\n\tfor(int i = 0; i < n; i++) fin.scan(a[i]);\n\n\theavy_light_decomposition\
    \ hld(n);\n\tfor(int i = 0; i < n - 1; i++) {\n\t\tint a, b; fin.scan(a, b);\n\
    \n\t\thld.add_edge(a, b);\n\t}\n\thld.build();\n\n\tcplib::segment_tree<cplib::add_monoid<i64>>\
    \ seg(n);\n\tfor(int i = 0; i < n; i++) seg.change(hld[i], a[i]);\n\twhile(q--)\
    \ {\n\t\tint type, x, y; fin.scan(type, x, y);\n\n\t\tif(type == 0) seg.update(hld[x],\
    \ y);\n\t\tif(type == 1) {\n\t\t\ti64 ans = 0;\n\t\t\tauto p = [&](int l, int\
    \ r) { ans += seg.fold(l, r); };\n\t\t\thld.path(x, y, p);\n\n\t\t\tfout.println(ans);\n\
    \t\t}\n\t}\n\treturn 0;\n}\n"
  dependsOn:
  - data_structure/segment_tree.hpp
  - data_structure/monoid.hpp
  - tree/heavy_light_decomposition.hpp
  - other/fast_io.hpp
  isVerificationFile: true
  path: test/yosupo/vertex_add_path_sum.test.cpp
  requiredBy: []
  timestamp: '2020-09-19 05:52:18+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/vertex_add_path_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/vertex_add_path_sum.test.cpp
- /verify/test/yosupo/vertex_add_path_sum.test.cpp.html
title: test/yosupo/vertex_add_path_sum.test.cpp
---
