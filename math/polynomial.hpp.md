---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/arbitary_mod_number_theoritic_transform.hpp
    title: math/arbitary_mod_number_theoritic_transform.hpp
  - icon: ':x:'
    path: math/arbitary_mod_number_theoritic_transform.hpp
    title: math/arbitary_mod_number_theoritic_transform.hpp
  - icon: ':warning:'
    path: math/fast_fourier_transform.hpp
    title: math/fast_fourier_transform.hpp
  - icon: ':x:'
    path: math/number_theoritic_transform.hpp
    title: math/number_theoritic_transform.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo/convolution_mod.test.cpp
    title: test/yosupo/convolution_mod.test.cpp
  - icon: ':x:'
    path: test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp
    title: test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp
  - icon: ':x:'
    path: test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp
    title: test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp
  - icon: ':x:'
    path: test/yosupo/exp_of_formal_power_series.ntt.test.cpp
    title: test/yosupo/exp_of_formal_power_series.ntt.test.cpp
  - icon: ':x:'
    path: test/yosupo/inv_of_formal_power_series.ntt.test.cpp
    title: test/yosupo/inv_of_formal_power_series.ntt.test.cpp
  - icon: ':x:'
    path: test/yosupo/log_of_formal_power_series.ntt.test.cpp
    title: test/yosupo/log_of_formal_power_series.ntt.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/polynomial.hpp\"\n\n\n\n#include <cstdint>\n#include\
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
    \ += r; }\n\tfriend polynomial operator+(const_reference l, polynomial r) { return\
    \ r += l; }\n\tpolynomial operator-(const polynomial& r) const { return polynomial(*this)\
    \ -= r; }\n\tpolynomial operator-(const_reference r) const { return polynomial(*this)\
    \ -= r; }\n\tfriend polynomial operator-(const_reference l, polynomial r) { return\
    \ r -= l; }\n\tpolynomial operator*(const_reference r) const { return polynomial(*this)\
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
    };\n}\n\n\n"
  code: "#ifndef INCLUDED_POLYNOMIAL_HPP\n#define INCLUDED_POLYNOMIAL_HPP\n\n#include\
    \ <cstdint>\n#include <vector>\n\nnamespace cplib {\ntemplate<class T>\nclass\
    \ polynomial: public std::vector<T> {\npublic:\n\tusing std::vector<T>::vector;\n\
    \tusing value_type = typename std::vector<T>::value_type;\n\tusing reference =\
    \ typename std::vector<T>::reference;\n\tusing const_reference = typename std::vector<T>::const_reference;\n\
    \tusing size_type = typename std::vector<T>::size_type;\n\nprivate:\n\tT eval(T\
    \ x) const {\n\t\tT ret = (*this)[0], tmp = x;\n\t\tfor(int i = 1; i < this->size();\
    \ i++) {\n\t\t\tret = ret + (*this)[i] * tmp;\n\t\t\ttmp = tmp * x;\n\t\t}\n\t\
    \treturn ret;\n\t}\n\npublic:\n\tpolynomial(const std::vector<T>& p): std::vector<T>(p)\
    \ {}\n\n\tsize_type nonzeros() const {\n\t\tsize_type ret = 0;\n\t\tfor(int i\
    \ = 0; i < this->size(); i++) {\n\t\t\tif((*this)[i] != T{}) ret++;\n\t\t}\n\t\
    \treturn ret;\n\t}\n\n\tstatic polynomial<T> one() { return term(0); }\n\tstatic\
    \ polynomial<T> zero() { return polynomial<T>({T{0}}); }\n\tstatic polynomial<T>\
    \ term(int k) { return polynomial<T>({T{1}}) << k; }\n\npublic:\n\tpolynomial\
    \ operator+(const polynomial& r) const { return polynomial(*this) += r; }\n\t\
    polynomial operator+(const_reference r) const { return polynomial(*this) += r;\
    \ }\n\tfriend polynomial operator+(const_reference l, polynomial r) { return r\
    \ += l; }\n\tpolynomial operator-(const polynomial& r) const { return polynomial(*this)\
    \ -= r; }\n\tpolynomial operator-(const_reference r) const { return polynomial(*this)\
    \ -= r; }\n\tfriend polynomial operator-(const_reference l, polynomial r) { return\
    \ r -= l; }\n\tpolynomial operator*(const_reference r) const { return polynomial(*this)\
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
    };\n}\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: math/polynomial.hpp
  requiredBy:
  - math/arbitary_mod_number_theoritic_transform.hpp
  - math/arbitary_mod_number_theoritic_transform.hpp
  - math/fast_fourier_transform.hpp
  - math/number_theoritic_transform.hpp
  timestamp: '2020-11-01 20:48:43+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo/exp_of_formal_power_series.ntt.test.cpp
  - test/yosupo/log_of_formal_power_series.ntt.test.cpp
  - test/yosupo/convolution_mod.test.cpp
  - test/yosupo/inv_of_formal_power_series.ntt.test.cpp
  - test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp
  - test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp
documentation_of: math/polynomial.hpp
layout: document
redirect_from:
- /library/math/polynomial.hpp
- /library/math/polynomial.hpp.html
title: math/polynomial.hpp
---
