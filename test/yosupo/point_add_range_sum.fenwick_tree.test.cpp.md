---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/fenwick_tree.hpp
    title: data_structure/fenwick_tree.hpp
  - icon: ':heavy_check_mark:'
    path: other/fast_io.hpp
    title: other/fast_io.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"test/yosupo/point_add_range_sum.fenwick_tree.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\n#line\
    \ 1 \"data_structure/fenwick_tree.hpp\"\n\n\n\n#include <functional>\n#include\
    \ <vector>\n\ntemplate<class CommutativeMonoid>\nclass fenwick_tree {\npublic:\n\
    \tusing T = typename CommutativeMonoid::value_type;\n\tusing size_type = std::uint_fast32_t;\n\
    \n\tusing checker = std::function<bool(T)>;\n\n\tstd::vector<T> data;\n\t\nprivate:\n\
    \tsize_type get_lsb(size_type i) const { return i & (~i + 1); }\n\t\npublic:\n\
    \tfenwick_tree() = default;\n\tfenwick_tree(const fenwick_tree &) = default;\n\
    \tfenwick_tree(fenwick_tree &&) = default;\n\n\tfenwick_tree(size_type size):\
    \ data(size + 1, T{}) {}\n\n\ttemplate<class InputIt>\n\tfenwick_tree(InputIt\
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
    \ inverse(const value_type& x) { return -x; }\n};\n\n\n#line 1 \"other/fast_io.hpp\"\
    \n\n\n\n#include <cstdio>\n#include <cstdint>\n#include <cstddef>\n#include <cstring>\n\
    #include <limits>\n#include <string>\n#include <type_traits>\n#include <utility>\n\
    #line 13 \"other/fast_io.hpp\"\n\nnamespace fast_io {\n\t// fast I/O by rsk0315\
    \ (update: 2020-03-02 01:10:54).\n\tstatic size_t constexpr buf_size = 1 << 17;\n\
    \tstatic size_t constexpr margin = 1;\n\tstatic char inbuf[buf_size + margin]\
    \ = {};\n\tstatic char outbuf[buf_size + margin] = {};\n\tstatic __attribute__((aligned(8)))\
    \ char minibuf[32];\n\tstatic size_t constexpr int_digits = 20;\t// 18446744073709551615\n\
    \tstatic uintmax_t constexpr digit_mask = 0x3030303030303030;\n\tstatic uintmax_t\
    \ constexpr first_mask = 0x00FF00FF00FF00FF;\n\tstatic uintmax_t constexpr second_mask\
    \ = 0x0000FFFF0000FFFF;\n\tstatic uintmax_t constexpr third_mask = 0x00000000FFFFFFFF;\n\
    \tstatic uintmax_t constexpr tenpow[] = {\n\t\t1, 10, 100, 1000, 10000, 100000,\
    \ 1000000, 10000000, 100000000\n\t};\n\ttemplate <typename Tp>\n\tusing enable_if_integral\
    \ = std::enable_if<std::is_integral<Tp>::value, Tp>;\n\n\tclass scanner {\n\t\t\
    char* pos = inbuf;\n\t\tchar* endpos = inbuf + buf_size;\n\n\t\tvoid M_read_from_stdin()\
    \ {\n\t\t\tendpos = inbuf + fread(pos, 1, buf_size, stdin);\n\t\t}\n\t\tvoid M_reread_from_stdin()\
    \ {\n\t\t\tptrdiff_t len = endpos - pos;\n\t\t\tif (!(inbuf + len <= pos)) return;\n\
    \t\t\tmemcpy(inbuf, pos, len);\n\t\t\tchar* tmp = inbuf + len;\n\t\t\tendpos =\
    \ tmp + fread(tmp, 1, buf_size-len, stdin);\n\t\t\t*endpos = 0;\n\t\t\tpos = inbuf;\n\
    \t\t}\n\n\tpublic:\n\t\tscanner() { M_read_from_stdin(); }\n\n\t\ttemplate <typename\
    \ Integral,\n\t\t\t\t\t\t\ttypename enable_if_integral<Integral>::type* = nullptr>\n\
    \t\tvoid scan_parallel(Integral& x) {\n\t\t\t// See https://qiita.com/rsk0315_h4x/items/17a9cb12e0de5fd918f4\n\
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
    \n\n#line 5 \"test/yosupo/point_add_range_sum.fenwick_tree.test.cpp\"\n\nint main()\
    \ {\n\tint n, q; fin.scan(n, q);\n\tfenwick_tree<monoid<std::int_fast64_t>> bit(n);\n\
    \tfor(int i = 0; i < n; i++) {\n\t\tint a; fin.scan(a);\n\n\t\tbit.change(i, a);\n\
    \t}\n\n\twhile(q--) {\n\t\tint type; fin.scan(type);\n\n\t\tif(type == 0) {\n\t\
    \t\tint p, x; fin.scan(p, x);\n\n\t\t\tbit.update(p, x);\n\t\t} else if(type ==\
    \ 1) {\n\t\t\tint l, r; fin.scan(l, r);\n\n\t\t\tfout.println(bit.fold(l, r));\n\
    \t\t}\n\t}\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include \"../../data_structure/fenwick_tree.hpp\"\n#include \"../../other/fast_io.hpp\"\
    \n\nint main() {\n\tint n, q; fin.scan(n, q);\n\tfenwick_tree<monoid<std::int_fast64_t>>\
    \ bit(n);\n\tfor(int i = 0; i < n; i++) {\n\t\tint a; fin.scan(a);\n\n\t\tbit.change(i,\
    \ a);\n\t}\n\n\twhile(q--) {\n\t\tint type; fin.scan(type);\n\n\t\tif(type ==\
    \ 0) {\n\t\t\tint p, x; fin.scan(p, x);\n\n\t\t\tbit.update(p, x);\n\t\t} else\
    \ if(type == 1) {\n\t\t\tint l, r; fin.scan(l, r);\n\n\t\t\tfout.println(bit.fold(l,\
    \ r));\n\t\t}\n\t}\n}\n"
  dependsOn:
  - data_structure/fenwick_tree.hpp
  - other/fast_io.hpp
  isVerificationFile: true
  path: test/yosupo/point_add_range_sum.fenwick_tree.test.cpp
  requiredBy: []
  timestamp: '2020-03-20 12:55:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/point_add_range_sum.fenwick_tree.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/point_add_range_sum.fenwick_tree.test.cpp
- /verify/test/yosupo/point_add_range_sum.fenwick_tree.test.cpp.html
title: test/yosupo/point_add_range_sum.fenwick_tree.test.cpp
---
