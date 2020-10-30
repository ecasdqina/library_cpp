---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: math/formal_power_series.hpp
    title: math/formal_power_series.hpp
  - icon: ':x:'
    path: math/modint.hpp
    title: math/modint.hpp
  - icon: ':x:'
    path: math/number_theoritic_transform.hpp
    title: math/number_theoritic_transform.hpp
  - icon: ':x:'
    path: math/polynomial.hpp
    title: math/polynomial.hpp
  - icon: ':question:'
    path: other/fast_io.hpp
    title: other/fast_io.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/inv_of_formal_power_series
    links:
    - https://judge.yosupo.jp/problem/inv_of_formal_power_series
  bundledCode: "#line 1 \"test/yosupo/inv_of_formal_power_series.ntt.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/inv_of_formal_power_series\"\
    \n\n#line 1 \"math/number_theoritic_transform.hpp\"\n\n\n\n#line 1 \"math/modint.hpp\"\
    \n\n\n\n#include <iostream>\n\nnamespace cplib {\ntemplate <std::uint_fast64_t\
    \ Modulus>\nclass modint {\n\tusing u32 = std::uint_fast32_t;\n\tusing u64 = std::uint_fast64_t;\n\
    \tusing i64 = std::int_fast64_t;\n\n\tinline u64 apply(i64 x) { return (x < 0\
    \ ? x + Modulus : x); };\n\npublic:\n\tu64 a;\n\tstatic constexpr u64 mod = Modulus;\n\
    \n\tconstexpr modint(const i64& x = 0) noexcept: a(apply(x % (i64)Modulus)) {}\n\
    \n\tconstexpr modint operator+(const modint& rhs) const noexcept { return modint(*this)\
    \ += rhs; }\n\tconstexpr modint operator-(const modint& rhs) const noexcept {\
    \ return modint(*this) -= rhs; }\n\tconstexpr modint operator*(const modint& rhs)\
    \ const noexcept { return modint(*this) *= rhs; }\n\tconstexpr modint operator/(const\
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
    \n\t\t\trhs *= rhs;\n\t\t\texp /= 2;\n\t\t}\n\t\treturn *this;\n\t}\n\tconstexpr\
    \ modint& operator^=(u64 k) noexcept {\n\t\tauto b = modint(1);\n\t\twhile(k)\
    \ {\n\t\t\tif(k & 1) b = b * (*this);\n\t\t\t(*this) *= (*this);\n\t\t\tk >>=\
    \ 1;\n\t\t}\n\t\treturn (*this) = b;\n\t}\n\tconstexpr modint& operator=(const\
    \ modint& rhs) noexcept {\n\t\ta = rhs.a;\n\t\treturn (*this);\n\t}\n\n\tconstexpr\
    \ u64& value() noexcept { return a; }\n\tconstexpr const u64& value() const noexcept\
    \ { return a; }\n\texplicit operator bool() const { return a; }\n\texplicit operator\
    \ u32() const { return a; }\n\n\tconst modint inverse() const {\n\t\treturn modint(1)\
    \ / *this;\n\t}\n\tconst modint pow(i64 k) const {\n\t\treturn modint(*this) ^\
    \ k;\n\t}\n\n\tfriend std::ostream& operator<<(std::ostream& os, const modint&\
    \ p) {\n\t\treturn os << p.a;\n\t}\n\tfriend std::istream& operator>>(std::istream&\
    \ is, modint& p) {\n\t\tu64 t;\n\t\tis >> t;\n\t\tp = modint(t);\n\t\treturn is;\n\
    \t}\n};\n}\n\n\n#line 1 \"math/polynomial.hpp\"\n\n\n\n#include <cstdint>\n#include\
    \ <vector>\n\nnamespace cplib {\ntemplate<class T>\nclass polynomial: public std::vector<T>\
    \ {\npublic:\n\tusing std::vector<T>::vector;\n\tusing value_type = typename std::vector<T>::value_type;\n\
    \tusing reference = typename std::vector<T>::reference;\n\tusing const_reference\
    \ = typename std::vector<T>::const_reference;\n\tusing size_type = typename std::vector<T>::size_type;\n\
    \nprivate:\n\tT eval(T x) const {\n\t\tT ret = (*this)[0], tmp = x;\n\t\tfor(int\
    \ i = 1; i < this->size(); i++) {\n\t\t\tret = ret + (*this)[i] * tmp;\n\t\t\t\
    tmp = tmp * x;\n\t\t}\n\t\treturn ret;\n\t}\n\npublic:\n\tpolynomial(const std::vector<T>&\
    \ p): std::vector<T>(p) {}\n\n\tsize_type nonzeros() const {\n\t\tsize_type ret\
    \ = 0;\n\t\tfor(int i = 0; i < this->size(); i++) {\n\t\t\tif((*this)[i] != T{})\
    \ ret++;\n\t\t}\n\t\treturn ret;\n\t}\n\n\tstatic polynomial<T> one() { return\
    \ term(0); }\n\tstatic polynomial<T> zero() { return polynomial<T>({T{0}}); }\n\
    \tstatic polynomial<T> term(int k) { return polynomial<T>({T{1}}) << k; }\n\n\
    public:\n\tpolynomial operator+(const polynomial& r) const { return polynomial(*this)\
    \ += r; }\n\tpolynomial operator+(const_reference r) const { return polynomial(*this)\
    \ += r; }\n\tpolynomial operator-(const polynomial& r) const { return polynomial(*this)\
    \ -= r; }\n\tpolynomial operator-(const_reference r) const { return polynomial(*this)\
    \ -= r; }\n\tpolynomial operator*(const_reference r) const { return polynomial(*this)\
    \ *= r; }\n\tpolynomial operator/(const_reference r) const { return polynomial(*this)\
    \ /= r; }\n\tpolynomial operator<<(size_type r) const { return polynomial(*this)\
    \ <<= r; }\n\tpolynomial operator>>(size_type r) const { return polynomial(*this)\
    \ >>= r; }\n\tpolynomial operator-() const {\n\t\tpolynomial ret(this->size());\n\
    \t\tfor(int i = 0; i < this->size(); i++) ret[i] = -(*this)[i];\n\t\treturn ret;\n\
    \t}\n\tpolynomial& operator+=(const polynomial& r) {\n\t\tif(r.size() > this->size())\
    \ this->resize(r.size());\n\t\tfor(int i = 0; i < r.size(); i++) (*this)[i] =\
    \ (*this)[i] + r[i];\n\t\treturn *this;\n\t}\n\tpolynomial& operator+=(const_reference\
    \ r) {\n\t\t(*this)[0] += r;\n\t\treturn *this;\n\t}\n\tpolynomial& operator-=(const\
    \ polynomial& r) {\n\t\tif(r.size() > this->size()) this->resize(r.size());\n\t\
    \tfor(int i = 0; i < r.size(); i++) (*this)[i] = (*this)[i] - r[i];\n\t\treturn\
    \ *this;\n\t}\n\tpolynomial& operator-=(const_reference r) {\n\t\t(*this)[0] -=\
    \ r;\n\t\treturn *this;\n\t}\n\tpolynomial& operator*=(const_reference r) {\n\t\
    \tfor(int i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] * r;\n\t\treturn\
    \ *this;\n\t}\n\tpolynomial& operator/=(const_reference r) {\n\t\tfor(int i =\
    \ 0; i < this->size(); i++) (*this)[i] = (*this)[i] / r;\n\t\treturn *this;\n\t\
    }\n\tpolynomial& operator<<=(size_type r) {\n\t\tthis->insert(begin(*this), r,\
    \ T{});\n\t\treturn *this;\n\t}\n\tpolynomial& operator>>=(size_type r) {\n\t\t\
    if(r >= this->size()) clear();\n\t\telse this->erase(begin(*this), begin(*this)\
    \ + r);\n\t\treturn *this;\n\t}\n\n\tpolynomial differential(size_type k) const\
    \ {\n\t\tpolynomial ret(*this);\n\t\tfor(int i = 0; i < k; i++) ret = ret.differential();\n\
    \t\treturn ret;\n\t}\n\tpolynomial differential() const {\n\t\tif(degree() < 1)\
    \ return polynomial();\n\t\tpolynomial ret(this->size() - 1);\n\t\tfor(int i =\
    \ 1; i < this->size(); i++) ret[i - 1] = (*this)[i] * T{i};\n\t\treturn ret;\n\
    \t}\n\tpolynomial integral(size_type k) const {\n\t\tpolynomial ret(*this);\n\t\
    \tfor(int i = 0; i < k; i++) ret = ret.integral();\n\t\treturn ret;\n\t}\n\tpolynomial\
    \ integral() const {\n\t\tpolynomial ret(this->size() + 1);\n\t\tfor(int i = 0;\
    \ i < this->size(); i++) ret[i + 1] = (*this)[i] / T{i + 1};\n\t\treturn ret;\n\
    \t}\n\tpolynomial prefix(size_type size) const {\n\t\tif(size == 0) return polynomial();\n\
    \t\treturn polynomial(begin(*this), begin(*this) + std::min(this->size(), size));\n\
    \t}\n\tvoid shrink() {\n\t\twhile(this->size() > 1 and this->back() == T{}) this->pop_back();\n\
    \t}\n\npublic:\n\tT operator()(T x) const { return eval(x); }\n\tsize_type degree()\
    \ const { return this->size() - 1; }\n\tvoid clear() { this->assign(1, T{}); }\n\
    };\n}\n\n\n#line 6 \"math/number_theoritic_transform.hpp\"\n\nnamespace cplib\
    \ {\ntemplate<class T, int primitive_root = 3>\nclass number_theoritic_transform:\
    \ public polynomial<T> {\npublic:\n\tusing polynomial<T>::polynomial;\n\tusing\
    \ value_type \t  = typename polynomial<T>::value_type;\n\tusing reference \t \
    \ = typename polynomial<T>::reference;\n\tusing const_reference = typename polynomial<T>::const_reference;\n\
    \tusing size_type \t  = typename polynomial<T>::size_type;\n\nprivate:\n\tvoid\
    \ ntt(number_theoritic_transform& a) const {\n\t\tint N = a.size();\n\t\tstatic\
    \ std::vector<T> dw;\n\t\tif(dw.size() < N) {\n\t\t\tint n = dw.size();\n\t\t\t\
    dw.resize(N);\n\t\t\tfor(int i = n; i < N; i++) dw[i] = -(T(primitive_root) ^\
    \ ((T::mod - 1) >> i + 2));\n\t\t}\n\n\t\tfor(int m = N; m >>= 1;) {\n\t\t\tT\
    \ w = 1;\n\t\t\tfor(int s = 0, k = 0; s < N; s += 2 * m) {\n\t\t\t\tfor(int i\
    \ = s, j = s + m; i < s + m; i++, j++) {\n\t\t\t\t\tT x = a[i], y = a[j] * w;\n\
    \t\t\t\t\ta[i] = x + y;\n\t\t\t\t\ta[j] = x - y;\n\t\t\t\t}\n\t\t\t\tw *= dw[__builtin_ctz(++k)];\n\
    \t\t\t}\n\t\t}\n\t}\n\tvoid intt(number_theoritic_transform& a) const {\n\t\t\
    int N = a.size();\n\t\tstatic std::vector<T> idw;\n\t\tif(idw.size() < N) {\n\t\
    \t\tint n = idw.size();\n\t\t\tidw.resize(N);\n\t\t\tfor(int i = n; i < N; i++)\
    \ idw[i] = (-(T(primitive_root) ^ ((T::mod - 1) >> i + 2))).inverse();\n\t\t}\n\
    \n\t\tfor(int m = 1; m < N; m *= 2) {\n\t\t\tT w = 1;\n\t\t\tfor(int s = 0, k\
    \ = 0; s < N; s += 2 * m) {\n\t\t\t\tfor(int i = s, j = s + m; i < s + m; i++,\
    \ j++) {\n\t\t\t\t\tT x = a[i], y = a[j];\n\t\t\t\t\ta[i] = x + y;\n\t\t\t\t\t\
    a[j] = (x - y) * w;\n\t\t\t\t}\n\t\t\t\tw *= idw[__builtin_ctz(++k)];\n\t\t\t\
    }\n\t\t}\n\t}\n\tvoid transform(number_theoritic_transform& a, bool inverse =\
    \ false) const {\n\t\tsize_type n = 0;\n\t\twhile((1 << n) < a.size()) n++;\n\t\
    \tsize_type N = 1 << n;\n\t\ta.resize(N);\n\n\t\tif(!inverse) {\n\t\t\tntt(a);\n\
    \t\t} else {\n\t\t\tintt(a);\n\t\t\tT inv = T(N).inverse();\n\t\t\tfor(int i =\
    \ 0; i < a.size(); i++) a[i] *= inv;\n\t\t}\n\t}\n\n\tnumber_theoritic_transform\
    \ convolution(const number_theoritic_transform& ar, const number_theoritic_transform&\
    \ br) const {\n\t\tsize_type size = ar.degree() + br.degree() + 1;\n\t\tnumber_theoritic_transform\
    \ a(ar), b(br);\n\t\ta.resize(size);\n\t\tb.resize(size);\n\n\t\tif(br.nonzeros()\
    \ < 5) {\n\t\t\ta.assign(size, T{});\n\t\t\tfor(int i = 0; i < br.size(); i++)\
    \ {\n\t\t\t\tif(br[i] == T{}) continue;\n\t\t\t\tfor(int j = 0; j < ar.size();\
    \ j++) {\n\t\t\t\t\ta[i + j] += br[i] * ar[j];\n\t\t\t\t}\n\t\t\t}\n\t\t\treturn\
    \ a;\n\t\t}\n\t\tif(ar.nonzeros() < 5) {\n\t\t\ta.assign(size, T{});\n\t\t\tfor(int\
    \ i = 0; i < ar.size(); i++) {\n\t\t\t\tif(ar[i] == T{}) continue;\n\t\t\t\tfor(int\
    \ j = 0; j < br.size(); j++) {\n\t\t\t\t\ta[i + j] += ar[i] * br[j];\n\t\t\t\t\
    }\n\t\t\t}\n\t\t\treturn a;\n\t\t}\n\n\t\ttransform(a, false);\n\t\ttransform(b,\
    \ false);\n\n\t\tfor(int i = 0; i < a.size(); i++) a[i] *= b[i];\n\t\ttransform(a,\
    \ true);\n\t\ta.resize(size);\n\t\treturn a;\n\t}\n\npublic:\n\tnumber_theoritic_transform(const\
    \ polynomial<T>& p): polynomial<T>(p) {}\n\n\tnumber_theoritic_transform operator*(const_reference\
    \ r) const { return number_theoritic_transform(*this) *= r; }\n\tnumber_theoritic_transform&\
    \ operator*=(const_reference r) {\n\t\tfor(int i = 0; i < this->size(); i++) (*this)[i]\
    \ = (*this)[i] * r;\n\t\treturn *this;\n\t}\n\tnumber_theoritic_transform operator*(const\
    \ number_theoritic_transform& r) const { return number_theoritic_transform(*this)\
    \ *= r; }\n\tnumber_theoritic_transform& operator*=(const number_theoritic_transform&\
    \ r) {\n\t\treturn (*this) = convolution((*this), r);\n\t}\n};\n}\n// @docs docs/number_theoritic_transform.md\n\
    \n\n#line 1 \"math/formal_power_series.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <utility>\n\ntemplate<class T>\nclass formal_power_series: public T {\npublic:\n\
    \tusing T::T;\n\tusing value_type = typename T::value_type;\n\tusing reference\
    \ = typename T::reference;\n\tusing const_reference = typename T::const_reference;\n\
    \tusing size_type = typename T::size_type;\n\nprivate:\n\tformal_power_series():\
    \ T(1) {}\n\tformal_power_series(const T& p): T(p) {}\n\npublic:\n\tformal_power_series\
    \ inverse() const {\n\t\tassert((*this)[0] != value_type{});\n\n\t\tformal_power_series\
    \ ret(1, (*this)[0].inverse());\n\t\tfor(int i = 1; i < this->size(); i <<= 1)\
    \ {\n\t\t\tauto tmp = ret * this->prefix(i << 1);\n\t\t\tfor(int j = 0; j < i;\
    \ j++) {\n\t\t\t\ttmp[j] = value_type{};\n\t\t\t\tif(j + i < tmp.size()) tmp[j\
    \ + i] *= value_type(-1);\n\t\t\t}\n\t\t\ttmp = tmp * ret;\n\t\t\tfor(int j =\
    \ 0; j < i; j++) tmp[j] = ret[j];\n\t\t\tret = std::move(tmp).prefix(i << 1);\n\
    \t\t}\n\t\treturn ret.prefix(this->size());\n\t}\n\tformal_power_series log()\
    \ const {\n\t\tassert((*this)[0] == value_type(1));\n\t\t\n\t\treturn (formal_power_series(this->differential())\
    \ * this->inverse()).integral().prefix(this->size());\n\t}\n\tformal_power_series\
    \ exp() const {\n\t\tassert((*this)[0] == value_type{});\n\n\t\tformal_power_series\
    \ f(1, value_type(1)), g(1, value_type(1));\n\t\tfor(int i = 1; i < this->size();\
    \ i <<= 1) {\n\t\t\tg = (g * value_type(2) - f * g * g).prefix(i);\n\t\t\tformal_power_series\
    \ q = this->differential().prefix(i - 1);\n\t\t\tformal_power_series w = (q +\
    \ g * (f.differential() - f * q)).prefix((i << 1) - 1);\n\t\t\tf = (f + f * (*this\
    \ - w.integral()).prefix(i << 1)).prefix(i << 1);\n\n\t\t}\n\t\treturn f.prefix(this->size());\n\
    \t}\n\tformal_power_series pow(size_type k) const {\n\t\tfor(size_type i = 0;\
    \ i < this->size(); i++) {\n\t\t\tif((*this)[i] != value_type{}) {\n\t\t\t\tvalue_type\
    \ inv = (*this)[i].inverse();\n\t\t\t\tformal_power_series f(*this * inv);\n\t\
    \t\t\tformal_power_series g(f >> i);\n\t\t\t\tg = formal_power_series(g.log()\
    \ * value_type(k)).exp() * (*this)[i].pow(k);\n\t\t\t\tif(i * k > this->size())\
    \ return formal_power_series(this->size());\n\n\t\t\t\treturn (g << (i * k)).prefix(this->size());\n\
    \t\t\t}\n\t\t}\n\t\treturn *this;\n\t}\n};\n\n// @docs docs/formal_power_series.md\n\
    \n\n#line 1 \"other/fast_io.hpp\"\n\n\n\n#include <cstdio>\n#line 6 \"other/fast_io.hpp\"\
    \n#include <cstddef>\n#include <cstring>\n#include <limits>\n#include <string>\n\
    #include <type_traits>\n#line 13 \"other/fast_io.hpp\"\n\nnamespace fast_io {\n\
    \t// fast I/O by rsk0315 (update: 2020-03-02 01:10:54).\n\tstatic size_t constexpr\
    \ buf_size = 1 << 17;\n\tstatic size_t constexpr margin = 1;\n\tstatic char inbuf[buf_size\
    \ + margin] = {};\n\tstatic char outbuf[buf_size + margin] = {};\n\tstatic __attribute__((aligned(8)))\
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
    \n\n#line 6 \"test/yosupo/inv_of_formal_power_series.ntt.test.cpp\"\n\nusing fps\
    \ = formal_power_series<number_theoritic_transform<modint<998244353>>>;\n\nint\
    \ main() {\n\tint n; fin.scan(n);\n\tfps a(n);\n\tfor(int i = 0; i < n; i++) {\n\
    \t\tint x; fin.scan(x);\n\n\t\ta[i] = x;\n\t}\n\n\tfor(auto v: a.inverse()) fout.print(v.value(),\
    \ ' ');\n\tfout.println();\n\treturn 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/inv_of_formal_power_series\"\
    \n\n#include \"../../math/number_theoritic_transform.hpp\"\n#include \"../../math/formal_power_series.hpp\"\
    \n#include \"../../other/fast_io.hpp\"\n\nusing fps = formal_power_series<number_theoritic_transform<modint<998244353>>>;\n\
    \nint main() {\n\tint n; fin.scan(n);\n\tfps a(n);\n\tfor(int i = 0; i < n; i++)\
    \ {\n\t\tint x; fin.scan(x);\n\n\t\ta[i] = x;\n\t}\n\n\tfor(auto v: a.inverse())\
    \ fout.print(v.value(), ' ');\n\tfout.println();\n\treturn 0;\n}\n"
  dependsOn:
  - math/number_theoritic_transform.hpp
  - math/modint.hpp
  - math/polynomial.hpp
  - math/formal_power_series.hpp
  - other/fast_io.hpp
  isVerificationFile: true
  path: test/yosupo/inv_of_formal_power_series.ntt.test.cpp
  requiredBy: []
  timestamp: '2020-10-30 17:19:30+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/yosupo/inv_of_formal_power_series.ntt.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/inv_of_formal_power_series.ntt.test.cpp
- /verify/test/yosupo/inv_of_formal_power_series.ntt.test.cpp.html
title: test/yosupo/inv_of_formal_power_series.ntt.test.cpp
---
