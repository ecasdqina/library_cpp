---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: test/hackerrank/zundamochi.rolling_hash.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#766fdb3ef249a93055dc5b84cab8f79c">test/hackerrank</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/hackerrank/zundamochi.rolling_hash.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-18 17:46:43+09:00


* see: <a href="https://www.hackerrank.com/contests/kiritan-birthday-contest-2020/challenges/zundamochi">https://www.hackerrank.com/contests/kiritan-birthday-contest-2020/challenges/zundamochi</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/string/rolling_hash.hpp.html">string/rolling_hash.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://www.hackerrank.com/contests/kiritan-birthday-contest-2020/challenges/zundamochi"

#include <stdio.h>
#include <iostream>
#include <map>
#include "../../string/rolling_hash.hpp"

int main() {
    int n, k; scanf("%d%d", &n, &k);
    std::string s; std::cin >> s;

    rolling_hash hash(s);
    std::map<std::uint_fast64_t, std::vector<int>> mp;
    for(int i = 0; i < (int)s.size() - k + 1; i++) {
        mp[hash.hash(i, i + k)].push_back(i);
    }

    int ans = 0;
    for(auto vec: mp) {
        int tmp = -k, cnt = 0;
        for(auto v: vec.second) {
            if(tmp + k <= v) {
                tmp = v;
                cnt++;
            }
        }
        ans = std::max(ans, cnt);
    }

    printf("%d\n", ans);
    return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/hackerrank/zundamochi.rolling_hash.test.cpp"
#define PROBLEM "https://www.hackerrank.com/contests/kiritan-birthday-contest-2020/challenges/zundamochi"

#include <stdio.h>
#include <iostream>
#include <map>
#line 1 "test/hackerrank/../../string/rolling_hash.hpp"



#include <vector>
#include <string>

class rolling_hash {
public:
	using u64 = std::uint_fast64_t;
	using size_type = std::uint_fast32_t;

	static constexpr u64 MOD = (1uL << 61) - 1;
	static constexpr u64 base = 20200213;

	std::string str;
	std::vector<u64> hash_, pow;

private:
	static constexpr u64 mask30 = (1ul << 30) - 1;
	static constexpr u64 mask31 = (1ul << 31) - 1;

	u64 mul(u64 a, u64 b) const {
		u64 au = a >> 31;
		u64 ad = a & mask31;
		u64 bu = b >> 31;
		u64 bd = b & mask31;
		u64 mid = ad * bu + au * bd;
		u64 midu = mid >> 30;
		u64 midd = mid & mask30;
		return apply(au * bu * 2 + midu + (midd << 31) + ad * bd);
	}
	u64 apply(u64 val) const {
		val = (val & MOD) + (val >> 61);
		if(val >= MOD) val -= MOD;
		return val;
	}
	size_type xorshift(size_type x) const {
		x ^= x << 13;
		x ^= x >> 17;
		x ^= x << 5;
		return x;
	}

public:
	rolling_hash(const rolling_hash &) = default;
	rolling_hash(rolling_hash&&) = default;

	rolling_hash() : str() {};
	rolling_hash(const std::string & str) : str(str) {
		hash_.resize(str.size() + 1, 0);
		pow.resize(str.size() + 1, 1);
		for(size_type i = 0; i < str.size(); i++) {
			hash_[i + 1] = mul(hash_[i], base) + xorshift(str[i] + 1);
			pow[i + 1] = mul(pow[i], base);
			if(hash_[i + 1] >= MOD) hash_[i + 1] -= MOD;
		}
	}

	u64 hash() const { return hash_.back(); }
	u64 hash(size_type l, size_type r) const {
		u64 ret = MOD + hash_[r] - mul(hash_[l], pow[r - l]);
		return ret < MOD ? ret : ret - MOD;
	}
	
	size_type size() const { return str.size(); }
};


#line 7 "test/hackerrank/zundamochi.rolling_hash.test.cpp"

int main() {
    int n, k; scanf("%d%d", &n, &k);
    std::string s; std::cin >> s;

    rolling_hash hash(s);
    std::map<std::uint_fast64_t, std::vector<int>> mp;
    for(int i = 0; i < (int)s.size() - k + 1; i++) {
        mp[hash.hash(i, i + k)].push_back(i);
    }

    int ans = 0;
    for(auto vec: mp) {
        int tmp = -k, cnt = 0;
        for(auto v: vec.second) {
            if(tmp + k <= v) {
                tmp = v;
                cnt++;
            }
        }
        ans = std::max(ans, cnt);
    }

    printf("%d\n", ans);
    return 0;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

