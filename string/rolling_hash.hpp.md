---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/2763.test.cpp
    title: test/aoj/2763.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"string/rolling_hash.hpp\"\n\n\n\n#include <vector>\n#include\
    \ <string>\n\nclass rolling_hash {\npublic:\n\tusing u64 = std::uint_fast64_t;\n\
    \tusing size_type = std::uint_fast32_t;\n\n\tstatic constexpr u64 MOD = (1uL <<\
    \ 61) - 1;\n\tstatic constexpr u64 base = 20200213;\n\n\tstd::string str;\n\t\
    std::vector<u64> hash_, pow;\n\nprivate:\n\tstatic constexpr u64 mask30 = (1ul\
    \ << 30) - 1;\n\tstatic constexpr u64 mask31 = (1ul << 31) - 1;\n\n\tu64 mul(u64\
    \ a, u64 b) const {\n\t\tu64 au = a >> 31;\n\t\tu64 ad = a & mask31;\n\t\tu64\
    \ bu = b >> 31;\n\t\tu64 bd = b & mask31;\n\t\tu64 mid = ad * bu + au * bd;\n\t\
    \tu64 midu = mid >> 30;\n\t\tu64 midd = mid & mask30;\n\t\treturn apply(au * bu\
    \ * 2 + midu + (midd << 31) + ad * bd);\n\t}\n\tu64 apply(u64 val) const {\n\t\
    \tval = (val & MOD) + (val >> 61);\n\t\tif(val >= MOD) val -= MOD;\n\t\treturn\
    \ val;\n\t}\n\tsize_type xorshift(size_type x) const {\n\t\tx ^= x << 13;\n\t\t\
    x ^= x >> 17;\n\t\tx ^= x << 5;\n\t\treturn x;\n\t}\n\npublic:\n\trolling_hash(const\
    \ rolling_hash &) = default;\n\trolling_hash(rolling_hash&&) = default;\n\n\t\
    rolling_hash() : str() {};\n\trolling_hash(const std::string & str) : str(str)\
    \ {\n\t\thash_.resize(str.size() + 1, 0);\n\t\tpow.resize(str.size() + 1, 1);\n\
    \t\tfor(size_type i = 0; i < str.size(); i++) {\n\t\t\thash_[i + 1] = mul(hash_[i],\
    \ base) + xorshift(str[i] + 1);\n\t\t\tpow[i + 1] = mul(pow[i], base);\n\t\t\t\
    if(hash_[i + 1] >= MOD) hash_[i + 1] -= MOD;\n\t\t}\n\t}\n\n\tu64 hash() const\
    \ { return hash_.back(); }\n\tu64 hash(size_type l, size_type r) const {\n\t\t\
    u64 ret = MOD + hash_[r] - mul(hash_[l], pow[r - l]);\n\t\treturn ret < MOD ?\
    \ ret : ret - MOD;\n\t}\n\t\n\tsize_type size() const { return str.size(); }\n\
    };\n\n\n"
  code: "#ifndef INCLUDED_ROLLING_HASH_HPP\n#define INCLUDED_ROLLING_HASH_HPP\n\n\
    #include <vector>\n#include <string>\n\nclass rolling_hash {\npublic:\n\tusing\
    \ u64 = std::uint_fast64_t;\n\tusing size_type = std::uint_fast32_t;\n\n\tstatic\
    \ constexpr u64 MOD = (1uL << 61) - 1;\n\tstatic constexpr u64 base = 20200213;\n\
    \n\tstd::string str;\n\tstd::vector<u64> hash_, pow;\n\nprivate:\n\tstatic constexpr\
    \ u64 mask30 = (1ul << 30) - 1;\n\tstatic constexpr u64 mask31 = (1ul << 31) -\
    \ 1;\n\n\tu64 mul(u64 a, u64 b) const {\n\t\tu64 au = a >> 31;\n\t\tu64 ad = a\
    \ & mask31;\n\t\tu64 bu = b >> 31;\n\t\tu64 bd = b & mask31;\n\t\tu64 mid = ad\
    \ * bu + au * bd;\n\t\tu64 midu = mid >> 30;\n\t\tu64 midd = mid & mask30;\n\t\
    \treturn apply(au * bu * 2 + midu + (midd << 31) + ad * bd);\n\t}\n\tu64 apply(u64\
    \ val) const {\n\t\tval = (val & MOD) + (val >> 61);\n\t\tif(val >= MOD) val -=\
    \ MOD;\n\t\treturn val;\n\t}\n\tsize_type xorshift(size_type x) const {\n\t\t\
    x ^= x << 13;\n\t\tx ^= x >> 17;\n\t\tx ^= x << 5;\n\t\treturn x;\n\t}\n\npublic:\n\
    \trolling_hash(const rolling_hash &) = default;\n\trolling_hash(rolling_hash&&)\
    \ = default;\n\n\trolling_hash() : str() {};\n\trolling_hash(const std::string\
    \ & str) : str(str) {\n\t\thash_.resize(str.size() + 1, 0);\n\t\tpow.resize(str.size()\
    \ + 1, 1);\n\t\tfor(size_type i = 0; i < str.size(); i++) {\n\t\t\thash_[i + 1]\
    \ = mul(hash_[i], base) + xorshift(str[i] + 1);\n\t\t\tpow[i + 1] = mul(pow[i],\
    \ base);\n\t\t\tif(hash_[i + 1] >= MOD) hash_[i + 1] -= MOD;\n\t\t}\n\t}\n\n\t\
    u64 hash() const { return hash_.back(); }\n\tu64 hash(size_type l, size_type r)\
    \ const {\n\t\tu64 ret = MOD + hash_[r] - mul(hash_[l], pow[r - l]);\n\t\treturn\
    \ ret < MOD ? ret : ret - MOD;\n\t}\n\t\n\tsize_type size() const { return str.size();\
    \ }\n};\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: string/rolling_hash.hpp
  requiredBy: []
  timestamp: '2020-03-19 17:03:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/2763.test.cpp
documentation_of: string/rolling_hash.hpp
layout: document
redirect_from:
- /library/string/rolling_hash.hpp
- /library/string/rolling_hash.hpp.html
title: string/rolling_hash.hpp
---
