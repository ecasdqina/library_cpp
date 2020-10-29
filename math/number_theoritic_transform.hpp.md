---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: math/modint.hpp
  - icon: ':heavy_check_mark:'
    path: math/polynomial.hpp
    title: math/polynomial.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/arbitary_mod_number_theoritic_transform.hpp
    title: math/arbitary_mod_number_theoritic_transform.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution_mod.test.cpp
    title: test/yosupo/convolution_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp
    title: test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/exp_of_formal_power_series.ntt.test.cpp
    title: test/yosupo/exp_of_formal_power_series.ntt.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/inv_of_formal_power_series.ntt.test.cpp
    title: test/yosupo/inv_of_formal_power_series.ntt.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/log_of_formal_power_series.ntt.test.cpp
    title: test/yosupo/log_of_formal_power_series.ntt.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/number_theoritic_transform.md
    links: []
  bundledCode: "#line 1 \"math/number_theoritic_transform.hpp\"\n\n\n\n#line 1 \"\
    math/modint.hpp\"\n\n\n\n#include <iostream>\n\ntemplate <std::uint_fast64_t Modulus>\n\
    class modint {\n\tusing u32 = std::uint_fast32_t;\n\tusing u64 = std::uint_fast64_t;\n\
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
    \t}\n};\n\n\n#line 1 \"math/polynomial.hpp\"\n\n\n\n#include <cstdint>\n#include\
    \ <vector>\n\ntemplate<class T>\nclass polynomial: public std::vector<T> {\npublic:\n\
    \tusing std::vector<T>::vector;\n\tusing value_type = typename std::vector<T>::value_type;\n\
    \tusing reference = typename std::vector<T>::reference;\n\tusing const_reference\
    \ = typename std::vector<T>::const_reference;\n\tusing size_type = typename std::vector<T>::size_type;\n\
    \nprivate:\n\tT eval(T x) const {\n\t\tT ret = (*this)[0], tmp = x;\n\t\tfor(int\
    \ i = 1; i < this->size(); i++) {\n\t\t\tret = ret + (*this)[i] * tmp;\n\t\t\t\
    tmp = tmp * x;\n\t\t}\n\t\treturn ret;\n\t}\n\npublic:\n\tpolynomial(): std::vector<T>(1,\
    \ T{}) {}\n\tpolynomial(const std::vector<T>& p): std::vector<T>(p) {}\n\n\tpolynomial\
    \ operator+(const polynomial& r) const { return polynomial(*this) += r; }\n\t\
    polynomial operator-(const polynomial& r) const { return polynomial(*this) -=\
    \ r; }\n\tpolynomial operator*(const_reference r) const { return polynomial(*this)\
    \ *= r; }\n\tpolynomial operator/(const_reference r) const { return polynomial(*this)\
    \ /= r; }\n\tpolynomial operator<<(size_type r) const { return polynomial(*this)\
    \ <<= r; }\n\tpolynomial operator>>(size_type r) const { return polynomial(*this)\
    \ >>= r; }\n\tpolynomial operator-() const {\n\t\tpolynomial ret(this->size());\n\
    \t\tfor(int i = 0; i < this->size(); i++) ret[i] = -(*this)[i];\n\t\treturn ret;\n\
    \t}\n\tpolynomial& operator+=(const polynomial& r) {\n\t\tif(r.size() > this->size())\
    \ this->resize(r.size());\n\t\tfor(int i = 0; i < r.size(); i++) (*this)[i] =\
    \ (*this)[i] + r[i];\n\t\treturn *this;\n\t}\n\tpolynomial& operator-=(const polynomial&\
    \ r) {\n\t\tif(r.size() > this->size()) this->resize(r.size());\n\t\tfor(int i\
    \ = 0; i < r.size(); i++) (*this)[i] = (*this)[i] - r[i];\n\t\treturn *this;\n\
    \t}\n\tpolynomial& operator*=(const_reference r) {\n\t\tfor(int i = 0; i < this->size();\
    \ i++) (*this)[i] = (*this)[i] * r;\n\t\treturn *this;\n\t}\n\tpolynomial& operator/=(const_reference\
    \ r) {\n\t\tfor(int i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] / r;\n\
    \t\treturn *this;\n\t}\n\tpolynomial& operator<<=(size_type r) {\n\t\tthis->insert(begin(*this),\
    \ r, T{});\n\t\treturn *this;\n\t}\n\tpolynomial& operator>>=(size_type r) {\n\
    \t\tif(r >= this->size()) clear();\n\t\telse this->erase(begin(*this), begin(*this)\
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
    \t}\n\t\n\tvoid shrink() {\n\t\twhile(this->size() > 1 and this->back() == T{})\
    \ this->pop_back();\n\t}\n\t\n\tT operator()(T x) const { return eval(x); }\n\t\
    size_type degree() const { return this->size() - 1; }\n\tvoid clear() { this->assign(1,\
    \ T{}); }\n};\n\n\n#line 6 \"math/number_theoritic_transform.hpp\"\n\ntemplate<class\
    \ T, int primitive_root = 3>\nclass number_theoritic_transform: public polynomial<T>\
    \ {\npublic:\n\tusing polynomial<T>::polynomial;\n\tusing value_type = typename\
    \ polynomial<T>::value_type;\n\tusing reference = typename polynomial<T>::reference;\n\
    \tusing const_reference = typename polynomial<T>::const_reference;\n\tusing size_type\
    \ = typename polynomial<T>::size_type;\n\nprivate:\n\tvoid ntt(number_theoritic_transform&\
    \ a) const {\n\t\tint N = a.size();\n\t\tstatic std::vector<T> dw;\n\t\tif(dw.size()\
    \ < N) {\n\t\t\tint n = dw.size();\n\t\t\tdw.resize(N);\n\t\t\tfor(int i = n;\
    \ i < N; i++) dw[i] = -(T(primitive_root) ^ ((T::mod - 1) >> i + 2));\n\t\t}\n\
    \n\t\tfor(int m = N; m >>= 1;) {\n\t\t\tT w = 1;\n\t\t\tfor(int s = 0, k = 0;\
    \ s < N; s += 2 * m) {\n\t\t\t\tfor(int i = s, j = s + m; i < s + m; i++, j++)\
    \ {\n\t\t\t\t\tT x = a[i], y = a[j] * w;\n\t\t\t\t\ta[i] = x + y;\n\t\t\t\t\t\
    a[j] = x - y;\n\t\t\t\t}\n\t\t\t\tw *= dw[__builtin_ctz(++k)];\n\t\t\t}\n\t\t\
    }\n\t}\n\tvoid intt(number_theoritic_transform& a) const {\n\t\tint N = a.size();\n\
    \t\tstatic std::vector<T> idw;\n\t\tif(idw.size() < N) {\n\t\t\tint n = idw.size();\n\
    \t\t\tidw.resize(N);\n\t\t\tfor(int i = n; i < N; i++) idw[i] = (-(T(primitive_root)\
    \ ^ ((T::mod - 1) >> i + 2))).inverse();\n\t\t}\n\n\t\tfor(int m = 1; m < N; m\
    \ *= 2) {\n\t\t\tT w = 1;\n\t\t\tfor(int s = 0, k = 0; s < N; s += 2 * m) {\n\t\
    \t\t\tfor(int i = s, j = s + m; i < s + m; i++, j++) {\n\t\t\t\t\tT x = a[i],\
    \ y = a[j];\n\t\t\t\t\ta[i] = x + y;\n\t\t\t\t\ta[j] = (x - y) * w;\n\t\t\t\t\
    }\n\t\t\t\tw *= idw[__builtin_ctz(++k)];\n\t\t\t}\n\t\t}\n\t}\n\tvoid transform(number_theoritic_transform&\
    \ a, bool inverse = false) const {\n\t\tsize_type n = 0;\n\t\twhile((1 << n) <\
    \ a.size()) n++;\n\t\tsize_type N = 1 << n;\n\t\ta.resize(N);\n\n\t\tif(!inverse)\
    \ {\n\t\t\tntt(a);\n\t\t} else {\n\t\t\tintt(a);\n\t\t\tT inv = T(N).inverse();\n\
    \t\t\tfor(int i = 0; i < a.size(); i++) a[i] *= inv;\n\t\t}\n\t}\n\n\tnumber_theoritic_transform\
    \ convolution(const number_theoritic_transform& ar, const number_theoritic_transform&\
    \ br) const {\n\t\tsize_type size = ar.degree() + br.degree() + 1;\n\t\tnumber_theoritic_transform\
    \ a(ar), b(br);\n\t\ta.resize(size);\n\t\tb.resize(size);\n\t\ttransform(a, false);\n\
    \t\ttransform(b, false);\n\n\t\tfor(int i = 0; i < a.size(); i++) a[i] *= b[i];\n\
    \t\ttransform(a, true);\n\t\ta.resize(size);\n\t\treturn a;\n\t}\n\npublic:\n\t\
    number_theoritic_transform(const polynomial<T>& p): polynomial<T>(p) {}\n\t\n\t\
    number_theoritic_transform operator*(const_reference r) const { return number_theoritic_transform(*this)\
    \ *= r; }\n\tnumber_theoritic_transform& operator*=(const_reference r) {\n\t\t\
    for(int i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] * r;\n\t\treturn\
    \ *this;\n\t}\n\tnumber_theoritic_transform operator*(const number_theoritic_transform&\
    \ r) const { return number_theoritic_transform(*this) *= r; }\n\tnumber_theoritic_transform&\
    \ operator*=(const number_theoritic_transform& r) {\n\t\treturn (*this) = convolution((*this),\
    \ r);\n\t}\n};\n\n// @docs docs/number_theoritic_transform.md\n\n\n"
  code: "#ifndef INCLUDED_NUMBER_THEORITIC_TRANSFORM_HPP\n#define INCLUDED_NUMBER_THEORITIC_TRANSFORM_HPP\n\
    \n#include \"../math/modint.hpp\"\n#include \"../math/polynomial.hpp\"\n\ntemplate<class\
    \ T, int primitive_root = 3>\nclass number_theoritic_transform: public polynomial<T>\
    \ {\npublic:\n\tusing polynomial<T>::polynomial;\n\tusing value_type = typename\
    \ polynomial<T>::value_type;\n\tusing reference = typename polynomial<T>::reference;\n\
    \tusing const_reference = typename polynomial<T>::const_reference;\n\tusing size_type\
    \ = typename polynomial<T>::size_type;\n\nprivate:\n\tvoid ntt(number_theoritic_transform&\
    \ a) const {\n\t\tint N = a.size();\n\t\tstatic std::vector<T> dw;\n\t\tif(dw.size()\
    \ < N) {\n\t\t\tint n = dw.size();\n\t\t\tdw.resize(N);\n\t\t\tfor(int i = n;\
    \ i < N; i++) dw[i] = -(T(primitive_root) ^ ((T::mod - 1) >> i + 2));\n\t\t}\n\
    \n\t\tfor(int m = N; m >>= 1;) {\n\t\t\tT w = 1;\n\t\t\tfor(int s = 0, k = 0;\
    \ s < N; s += 2 * m) {\n\t\t\t\tfor(int i = s, j = s + m; i < s + m; i++, j++)\
    \ {\n\t\t\t\t\tT x = a[i], y = a[j] * w;\n\t\t\t\t\ta[i] = x + y;\n\t\t\t\t\t\
    a[j] = x - y;\n\t\t\t\t}\n\t\t\t\tw *= dw[__builtin_ctz(++k)];\n\t\t\t}\n\t\t\
    }\n\t}\n\tvoid intt(number_theoritic_transform& a) const {\n\t\tint N = a.size();\n\
    \t\tstatic std::vector<T> idw;\n\t\tif(idw.size() < N) {\n\t\t\tint n = idw.size();\n\
    \t\t\tidw.resize(N);\n\t\t\tfor(int i = n; i < N; i++) idw[i] = (-(T(primitive_root)\
    \ ^ ((T::mod - 1) >> i + 2))).inverse();\n\t\t}\n\n\t\tfor(int m = 1; m < N; m\
    \ *= 2) {\n\t\t\tT w = 1;\n\t\t\tfor(int s = 0, k = 0; s < N; s += 2 * m) {\n\t\
    \t\t\tfor(int i = s, j = s + m; i < s + m; i++, j++) {\n\t\t\t\t\tT x = a[i],\
    \ y = a[j];\n\t\t\t\t\ta[i] = x + y;\n\t\t\t\t\ta[j] = (x - y) * w;\n\t\t\t\t\
    }\n\t\t\t\tw *= idw[__builtin_ctz(++k)];\n\t\t\t}\n\t\t}\n\t}\n\tvoid transform(number_theoritic_transform&\
    \ a, bool inverse = false) const {\n\t\tsize_type n = 0;\n\t\twhile((1 << n) <\
    \ a.size()) n++;\n\t\tsize_type N = 1 << n;\n\t\ta.resize(N);\n\n\t\tif(!inverse)\
    \ {\n\t\t\tntt(a);\n\t\t} else {\n\t\t\tintt(a);\n\t\t\tT inv = T(N).inverse();\n\
    \t\t\tfor(int i = 0; i < a.size(); i++) a[i] *= inv;\n\t\t}\n\t}\n\n\tnumber_theoritic_transform\
    \ convolution(const number_theoritic_transform& ar, const number_theoritic_transform&\
    \ br) const {\n\t\tsize_type size = ar.degree() + br.degree() + 1;\n\t\tnumber_theoritic_transform\
    \ a(ar), b(br);\n\t\ta.resize(size);\n\t\tb.resize(size);\n\t\ttransform(a, false);\n\
    \t\ttransform(b, false);\n\n\t\tfor(int i = 0; i < a.size(); i++) a[i] *= b[i];\n\
    \t\ttransform(a, true);\n\t\ta.resize(size);\n\t\treturn a;\n\t}\n\npublic:\n\t\
    number_theoritic_transform(const polynomial<T>& p): polynomial<T>(p) {}\n\t\n\t\
    number_theoritic_transform operator*(const_reference r) const { return number_theoritic_transform(*this)\
    \ *= r; }\n\tnumber_theoritic_transform& operator*=(const_reference r) {\n\t\t\
    for(int i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] * r;\n\t\treturn\
    \ *this;\n\t}\n\tnumber_theoritic_transform operator*(const number_theoritic_transform&\
    \ r) const { return number_theoritic_transform(*this) *= r; }\n\tnumber_theoritic_transform&\
    \ operator*=(const number_theoritic_transform& r) {\n\t\treturn (*this) = convolution((*this),\
    \ r);\n\t}\n};\n\n// @docs docs/number_theoritic_transform.md\n\n#endif\n"
  dependsOn:
  - math/modint.hpp
  - math/polynomial.hpp
  isVerificationFile: false
  path: math/number_theoritic_transform.hpp
  requiredBy:
  - math/arbitary_mod_number_theoritic_transform.hpp
  timestamp: '2020-03-20 12:55:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/exp_of_formal_power_series.ntt.test.cpp
  - test/yosupo/log_of_formal_power_series.ntt.test.cpp
  - test/yosupo/convolution_mod.test.cpp
  - test/yosupo/inv_of_formal_power_series.ntt.test.cpp
  - test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp
documentation_of: math/number_theoritic_transform.hpp
layout: document
redirect_from:
- /library/math/number_theoritic_transform.hpp
- /library/math/number_theoritic_transform.hpp.html
title: math/number_theoritic_transform.hpp
---
