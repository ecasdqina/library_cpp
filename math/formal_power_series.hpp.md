---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
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
    _deprecated_at_docs: docs/formal_power_series.md
    links: []
  bundledCode: "#line 1 \"math/formal_power_series.hpp\"\n\n\n\n#include <cassert>\n\
    #include <utility>\n\ntemplate<class T>\nclass formal_power_series: public T {\n\
    public:\n\tusing T::T;\n\tusing value_type = typename T::value_type;\n\tusing\
    \ reference = typename T::reference;\n\tusing const_reference = typename T::const_reference;\n\
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
    \n\n"
  code: "#ifndef INCLUDED_FORMAL_POWER_SERIES_HPP\n#define INCLUDED_FORMAL_POWER_SERIES_HPP\n\
    \n#include <cassert>\n#include <utility>\n\ntemplate<class T>\nclass formal_power_series:\
    \ public T {\npublic:\n\tusing T::T;\n\tusing value_type = typename T::value_type;\n\
    \tusing reference = typename T::reference;\n\tusing const_reference = typename\
    \ T::const_reference;\n\tusing size_type = typename T::size_type;\n\nprivate:\n\
    \tformal_power_series(): T(1) {}\n\tformal_power_series(const T& p): T(p) {}\n\
    \npublic:\n\tformal_power_series inverse() const {\n\t\tassert((*this)[0] != value_type{});\n\
    \n\t\tformal_power_series ret(1, (*this)[0].inverse());\n\t\tfor(int i = 1; i\
    \ < this->size(); i <<= 1) {\n\t\t\tauto tmp = ret * this->prefix(i << 1);\n\t\
    \t\tfor(int j = 0; j < i; j++) {\n\t\t\t\ttmp[j] = value_type{};\n\t\t\t\tif(j\
    \ + i < tmp.size()) tmp[j + i] *= value_type(-1);\n\t\t\t}\n\t\t\ttmp = tmp *\
    \ ret;\n\t\t\tfor(int j = 0; j < i; j++) tmp[j] = ret[j];\n\t\t\tret = std::move(tmp).prefix(i\
    \ << 1);\n\t\t}\n\t\treturn ret.prefix(this->size());\n\t}\n\tformal_power_series\
    \ log() const {\n\t\tassert((*this)[0] == value_type(1));\n\t\t\n\t\treturn (formal_power_series(this->differential())\
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
    \n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: math/formal_power_series.hpp
  requiredBy: []
  timestamp: '2020-03-20 12:55:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/exp_of_formal_power_series.ntt.test.cpp
  - test/yosupo/log_of_formal_power_series.ntt.test.cpp
  - test/yosupo/inv_of_formal_power_series.ntt.test.cpp
documentation_of: math/formal_power_series.hpp
layout: document
redirect_from:
- /library/math/formal_power_series.hpp
- /library/math/formal_power_series.hpp.html
title: math/formal_power_series.hpp
---
## 計算量
- inv, log, exp, pow $\Theta(N\log N)$

## reference
- https://ei1333.github.io/luzhiled/snippets/math/formal-power-series.html

## example
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include "../../math/number_theoritic_transform.hpp"
#include "../../math/formal_power_series.hpp"
#include "../../other/fast_io.hpp"

using fps = formal_power_series<number_theoritic_transform<modint<998244353>>>;

int main() {
	int n; fin.scan(n);
	fps a(n);
	for(int i = 0; i < n; i++) {
		int x; fin.scan(x);

		a[i] = x;
	}

	for(auto v: a.inverse()) fout.print(v.value(), ' ');
	fout.println();
	return 0;
}
```