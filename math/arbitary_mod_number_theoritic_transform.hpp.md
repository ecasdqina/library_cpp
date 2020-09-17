---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: math/modint.hpp
  - icon: ':heavy_check_mark:'
    path: math/polynomial.hpp
    title: math/polynomial.hpp
  - icon: ':heavy_check_mark:'
    path: math/number_theoritic_transform.hpp
    title: math/number_theoritic_transform.hpp
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: math/modint.hpp
  - icon: ':heavy_check_mark:'
    path: math/polynomial.hpp
    title: math/polynomial.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp
    title: test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    _deprecated_at_docs: docs/arbitary_mod_number_theoritic_transform.md
    links:
    - https://lumakernel.github.io/ecasdqina/math/FFT/NTT
  bundledCode: "#line 1 \"math/arbitary_mod_number_theoritic_transform.hpp\"\n\n\n\
    \n#line 1 \"math/modint.hpp\"\n\n\n\n#include <iostream>\n\ntemplate <std::uint_fast64_t\
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
    \ T{}); }\n};\n\n\n#line 1 \"math/number_theoritic_transform.hpp\"\n\n\n\n#line\
    \ 6 \"math/number_theoritic_transform.hpp\"\n\ntemplate<class T, int primitive_root\
    \ = 3>\nclass number_theoritic_transform: public polynomial<T> {\npublic:\n\t\
    using polynomial<T>::polynomial;\n\tusing value_type = typename polynomial<T>::value_type;\n\
    \tusing reference = typename polynomial<T>::reference;\n\tusing const_reference\
    \ = typename polynomial<T>::const_reference;\n\tusing size_type = typename polynomial<T>::size_type;\n\
    \nprivate:\n\tvoid ntt(number_theoritic_transform& a) const {\n\t\tint N = a.size();\n\
    \t\tstatic std::vector<T> dw;\n\t\tif(dw.size() < N) {\n\t\t\tint n = dw.size();\n\
    \t\t\tdw.resize(N);\n\t\t\tfor(int i = n; i < N; i++) dw[i] = -(T(primitive_root)\
    \ ^ ((T::mod - 1) >> i + 2));\n\t\t}\n\n\t\tfor(int m = N; m >>= 1;) {\n\t\t\t\
    T w = 1;\n\t\t\tfor(int s = 0, k = 0; s < N; s += 2 * m) {\n\t\t\t\tfor(int i\
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
    \ r);\n\t}\n};\n\n// @docs docs/number_theoritic_transform.md\n\n\n#line 7 \"\
    math/arbitary_mod_number_theoritic_transform.hpp\"\n\nnamespace amnttlib {\n\t\
    using u64 = std::uint_fast64_t;\n\n\t// https://lumakernel.github.io/ecasdqina/math/FFT/NTT\n\
    \tconstexpr u64 ntt_primes[][2] = {\n\t\t{1224736769, 3}, // 2^24 * 73 + 1,\n\t\
    \t{1053818881, 7}, // 2^20 * 3 * 5 * 67 + 1\n\t\t{1051721729, 6}, // 2^20 * 17\
    \ * 59 + 1\n\t\t{1045430273, 3}, // 2^20 * 997 + 1\n\t\t{1012924417, 5}, // 2^21\
    \ * 3 * 7 * 23 + 1\n\t\t{1007681537, 3}, // 2^20 * 31^2 + 1\n\t\t{1004535809,\
    \ 3}, // 2^21 * 479 + 1\n\t\t{998244353, 3},  // 2^23 * 7 * 17 + 1\n\t\t{985661441,\
    \ 3},  // 2^22 * 5 * 47 + 1\n\t\t{976224257, 3},  // 2^20 * 7^2 * 19 + 1\n\t\t\
    {975175681, 17}, // 2^21 * 3 * 5 * 31 + 1\n\t\t{962592769, 7},  // 2^21 * 3^3\
    \ * 17 + 1\n\t\t{950009857, 7},  // 2^21 * 4 * 151 + 1\n\t\t{943718401, 7},  //\
    \ 2^22 * 3^2 * 5^2 + 1\n\t\t{935329793, 3},  // 2^22 * 223 + 1\n\t\t{924844033,\
    \ 5},  // 2^21 * 3^2 * 7^2 + 1\n\t\t{469762049, 3},  // 2^26 * 7 + 1\n\t\t{167772161,\
    \ 3},  // 2^25 * 5 + 1\n\t};\n};\n\ntemplate<class T,\n\tamnttlib::u64 MOD_1 =\
    \ amnttlib::ntt_primes[0][0],\n\tamnttlib::u64 PRR_1 = amnttlib::ntt_primes[0][1],\n\
    \tamnttlib::u64 MOD_2 = amnttlib::ntt_primes[2][0],\n\tamnttlib::u64 PRR_2 = amnttlib::ntt_primes[2][1],\n\
    \tamnttlib::u64 MOD_3 = amnttlib::ntt_primes[3][0],\n\tamnttlib::u64 PRR_3 = amnttlib::ntt_primes[3][1]\n\
    > class arbitary_mod_number_theoritic_transform: public polynomial<T> {\npublic:\n\
    \tusing polynomial<T>::polynomial;\n\tusing value_type = typename polynomial<T>::value_type;\n\
    \tusing reference = typename polynomial<T>::reference;\n\tusing const_reference\
    \ = typename polynomial<T>::const_reference;\n\tusing size_type = typename polynomial<T>::size_type;\n\
    \n\tusing amntt = arbitary_mod_number_theoritic_transform;\n\tusing m1 = modint<MOD_1>;\n\
    \tusing m2 = modint<MOD_2>;\n\tusing m3 = modint<MOD_3>;\n\nprivate:\n\tamntt\
    \ convolution(const amntt& ar, const amntt& br) {\n\t\tnumber_theoritic_transform<m1,\
    \ PRR_1> ntt1_a(ar.size()), ntt1_b(br.size());\n\t\tnumber_theoritic_transform<m2,\
    \ PRR_2> ntt2_a(ar.size()), ntt2_b(br.size());\n\t\tnumber_theoritic_transform<m3,\
    \ PRR_3> ntt3_a(ar.size()), ntt3_b(br.size());\n\t\tfor(int i = 0; i < ar.size();\
    \ i++) {\n\t\t\tntt1_a[i] = m1(ar[i].value());\n\t\t\tntt2_a[i] = m2(ar[i].value());\n\
    \t\t\tntt3_a[i] = m3(ar[i].value());\n\t\t}\n\t\tfor(int i = 0; i < br.size();\
    \ i++) {\n\t\t\tntt1_b[i] = m1(br[i].value());\n\t\t\tntt2_b[i] = m2(br[i].value());\n\
    \t\t\tntt3_b[i] = m3(br[i].value());\n\t\t}\n\t\tauto x = ntt1_a * ntt1_b;\n\t\
    \tauto y = ntt2_a * ntt2_b;\n\t\tauto z = ntt3_a * ntt3_b;\n\n\t\tamntt ret(x.size());\n\
    \t\tconst m2 m1_inv_m2 = m2(MOD_1).inverse();\n\t\tconst m3 m12_inv_m3 = (m3(MOD_1)\
    \ * m3(MOD_2)).inverse();\n\t\tconst T m12 = T(MOD_1) * T(MOD_2);\n\t\tfor(int\
    \ i = 0; i < ret.size(); i++) {\n\t\t\tm2 v1 = (m2(y[i].value()) - m2(x[i].value()))\
    \ * m1_inv_m2;\n\t\t\tm3 v2 = (m3(z[i].value()) - (m3(x[i].value()) + m3(MOD_1)\
    \ * m3(v1.value()))) * m12_inv_m3;\n\t\t\tret[i] = (T(x[i].value()) + T(MOD_1)\
    \ * T(v1.value()) + m12 * T(v2.value()));\n\t\t}\n\t\tret.resize(ar.degree() +\
    \ br.degree() + 1);\n\t\treturn ret;\n\t}\n\t\npublic:\n\tarbitary_mod_number_theoritic_transform(const\
    \ polynomial<T>& p): polynomial<T>(p) {}\n\n\n\tamntt operator*(const_reference\
    \ r) const { return amntt(*this) *= r; }\n\tamntt& operator*=(const_reference\
    \ r) {\n\t\tfor(int i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] * r;\n\
    \t\treturn *this;\n\t}\n\tamntt operator*(const amntt& r) const { return amntt(*this)\
    \ *= r; }\n\tamntt& operator*=(const amntt& r) {\n\t\treturn (*this) = convolution((*this),\
    \ r);\n\t}\n};\n\n// @docs docs/arbitary_mod_number_theoritic_transform.md\n\n\
    \n"
  code: "#ifndef INCLUDED_ARBITARY_MOD_NUMBER_THEORITIC_TRANSFORM_HPP\n#define INCLUDED_ARBITARY_MOD_NUMBER_THEORITIC_TRANSFORM_HPP\n\
    \n#include \"../math/modint.hpp\"\n#include \"../math/polynomial.hpp\"\n#include\
    \ \"../math/number_theoritic_transform.hpp\"\n\nnamespace amnttlib {\n\tusing\
    \ u64 = std::uint_fast64_t;\n\n\t// https://lumakernel.github.io/ecasdqina/math/FFT/NTT\n\
    \tconstexpr u64 ntt_primes[][2] = {\n\t\t{1224736769, 3}, // 2^24 * 73 + 1,\n\t\
    \t{1053818881, 7}, // 2^20 * 3 * 5 * 67 + 1\n\t\t{1051721729, 6}, // 2^20 * 17\
    \ * 59 + 1\n\t\t{1045430273, 3}, // 2^20 * 997 + 1\n\t\t{1012924417, 5}, // 2^21\
    \ * 3 * 7 * 23 + 1\n\t\t{1007681537, 3}, // 2^20 * 31^2 + 1\n\t\t{1004535809,\
    \ 3}, // 2^21 * 479 + 1\n\t\t{998244353, 3},  // 2^23 * 7 * 17 + 1\n\t\t{985661441,\
    \ 3},  // 2^22 * 5 * 47 + 1\n\t\t{976224257, 3},  // 2^20 * 7^2 * 19 + 1\n\t\t\
    {975175681, 17}, // 2^21 * 3 * 5 * 31 + 1\n\t\t{962592769, 7},  // 2^21 * 3^3\
    \ * 17 + 1\n\t\t{950009857, 7},  // 2^21 * 4 * 151 + 1\n\t\t{943718401, 7},  //\
    \ 2^22 * 3^2 * 5^2 + 1\n\t\t{935329793, 3},  // 2^22 * 223 + 1\n\t\t{924844033,\
    \ 5},  // 2^21 * 3^2 * 7^2 + 1\n\t\t{469762049, 3},  // 2^26 * 7 + 1\n\t\t{167772161,\
    \ 3},  // 2^25 * 5 + 1\n\t};\n};\n\ntemplate<class T,\n\tamnttlib::u64 MOD_1 =\
    \ amnttlib::ntt_primes[0][0],\n\tamnttlib::u64 PRR_1 = amnttlib::ntt_primes[0][1],\n\
    \tamnttlib::u64 MOD_2 = amnttlib::ntt_primes[2][0],\n\tamnttlib::u64 PRR_2 = amnttlib::ntt_primes[2][1],\n\
    \tamnttlib::u64 MOD_3 = amnttlib::ntt_primes[3][0],\n\tamnttlib::u64 PRR_3 = amnttlib::ntt_primes[3][1]\n\
    > class arbitary_mod_number_theoritic_transform: public polynomial<T> {\npublic:\n\
    \tusing polynomial<T>::polynomial;\n\tusing value_type = typename polynomial<T>::value_type;\n\
    \tusing reference = typename polynomial<T>::reference;\n\tusing const_reference\
    \ = typename polynomial<T>::const_reference;\n\tusing size_type = typename polynomial<T>::size_type;\n\
    \n\tusing amntt = arbitary_mod_number_theoritic_transform;\n\tusing m1 = modint<MOD_1>;\n\
    \tusing m2 = modint<MOD_2>;\n\tusing m3 = modint<MOD_3>;\n\nprivate:\n\tamntt\
    \ convolution(const amntt& ar, const amntt& br) {\n\t\tnumber_theoritic_transform<m1,\
    \ PRR_1> ntt1_a(ar.size()), ntt1_b(br.size());\n\t\tnumber_theoritic_transform<m2,\
    \ PRR_2> ntt2_a(ar.size()), ntt2_b(br.size());\n\t\tnumber_theoritic_transform<m3,\
    \ PRR_3> ntt3_a(ar.size()), ntt3_b(br.size());\n\t\tfor(int i = 0; i < ar.size();\
    \ i++) {\n\t\t\tntt1_a[i] = m1(ar[i].value());\n\t\t\tntt2_a[i] = m2(ar[i].value());\n\
    \t\t\tntt3_a[i] = m3(ar[i].value());\n\t\t}\n\t\tfor(int i = 0; i < br.size();\
    \ i++) {\n\t\t\tntt1_b[i] = m1(br[i].value());\n\t\t\tntt2_b[i] = m2(br[i].value());\n\
    \t\t\tntt3_b[i] = m3(br[i].value());\n\t\t}\n\t\tauto x = ntt1_a * ntt1_b;\n\t\
    \tauto y = ntt2_a * ntt2_b;\n\t\tauto z = ntt3_a * ntt3_b;\n\n\t\tamntt ret(x.size());\n\
    \t\tconst m2 m1_inv_m2 = m2(MOD_1).inverse();\n\t\tconst m3 m12_inv_m3 = (m3(MOD_1)\
    \ * m3(MOD_2)).inverse();\n\t\tconst T m12 = T(MOD_1) * T(MOD_2);\n\t\tfor(int\
    \ i = 0; i < ret.size(); i++) {\n\t\t\tm2 v1 = (m2(y[i].value()) - m2(x[i].value()))\
    \ * m1_inv_m2;\n\t\t\tm3 v2 = (m3(z[i].value()) - (m3(x[i].value()) + m3(MOD_1)\
    \ * m3(v1.value()))) * m12_inv_m3;\n\t\t\tret[i] = (T(x[i].value()) + T(MOD_1)\
    \ * T(v1.value()) + m12 * T(v2.value()));\n\t\t}\n\t\tret.resize(ar.degree() +\
    \ br.degree() + 1);\n\t\treturn ret;\n\t}\n\t\npublic:\n\tarbitary_mod_number_theoritic_transform(const\
    \ polynomial<T>& p): polynomial<T>(p) {}\n\n\n\tamntt operator*(const_reference\
    \ r) const { return amntt(*this) *= r; }\n\tamntt& operator*=(const_reference\
    \ r) {\n\t\tfor(int i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] * r;\n\
    \t\treturn *this;\n\t}\n\tamntt operator*(const amntt& r) const { return amntt(*this)\
    \ *= r; }\n\tamntt& operator*=(const amntt& r) {\n\t\treturn (*this) = convolution((*this),\
    \ r);\n\t}\n};\n\n// @docs docs/arbitary_mod_number_theoritic_transform.md\n\n\
    #endif\n"
  dependsOn:
  - math/modint.hpp
  - math/polynomial.hpp
  - math/number_theoritic_transform.hpp
  - math/modint.hpp
  - math/polynomial.hpp
  isVerificationFile: false
  path: math/arbitary_mod_number_theoritic_transform.hpp
  requiredBy: []
  timestamp: '2020-03-20 12:55:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp
documentation_of: math/arbitary_mod_number_theoritic_transform.hpp
layout: document
redirect_from:
- /library/math/arbitary_mod_number_theoritic_transform.hpp
- /library/math/arbitary_mod_number_theoritic_transform.hpp.html
title: math/arbitary_mod_number_theoritic_transform.hpp
---
## 計算量
- 時間 $\Theta(N\log N)$

## note
- テンプレート引数として modint が渡されることを想定している．

## description
三素数による NTT を garner のアルゴリズムによって復元するため定数倍が重い．

## reference
- https://math314.hateblo.jp/entry/2015/05/07/014908

## example
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "../../math/arbitary_mod_number_theoritic_transform.hpp"
#include "../../other/fast_io.hpp"

using mint = modint<(int)(1e9 + 7)>;

int main() {
	int n, m; fin.scan(n, m);
	arbitary_mod_number_theoritic_transform<mint> a(n), b(m);
	for(int i = 0; i < n; i++) {
		int x; fin.scan(x);
		a[i] = x;
	}
	for(int i = 0; i < m; i++) {
		int x; fin.scan(x);
		b[i] = x;
	}

	for(auto v: a * b) fout.print(v.value(), ' ');
	fout.println();
	return 0;
}
```