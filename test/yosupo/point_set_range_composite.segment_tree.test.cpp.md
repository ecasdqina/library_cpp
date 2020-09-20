---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree.hpp
    title: data_structure/segment_tree.hpp
  - icon: ':heavy_check_mark:'
    path: data_structure/monoid.hpp
    title: data_structure/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: math/modint.hpp
  - icon: ':heavy_check_mark:'
    path: other/fast_io.hpp
    title: other/fast_io.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_composite
    links:
    - https://judge.yosupo.jp/problem/point_set_range_composite
  bundledCode: "#line 1 \"test/yosupo/point_set_range_composite.segment_tree.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n\n#line 2 \"data_structure/segment_tree.hpp\"\n\n#include <vector>\n#include\
    \ <cstdint>\n\n#line 2 \"data_structure/monoid.hpp\"\n\n#include <algorithm>\n\
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
    \ return monoid{x.a.inverse()}; }\n};\n}\n#line 7 \"data_structure/segment_tree.hpp\"\
    \n\nnamespace cplib {\ntemplate<class Monoid> class segment_tree {\npublic:\n\t\
    using value_type = Monoid;\n\tusing T = typename value_type::value_type;\n\tusing\
    \ usize = std::uint_fast32_t;\n\nprivate:\n\tint n;\n\tstd::vector<value_type>\
    \ data;\n\nprivate:\n\tusize base() const { return data.size() >> 1; }\n\npublic:\n\
    \tsegment_tree() = default;\n\texplicit segment_tree(usize n): n(n) {\n\t\tusize\
    \ size = 1;\n\t\twhile(size <= n) size <<= 1;\n\t\tdata.assign(size << 1, value_type::identity());\n\
    \t}\n\ttemplate<class InputIt> explicit segment_tree(InputIt first, InputIt last)\n\
    \t: segment_tree(std::distance(first, last)) {\n\t\tfor(int index = 0; first !=\
    \ last; first++, index++) set(index, *first);\n\t\tbuild();\n\t}\n\n\tusize size()\
    \ const { return n; }\n\tbool empty() const { return size() == 0; }\n\tvoid clear()\
    \ {\n\t\tn = 0;\n\t\tdata.clear();\n\t}\n\tvoid swap(segment_tree& r) {\n\t\t\
    std::swap(n, r.n);\n\t\tdata.swap(r.data);\n\t}\n\n\tT get(usize i) const { return\
    \ data[i + base()].a; }\n\tvoid set(usize i, const value_type& x) { data[i + base()]\
    \ = x; }\n\n\tvoid build() {\n\t\tfor(usize i = (int)base() - 1; i > 0; i--)\n\
    \t\t\tdata[i] = value_type::operation(data[i * 2 + 0], data[i * 2 + 1]);\n\t}\n\
    \tvoid change(usize i, const value_type& x) {\n\t\tdata[i += base()] = x;\n\t\t\
    while(i >>= 1) data[i] = value_type::operation(data[i * 2 + 0], data[i * 2 + 1]);\n\
    \t}\n\tvoid update(usize i, const value_type& x) { change(i, value_type::operation(get(i),\
    \ x)); }\n\n\tT fold(usize first, usize last) const {\n\t\tfirst += base();\n\t\
    \tlast += base();\n\n\t\tvalue_type lval = value_type::identity();\n\t\tvalue_type\
    \ rval = value_type::identity();\n\t\twhile(first != last) {\n\t\t\tif(first &\
    \ 1) lval = value_type::operation(lval, data[first++]);\n\t\t\tif(last  & 1) rval\
    \ = value_type::operation(data[--last], rval);\n\t\t\tfirst >>= 1;\n\t\t\tlast\
    \  >>= 1;\n\t\t}\n\t\treturn value_type::operation(lval, rval).a;\n\t}\n\tT fold_all()\
    \ const { return data[1].a; }\n\n\t// return max{r | f(fold(l, r - 1)) = true}\n\
    \ttemplate<class F> usize search_right(int l, const F& f) const {\n\t\tif(l ==\
    \ size()) return base();\n\n\t\tl += base();\n\t\tvalue_type acc = value_type::identity();\n\
    \t\tdo {\n\t\t\twhile(l % 2 == 0) l >>= 1;\n\t\t\tif(!f(value_type::operation(acc,\
    \ data[l]).a)) {\n\t\t\t\twhile(l < base()) {\n\t\t\t\t\tl = l << 1;\n\t\t\t\t\
    \tif(f(value_type::operation(acc, data[l]).a)) {\n\t\t\t\t\t\tacc = value_type::operation(acc,\
    \ data[l]);\n\t\t\t\t\t\tl += 1;\n\t\t\t\t\t}\n\t\t\t\t}\n\t\t\t\treturn l - base();\n\
    \t\t\t}\n\t\t\tacc = value_type::operation(acc, data[l]);\n\t\t\tl += 1;\n\t\t\
    } while((l & -l) != l);\n\t\treturn size();\n\t}\n\n\t// return min{l | f(fold(l,\
    \ r - 1) = true}\n\ttemplate<class F> usize search_left(int r, const F& f) const\
    \ {\n\t\tif(r == 0) return 0;\n\n\t\tr += base();\n\t\tvalue_type acc = value_type::identity();\n\
    \t\tdo {\n\t\t\tr--;\n\t\t\twhile(r > 1 and (r % 2)) r >>= 1;\n\t\t\tif(!f(value_type::operation(data[r],\
    \ acc).a)) {\n\t\t\t\twhile(r < base()) {\n\t\t\t\t\tr = r * 2 + 1;\n\t\t\t\t\t\
    if(f(value_type::operation(data[r], acc).a)) {\n\t\t\t\t\t\tacc = value_type::operation(data[r],\
    \ acc);\n\t\t\t\t\t\tr -= 1;\n\t\t\t\t\t}\n\t\t\t\t}\n\t\t\t\treturn r + 1 - base();\n\
    \t\t\t}\n\t\t\tacc = value_type::operation(data[r], acc);\n\t\t} while((r & -r)\
    \ == r);\n\t\treturn 0;\n\t}\n};\n}\n\n// @docs docs/segment_tree.md\n#line 1\
    \ \"math/modint.hpp\"\n\n\n\n#include <iostream>\n\ntemplate <std::uint_fast64_t\
    \ Modulus>\nclass modint {\n\tusing u32 = std::uint_fast32_t;\n\tusing u64 = std::uint_fast64_t;\n\
    \tusing i64 = std::int_fast64_t;\n\n\tinline u64 apply(i64 x) { return (x < 0\
    \ ? x + Modulus : x); };\n\npublic:\n\tu64 a;\n\tstatic constexpr u64 mod = Modulus;\n\
    \n\tconstexpr modint(const i64& x = 0) noexcept: a(apply(x % (i64)Modulus)) {}\n\
    \n\tconstexpr modint operator+(const modint& rhs) const noexcept { return modint(*this)\
    \ += rhs; }\n\tconstexpr modint operator-(const modint& rhs) const noexcept {\
    \ return modint(*this) -= rhs; }\t\n\tconstexpr modint operator*(const modint&\
    \ rhs) const noexcept { return modint(*this) *= rhs; }\n\tconstexpr modint operator/(const\
    \ modint& rhs) const noexcept { return modint(*this) /= rhs; }\n\tconstexpr modint\
    \ operator^(const u64& k) const noexcept { return modint(*this) ^= k; }\n\tconstexpr\
    \ modint operator^(const modint& k) const noexcept { return modint(*this) ^= k.value();\
    \ }\n\tconstexpr modint operator-() const noexcept { return modint(Modulus - a);\
    \ }\n\tconstexpr modint operator++() noexcept { return (*this) = modint(*this)\
    \ + 1; }\n\tconstexpr modint operator--() noexcept { return (*this) = modint(*this)\
    \ - 1; }\n\tconst bool operator==(const modint& rhs) const noexcept { return a\
    \ == rhs.a; };\n\tconst bool operator!=(const modint& rhs) const noexcept { return\
    \ a != rhs.a; };\n\tconst bool operator<=(const modint& rhs) const noexcept {\
    \ return a <= rhs.a; };\n\tconst bool operator>=(const modint& rhs) const noexcept\
    \ { return a >= rhs.a; };\n\tconst bool operator<(const modint& rhs) const noexcept\
    \ { return a < rhs.a; };\n\tconst bool operator>(const modint& rhs) const noexcept\
    \ { return a > rhs.a; };\n\tconstexpr modint& operator+=(const modint& rhs) noexcept\
    \ {\n\t\ta += rhs.a;\n\t\tif (a >= Modulus) a -= Modulus;\n\t\treturn *this;\n\
    \t}\n\tconstexpr modint& operator-=(const modint& rhs) noexcept {\n\t\tif (a <\
    \ rhs.a) a += Modulus;\n\t\ta -= rhs.a;\n\t\treturn *this;\n\t}\n\tconstexpr modint&\
    \ operator*=(const modint& rhs) noexcept {\n\t\ta = a * rhs.a % Modulus;\n\t\t\
    return *this;\n\t}\n\tconstexpr modint& operator/=(modint rhs) noexcept {\n\t\t\
    u64 exp = Modulus - 2;\n\t\twhile (exp) {\n\t\t\tif (exp % 2) (*this) *= rhs;\n\
    \t\t\t\n\t\t\trhs *= rhs;\n\t\t\texp /= 2;\n\t\t}\n\t\treturn *this;\n\t}\n\t\
    constexpr modint& operator^=(u64 k) noexcept {\n\t\tauto b = modint(1);\n\t\t\
    while(k) {\n\t\t\tif(k & 1) b = b * (*this);\n\t\t\t(*this) *= (*this);\n\t\t\t\
    k >>= 1;\n\t\t}\n\t\treturn (*this) = b;\n\t}\n\tconstexpr modint& operator=(const\
    \ modint& rhs) noexcept {\n\t\ta = rhs.a;\n\t\treturn (*this);\n\t}\n\n\tconstexpr\
    \ u64& value() noexcept { return a; }\n\tconstexpr const u64& value() const noexcept\
    \ { return a; }\n\texplicit operator bool() const { return a; }\n\texplicit operator\
    \ u32() const { return a; }\n\n\tconst modint inverse() const {\n\t\treturn modint(1)\
    \ / *this;\n\t}\n\tconst modint pow(i64 k) const {\n\t\treturn modint(*this) ^\
    \ k;\n\t}\n\n\tfriend std::ostream& operator<<(std::ostream& os, const modint&\
    \ p) {\n\t\treturn os << p.a;\n\t}\n\tfriend std::istream& operator>>(std::istream&\
    \ is, modint& p) {\n\t\tu64 t;\n\t\tis >> t;\n\t\tp = modint(t);\n\t\treturn is;\n\
    \t}\n};\n\n\n#line 1 \"other/fast_io.hpp\"\n\n\n\n#include <cstdio>\n#line 6 \"\
    other/fast_io.hpp\"\n#include <cstddef>\n#include <cstring>\n#include <limits>\n\
    #include <string>\n#include <type_traits>\n#include <utility>\n#line 13 \"other/fast_io.hpp\"\
    \n\nnamespace fast_io {\n\t// fast I/O by rsk0315 (update: 2020-03-02 01:10:54).\n\
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
    \n\n#line 6 \"test/yosupo/point_set_range_composite.segment_tree.test.cpp\"\n\n\
    using mint = modint<998244353>;\n\nstruct node {\n\tmint a, b;\n\n\tnode operator+(const\
    \ node& r) const { return node{r.a * a, r.a * b + r.b}; }\n\tmint eval(mint x)\
    \ { return a * x + b; }\n} id{1, 0};\n\nint main() {\n\tint n, q; fin.scan(n,\
    \ q);\n\n\tusing T = cplib::monoid<node, id>;\n\tcplib::segment_tree<T> seg(n);\n\
    \tfor(int i = 0; i < n; i++) {\n\t\tint a, b; fin.scan(a, b);\n\n\t\tseg.set(i,\
    \ node{a, b});\n\t}\n\tseg.build();\n\n\twhile(q--) {\n\t\tint type, x, y, z;\
    \ fin.scan(type, x, y, z);\n\n\t\tif(type == 0) seg.change(x, node{y, z});\n\t\
    \tif(type == 1) fout.println(seg.fold(x, y).eval(z).value());\n\t}\n\treturn 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n\n#include \"../../data_structure/segment_tree.hpp\"\n#include \"../../math/modint.hpp\"\
    \n#include \"../../other/fast_io.hpp\"\n\nusing mint = modint<998244353>;\n\n\
    struct node {\n\tmint a, b;\n\n\tnode operator+(const node& r) const { return\
    \ node{r.a * a, r.a * b + r.b}; }\n\tmint eval(mint x) { return a * x + b; }\n\
    } id{1, 0};\n\nint main() {\n\tint n, q; fin.scan(n, q);\n\n\tusing T = cplib::monoid<node,\
    \ id>;\n\tcplib::segment_tree<T> seg(n);\n\tfor(int i = 0; i < n; i++) {\n\t\t\
    int a, b; fin.scan(a, b);\n\n\t\tseg.set(i, node{a, b});\n\t}\n\tseg.build();\n\
    \n\twhile(q--) {\n\t\tint type, x, y, z; fin.scan(type, x, y, z);\n\n\t\tif(type\
    \ == 0) seg.change(x, node{y, z});\n\t\tif(type == 1) fout.println(seg.fold(x,\
    \ y).eval(z).value());\n\t}\n\treturn 0;\n}\n"
  dependsOn:
  - data_structure/segment_tree.hpp
  - data_structure/monoid.hpp
  - math/modint.hpp
  - other/fast_io.hpp
  isVerificationFile: true
  path: test/yosupo/point_set_range_composite.segment_tree.test.cpp
  requiredBy: []
  timestamp: '2020-09-21 01:52:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/point_set_range_composite.segment_tree.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/point_set_range_composite.segment_tree.test.cpp
- /verify/test/yosupo/point_set_range_composite.segment_tree.test.cpp.html
title: test/yosupo/point_set_range_composite.segment_tree.test.cpp
---
