---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/number_theoritic_transform.hpp
    title: math/number_theoritic_transform.hpp
  - icon: ':heavy_check_mark:'
    path: math/arbitary_mod_number_theoritic_transform.hpp
    title: math/arbitary_mod_number_theoritic_transform.hpp
  - icon: ':heavy_check_mark:'
    path: math/arbitary_mod_number_theoritic_transform.hpp
    title: math/arbitary_mod_number_theoritic_transform.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp
    title: test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp
    title: test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/point_set_range_composite.segment_tree.test.cpp
    title: test/yosupo/point_set_range_composite.segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution_mod.test.cpp
    title: test/yosupo/convolution_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/inv_of_formal_power_series.ntt.test.cpp
    title: test/yosupo/inv_of_formal_power_series.ntt.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/log_of_formal_power_series.ntt.test.cpp
    title: test/yosupo/log_of_formal_power_series.ntt.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/exp_of_formal_power_series.ntt.test.cpp
    title: test/yosupo/exp_of_formal_power_series.ntt.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"math/modint.hpp\"\n\n\n\n#include <iostream>\n\ntemplate\
    \ <std::uint_fast64_t Modulus>\nclass modint {\n\tusing u32 = std::uint_fast32_t;\n\
    \tusing u64 = std::uint_fast64_t;\n\tusing i64 = std::int_fast64_t;\n\n\tinline\
    \ u64 apply(i64 x) { return (x < 0 ? x + Modulus : x); };\n\npublic:\n\tu64 a;\n\
    \tstatic constexpr u64 mod = Modulus;\n\n\tconstexpr modint(const i64& x = 0)\
    \ noexcept: a(apply(x % (i64)Modulus)) {}\n\n\tconstexpr modint operator+(const\
    \ modint& rhs) const noexcept { return modint(*this) += rhs; }\n\tconstexpr modint\
    \ operator-(const modint& rhs) const noexcept { return modint(*this) -= rhs; }\t\
    \n\tconstexpr modint operator*(const modint& rhs) const noexcept { return modint(*this)\
    \ *= rhs; }\n\tconstexpr modint operator/(const modint& rhs) const noexcept {\
    \ return modint(*this) /= rhs; }\n\tconstexpr modint operator^(const u64& k) const\
    \ noexcept { return modint(*this) ^= k; }\n\tconstexpr modint operator^(const\
    \ modint& k) const noexcept { return modint(*this) ^= k.value(); }\n\tconstexpr\
    \ modint operator-() const noexcept { return modint(Modulus - a); }\n\tconstexpr\
    \ modint operator++() noexcept { return (*this) = modint(*this) + 1; }\n\tconstexpr\
    \ modint operator--() noexcept { return (*this) = modint(*this) - 1; }\n\tconst\
    \ bool operator==(const modint& rhs) const noexcept { return a == rhs.a; };\n\t\
    const bool operator!=(const modint& rhs) const noexcept { return a != rhs.a; };\n\
    \tconst bool operator<=(const modint& rhs) const noexcept { return a <= rhs.a;\
    \ };\n\tconst bool operator>=(const modint& rhs) const noexcept { return a >=\
    \ rhs.a; };\n\tconst bool operator<(const modint& rhs) const noexcept { return\
    \ a < rhs.a; };\n\tconst bool operator>(const modint& rhs) const noexcept { return\
    \ a > rhs.a; };\n\tconstexpr modint& operator+=(const modint& rhs) noexcept {\n\
    \t\ta += rhs.a;\n\t\tif (a >= Modulus) a -= Modulus;\n\t\treturn *this;\n\t}\n\
    \tconstexpr modint& operator-=(const modint& rhs) noexcept {\n\t\tif (a < rhs.a)\
    \ a += Modulus;\n\t\ta -= rhs.a;\n\t\treturn *this;\n\t}\n\tconstexpr modint&\
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
    \t}\n};\n\n\n"
  code: "#ifndef INCLUDED_MODINT_HPP\n#define INCLUDED_MODINT_HPP\n\n#include <iostream>\n\
    \ntemplate <std::uint_fast64_t Modulus>\nclass modint {\n\tusing u32 = std::uint_fast32_t;\n\
    \tusing u64 = std::uint_fast64_t;\n\tusing i64 = std::int_fast64_t;\n\n\tinline\
    \ u64 apply(i64 x) { return (x < 0 ? x + Modulus : x); };\n\npublic:\n\tu64 a;\n\
    \tstatic constexpr u64 mod = Modulus;\n\n\tconstexpr modint(const i64& x = 0)\
    \ noexcept: a(apply(x % (i64)Modulus)) {}\n\n\tconstexpr modint operator+(const\
    \ modint& rhs) const noexcept { return modint(*this) += rhs; }\n\tconstexpr modint\
    \ operator-(const modint& rhs) const noexcept { return modint(*this) -= rhs; }\t\
    \n\tconstexpr modint operator*(const modint& rhs) const noexcept { return modint(*this)\
    \ *= rhs; }\n\tconstexpr modint operator/(const modint& rhs) const noexcept {\
    \ return modint(*this) /= rhs; }\n\tconstexpr modint operator^(const u64& k) const\
    \ noexcept { return modint(*this) ^= k; }\n\tconstexpr modint operator^(const\
    \ modint& k) const noexcept { return modint(*this) ^= k.value(); }\n\tconstexpr\
    \ modint operator-() const noexcept { return modint(Modulus - a); }\n\tconstexpr\
    \ modint operator++() noexcept { return (*this) = modint(*this) + 1; }\n\tconstexpr\
    \ modint operator--() noexcept { return (*this) = modint(*this) - 1; }\n\tconst\
    \ bool operator==(const modint& rhs) const noexcept { return a == rhs.a; };\n\t\
    const bool operator!=(const modint& rhs) const noexcept { return a != rhs.a; };\n\
    \tconst bool operator<=(const modint& rhs) const noexcept { return a <= rhs.a;\
    \ };\n\tconst bool operator>=(const modint& rhs) const noexcept { return a >=\
    \ rhs.a; };\n\tconst bool operator<(const modint& rhs) const noexcept { return\
    \ a < rhs.a; };\n\tconst bool operator>(const modint& rhs) const noexcept { return\
    \ a > rhs.a; };\n\tconstexpr modint& operator+=(const modint& rhs) noexcept {\n\
    \t\ta += rhs.a;\n\t\tif (a >= Modulus) a -= Modulus;\n\t\treturn *this;\n\t}\n\
    \tconstexpr modint& operator-=(const modint& rhs) noexcept {\n\t\tif (a < rhs.a)\
    \ a += Modulus;\n\t\ta -= rhs.a;\n\t\treturn *this;\n\t}\n\tconstexpr modint&\
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
    \t}\n};\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: math/modint.hpp
  requiredBy:
  - math/number_theoritic_transform.hpp
  - math/arbitary_mod_number_theoritic_transform.hpp
  - math/arbitary_mod_number_theoritic_transform.hpp
  timestamp: '2020-03-19 17:03:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp
  - test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp
  - test/yosupo/point_set_range_composite.segment_tree.test.cpp
  - test/yosupo/convolution_mod.test.cpp
  - test/yosupo/inv_of_formal_power_series.ntt.test.cpp
  - test/yosupo/log_of_formal_power_series.ntt.test.cpp
  - test/yosupo/exp_of_formal_power_series.ntt.test.cpp
documentation_of: math/modint.hpp
layout: document
redirect_from:
- /library/math/modint.hpp
- /library/math/modint.hpp.html
title: math/modint.hpp
---
