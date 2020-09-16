---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/polynomial.hpp
    title: math/polynomial.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    _deprecated_at_docs: docs/fast_fourier_transform.md
    links: []
  bundledCode: "#line 1 \"math/fast_fourier_transform.hpp\"\n\n\n\n#line 1 \"math/polynomial.hpp\"\
    \n\n\n\n#include <cstdint>\n#include <vector>\n\ntemplate<class T>\nclass polynomial:\
    \ public std::vector<T> {\npublic:\n\tusing std::vector<T>::vector;\n\tusing value_type\
    \ = typename std::vector<T>::value_type;\n\tusing reference = typename std::vector<T>::reference;\n\
    \tusing const_reference = typename std::vector<T>::const_reference;\n\tusing size_type\
    \ = typename std::vector<T>::size_type;\n\nprivate:\n\tT eval(T x) const {\n\t\
    \tT ret = (*this)[0], tmp = x;\n\t\tfor(int i = 1; i < this->size(); i++) {\n\t\
    \t\tret = ret + (*this)[i] * tmp;\n\t\t\ttmp = tmp * x;\n\t\t}\n\t\treturn ret;\n\
    \t}\n\npublic:\n\tpolynomial(): std::vector<T>(1, T{}) {}\n\tpolynomial(const\
    \ std::vector<T>& p): std::vector<T>(p) {}\n\n\tpolynomial operator+(const polynomial&\
    \ r) const { return polynomial(*this) += r; }\n\tpolynomial operator-(const polynomial&\
    \ r) const { return polynomial(*this) -= r; }\n\tpolynomial operator*(const_reference\
    \ r) const { return polynomial(*this) *= r; }\n\tpolynomial operator/(const_reference\
    \ r) const { return polynomial(*this) /= r; }\n\tpolynomial operator<<(size_type\
    \ r) const { return polynomial(*this) <<= r; }\n\tpolynomial operator>>(size_type\
    \ r) const { return polynomial(*this) >>= r; }\n\tpolynomial operator-() const\
    \ {\n\t\tpolynomial ret(this->size());\n\t\tfor(int i = 0; i < this->size(); i++)\
    \ ret[i] = -(*this)[i];\n\t\treturn ret;\n\t}\n\tpolynomial& operator+=(const\
    \ polynomial& r) {\n\t\tif(r.size() > this->size()) this->resize(r.size());\n\t\
    \tfor(int i = 0; i < r.size(); i++) (*this)[i] = (*this)[i] + r[i];\n\t\treturn\
    \ *this;\n\t}\n\tpolynomial& operator-=(const polynomial& r) {\n\t\tif(r.size()\
    \ > this->size()) this->resize(r.size());\n\t\tfor(int i = 0; i < r.size(); i++)\
    \ (*this)[i] = (*this)[i] - r[i];\n\t\treturn *this;\n\t}\n\tpolynomial& operator*=(const_reference\
    \ r) {\n\t\tfor(int i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] * r;\n\
    \t\treturn *this;\n\t}\n\tpolynomial& operator/=(const_reference r) {\n\t\tfor(int\
    \ i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] / r;\n\t\treturn *this;\n\
    \t}\n\tpolynomial& operator<<=(size_type r) {\n\t\tthis->insert(begin(*this),\
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
    \ T{}); }\n};\n\n\n#line 5 \"math/fast_fourier_transform.hpp\"\n#include <complex>\n\
    \ntemplate<class T, class Real = double, class Complex = std::complex<Real>>\n\
    class fast_fourier_transform: public polynomial<T> {\npublic:\n\tusing polynomial<T>::polynomial;\n\
    \tusing value_type = typename polynomial<T>::value_type;\n\tusing reference =\
    \ typename polynomial<T>::reference;\n\tusing const_reference = typename polynomial<T>::const_reference;\n\
    \tusing size_type = typename polynomial<T>::size_type;\n\nprivate:\n\t// constexpr\
    \ Real PI = std::numbers::pi_v<Real>;\n\tstatic constexpr Real PI = std::acos(Real(-1));;\n\
    \t\n\tvoid transform(polynomial<Complex>& a, bool inverse = false) {\n\t\tsize_type\
    \ n = 0;\n\t\twhile((1 << n) < a.size()) n++;\n\t\tsize_type N = 1 << n;\n\t\t\
    a.resize(N);\n\n\t\tsize_type mask = N - 1;\n\t\tpolynomial<Complex> tmp(N);\n\
    \t\tfor(int i = N >> 1; i >= 1; i >>= 1) {\n\t\t\tReal theta = 2 * PI * i * (inverse\
    \ ? -1 : 1) / N;\n\t\t\tComplex zeta(std::cos(theta), std::sin(theta));\n\t\t\t\
    Complex powZeta(1);\n\n\t\t\tfor(int j = 0; j < N; j += i) {\n\t\t\t\tfor(int\
    \ k = 0; k < i; k++) {\n\t\t\t\t\ttmp[j + k] = a[((j << 1) & mask) | k] + powZeta\
    \ * a[(((j << 1) | i) & mask) | k];\n\t\t\t\t}\n\t\t\t\tpowZeta *= zeta;\n\t\t\
    \t}\n\t\t\ta.swap(tmp);\n\t\t}\n\n\t\tif(n & 1) {\n\t\t\tstd::swap(a, tmp);\n\t\
    \t\tfor(int i = 0; i < N; i++) a[i] = tmp[i];\n\t\t}\n\t\tif(inverse) for(int\
    \ i = 0; i < N; i++) a[i] /= N;\n\t}\n\tfast_fourier_transform convolution(const\
    \ fast_fourier_transform& ar, const fast_fourier_transform& br) {\n\t\tsize_type\
    \ size = ar.degree() + br.degree() + 1;\n\t\tpolynomial<Complex> a(size);\n\t\t\
    for(int i = 0; i < ar.size(); i++) a[i].real(ar[i]);\n\t\tfor(int i = 0; i < br.size();\
    \ i++) a[i].imag(br[i]);\n\t\ttransform(a, false);\n\t\t\n\t\tint N = a.size();\n\
    \t\tpolynomial<Complex> c(N);\n\t\tfor(int i = 0; i < N; i++) {\n\t\t\tint j =\
    \ (i == 0 ? 0 : N - i);\n\t\t\tc[i] = (a[i] + conj(a[j])) * (a[i] - conj(a[j]))\
    \ * Complex(0, -.25);\n\t\t}\n\t\ttransform(c, true);\n\n\t\tfast_fourier_transform\
    \ ret(size);\n\t\tfor(int i = 0; i < size; i++) ret[i] = round(c[i].real());\n\
    \t\treturn ret;\n\t\t\n\t}\npublic:\n\tfast_fourier_transform(const polynomial<T>&\
    \ p): polynomial<T>(p) {}\n\n\tfast_fourier_transform operator*(const_reference\
    \ r) const { return fast_fourier_transform(*this) *= r; }\n\tfast_fourier_transform&\
    \ operator*=(const_reference r) {\n\t\tfor(int i = 0; i < this->size(); i++) (*this)[i]\
    \ = (*this)[i] * r;\n\t\treturn *this;\n\t}\n\tfast_fourier_transform operator*(const\
    \ fast_fourier_transform& r) const { return fast_fourier_transform(*this) *= r;\
    \ }\n\tfast_fourier_transform& operator*=(const fast_fourier_transform& r) {\n\
    \t\treturn (*this) = convolution((*this), r);\n\t}\n};\n\n// @docs docs/fast_fourier_transform.md\n\
    \n\n"
  code: "#ifndef INCLUDED_FAST_FOURIER_TRANSFORM_HPP\n#define INCLUDED_FAST_FOURIER_TRANSFORM_HPP\n\
    \n#include \"../math/polynomial.hpp\"\n#include <complex>\n\ntemplate<class T,\
    \ class Real = double, class Complex = std::complex<Real>>\nclass fast_fourier_transform:\
    \ public polynomial<T> {\npublic:\n\tusing polynomial<T>::polynomial;\n\tusing\
    \ value_type = typename polynomial<T>::value_type;\n\tusing reference = typename\
    \ polynomial<T>::reference;\n\tusing const_reference = typename polynomial<T>::const_reference;\n\
    \tusing size_type = typename polynomial<T>::size_type;\n\nprivate:\n\t// constexpr\
    \ Real PI = std::numbers::pi_v<Real>;\n\tstatic constexpr Real PI = std::acos(Real(-1));;\n\
    \t\n\tvoid transform(polynomial<Complex>& a, bool inverse = false) {\n\t\tsize_type\
    \ n = 0;\n\t\twhile((1 << n) < a.size()) n++;\n\t\tsize_type N = 1 << n;\n\t\t\
    a.resize(N);\n\n\t\tsize_type mask = N - 1;\n\t\tpolynomial<Complex> tmp(N);\n\
    \t\tfor(int i = N >> 1; i >= 1; i >>= 1) {\n\t\t\tReal theta = 2 * PI * i * (inverse\
    \ ? -1 : 1) / N;\n\t\t\tComplex zeta(std::cos(theta), std::sin(theta));\n\t\t\t\
    Complex powZeta(1);\n\n\t\t\tfor(int j = 0; j < N; j += i) {\n\t\t\t\tfor(int\
    \ k = 0; k < i; k++) {\n\t\t\t\t\ttmp[j + k] = a[((j << 1) & mask) | k] + powZeta\
    \ * a[(((j << 1) | i) & mask) | k];\n\t\t\t\t}\n\t\t\t\tpowZeta *= zeta;\n\t\t\
    \t}\n\t\t\ta.swap(tmp);\n\t\t}\n\n\t\tif(n & 1) {\n\t\t\tstd::swap(a, tmp);\n\t\
    \t\tfor(int i = 0; i < N; i++) a[i] = tmp[i];\n\t\t}\n\t\tif(inverse) for(int\
    \ i = 0; i < N; i++) a[i] /= N;\n\t}\n\tfast_fourier_transform convolution(const\
    \ fast_fourier_transform& ar, const fast_fourier_transform& br) {\n\t\tsize_type\
    \ size = ar.degree() + br.degree() + 1;\n\t\tpolynomial<Complex> a(size);\n\t\t\
    for(int i = 0; i < ar.size(); i++) a[i].real(ar[i]);\n\t\tfor(int i = 0; i < br.size();\
    \ i++) a[i].imag(br[i]);\n\t\ttransform(a, false);\n\t\t\n\t\tint N = a.size();\n\
    \t\tpolynomial<Complex> c(N);\n\t\tfor(int i = 0; i < N; i++) {\n\t\t\tint j =\
    \ (i == 0 ? 0 : N - i);\n\t\t\tc[i] = (a[i] + conj(a[j])) * (a[i] - conj(a[j]))\
    \ * Complex(0, -.25);\n\t\t}\n\t\ttransform(c, true);\n\n\t\tfast_fourier_transform\
    \ ret(size);\n\t\tfor(int i = 0; i < size; i++) ret[i] = round(c[i].real());\n\
    \t\treturn ret;\n\t\t\n\t}\npublic:\n\tfast_fourier_transform(const polynomial<T>&\
    \ p): polynomial<T>(p) {}\n\n\tfast_fourier_transform operator*(const_reference\
    \ r) const { return fast_fourier_transform(*this) *= r; }\n\tfast_fourier_transform&\
    \ operator*=(const_reference r) {\n\t\tfor(int i = 0; i < this->size(); i++) (*this)[i]\
    \ = (*this)[i] * r;\n\t\treturn *this;\n\t}\n\tfast_fourier_transform operator*(const\
    \ fast_fourier_transform& r) const { return fast_fourier_transform(*this) *= r;\
    \ }\n\tfast_fourier_transform& operator*=(const fast_fourier_transform& r) {\n\
    \t\treturn (*this) = convolution((*this), r);\n\t}\n};\n\n// @docs docs/fast_fourier_transform.md\n\
    \n#endif\n"
  dependsOn:
  - math/polynomial.hpp
  isVerificationFile: false
  path: math/fast_fourier_transform.hpp
  requiredBy: []
  timestamp: '2020-03-20 12:55:43+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/fast_fourier_transform.hpp
layout: document
redirect_from:
- /library/math/fast_fourier_transform.hpp
- /library/math/fast_fourier_transform.hpp.html
title: math/fast_fourier_transform.hpp
---
## 計算量
- 時間 $\Theta(N\log N)$

## reference
- https://lumakernel.github.io/ecasdqina/math/FFT/standard