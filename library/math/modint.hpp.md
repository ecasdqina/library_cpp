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
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :question: math/modint.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/modint.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-19 17:03:37+09:00




## Required by

* :heavy_check_mark: <a href="arbitary_mod_number_theoritic_transform.hpp.html">math/arbitary_mod_number_theoritic_transform.hpp</a>
* :question: <a href="number_theoritic_transform.hpp.html">math/number_theoritic_transform.hpp</a>
* :warning: <a href="../test/yosupo/exp_of_formal_power_series.ntt.test .hpp.html">test/yosupo/exp_of_formal_power_series.ntt.test .hpp</a>
* :warning: <a href="../test/yosupo/log_of_formal_power_series.ntt.test  .hpp.html">test/yosupo/log_of_formal_power_series.ntt.test  .hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/yosupo/convolution_mod.test.cpp.html">test/yosupo/convolution_mod.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp.html">test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp</a>
* :x: <a href="../../verify/test/yosupo/inv_of_formal_power_series.ntt.test.hpp.html">test/yosupo/inv_of_formal_power_series.ntt.test.hpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/point_set_range_composite.segment_tree.test.cpp.html">test/yosupo/point_set_range_composite.segment_tree.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef INCLUDED_MODINT_HPP
#define INCLUDED_MODINT_HPP

#include <iostream>

template <std::uint_fast64_t Modulus>
class modint {
	using u32 = std::uint_fast32_t;
	using u64 = std::uint_fast64_t;
	using i64 = std::int_fast64_t;

	inline u64 apply(i64 x) { return (x < 0 ? x + Modulus : x); };

public:
	u64 a;
	static constexpr u64 mod = Modulus;

	constexpr modint(const i64& x = 0) noexcept: a(apply(x % (i64)Modulus)) {}

	constexpr modint operator+(const modint& rhs) const noexcept { return modint(*this) += rhs; }
	constexpr modint operator-(const modint& rhs) const noexcept { return modint(*this) -= rhs; }	
	constexpr modint operator*(const modint& rhs) const noexcept { return modint(*this) *= rhs; }
	constexpr modint operator/(const modint& rhs) const noexcept { return modint(*this) /= rhs; }
	constexpr modint operator^(const u64& k) const noexcept { return modint(*this) ^= k; }
	constexpr modint operator^(const modint& k) const noexcept { return modint(*this) ^= k.value(); }
	constexpr modint operator-() const noexcept { return modint(Modulus - a); }
	constexpr modint operator++() noexcept { return (*this) = modint(*this) + 1; }
	constexpr modint operator--() noexcept { return (*this) = modint(*this) - 1; }
	const bool operator==(const modint& rhs) const noexcept { return a == rhs.a; };
	const bool operator!=(const modint& rhs) const noexcept { return a != rhs.a; };
	const bool operator<=(const modint& rhs) const noexcept { return a <= rhs.a; };
	const bool operator>=(const modint& rhs) const noexcept { return a >= rhs.a; };
	const bool operator<(const modint& rhs) const noexcept { return a < rhs.a; };
	const bool operator>(const modint& rhs) const noexcept { return a > rhs.a; };
	constexpr modint& operator+=(const modint& rhs) noexcept {
		a += rhs.a;
		if (a >= Modulus) a -= Modulus;
		return *this;
	}
	constexpr modint& operator-=(const modint& rhs) noexcept {
		if (a < rhs.a) a += Modulus;
		a -= rhs.a;
		return *this;
	}
	constexpr modint& operator*=(const modint& rhs) noexcept {
		a = a * rhs.a % Modulus;
		return *this;
	}
	constexpr modint& operator/=(modint rhs) noexcept {
		u64 exp = Modulus - 2;
		while (exp) {
			if (exp % 2) (*this) *= rhs;
			
			rhs *= rhs;
			exp /= 2;
		}
		return *this;
	}
	constexpr modint& operator^=(u64 k) noexcept {
		auto b = modint(1);
		while(k) {
			if(k & 1) b = b * (*this);
			(*this) *= (*this);
			k >>= 1;
		}
		return (*this) = b;
	}
	constexpr modint& operator=(const modint& rhs) noexcept {
		a = rhs.a;
		return (*this);
	}

	constexpr u64& value() noexcept { return a; }
	constexpr const u64& value() const noexcept { return a; }
	explicit operator bool() const { return a; }
	explicit operator u32() const { return a; }

	const modint inverse() const {
		return modint(1) / *this;
	}
	const modint pow(i64 k) const {
		return modint(*this) ^ k;
	}

	friend std::ostream& operator<<(std::ostream& os, const modint& p) {
		return os << p.a;
	}
	friend std::istream& operator>>(std::istream& is, modint& p) {
		u64 t;
		is >> t;
		p = modint(t);
		return is;
	}
};

#endif

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/modint.hpp"



#include <iostream>

template <std::uint_fast64_t Modulus>
class modint {
	using u32 = std::uint_fast32_t;
	using u64 = std::uint_fast64_t;
	using i64 = std::int_fast64_t;

	inline u64 apply(i64 x) { return (x < 0 ? x + Modulus : x); };

public:
	u64 a;
	static constexpr u64 mod = Modulus;

	constexpr modint(const i64& x = 0) noexcept: a(apply(x % (i64)Modulus)) {}

	constexpr modint operator+(const modint& rhs) const noexcept { return modint(*this) += rhs; }
	constexpr modint operator-(const modint& rhs) const noexcept { return modint(*this) -= rhs; }	
	constexpr modint operator*(const modint& rhs) const noexcept { return modint(*this) *= rhs; }
	constexpr modint operator/(const modint& rhs) const noexcept { return modint(*this) /= rhs; }
	constexpr modint operator^(const u64& k) const noexcept { return modint(*this) ^= k; }
	constexpr modint operator^(const modint& k) const noexcept { return modint(*this) ^= k.value(); }
	constexpr modint operator-() const noexcept { return modint(Modulus - a); }
	constexpr modint operator++() noexcept { return (*this) = modint(*this) + 1; }
	constexpr modint operator--() noexcept { return (*this) = modint(*this) - 1; }
	const bool operator==(const modint& rhs) const noexcept { return a == rhs.a; };
	const bool operator!=(const modint& rhs) const noexcept { return a != rhs.a; };
	const bool operator<=(const modint& rhs) const noexcept { return a <= rhs.a; };
	const bool operator>=(const modint& rhs) const noexcept { return a >= rhs.a; };
	const bool operator<(const modint& rhs) const noexcept { return a < rhs.a; };
	const bool operator>(const modint& rhs) const noexcept { return a > rhs.a; };
	constexpr modint& operator+=(const modint& rhs) noexcept {
		a += rhs.a;
		if (a >= Modulus) a -= Modulus;
		return *this;
	}
	constexpr modint& operator-=(const modint& rhs) noexcept {
		if (a < rhs.a) a += Modulus;
		a -= rhs.a;
		return *this;
	}
	constexpr modint& operator*=(const modint& rhs) noexcept {
		a = a * rhs.a % Modulus;
		return *this;
	}
	constexpr modint& operator/=(modint rhs) noexcept {
		u64 exp = Modulus - 2;
		while (exp) {
			if (exp % 2) (*this) *= rhs;
			
			rhs *= rhs;
			exp /= 2;
		}
		return *this;
	}
	constexpr modint& operator^=(u64 k) noexcept {
		auto b = modint(1);
		while(k) {
			if(k & 1) b = b * (*this);
			(*this) *= (*this);
			k >>= 1;
		}
		return (*this) = b;
	}
	constexpr modint& operator=(const modint& rhs) noexcept {
		a = rhs.a;
		return (*this);
	}

	constexpr u64& value() noexcept { return a; }
	constexpr const u64& value() const noexcept { return a; }
	explicit operator bool() const { return a; }
	explicit operator u32() const { return a; }

	const modint inverse() const {
		return modint(1) / *this;
	}
	const modint pow(i64 k) const {
		return modint(*this) ^ k;
	}

	friend std::ostream& operator<<(std::ostream& os, const modint& p) {
		return os << p.a;
	}
	friend std::istream& operator>>(std::istream& is, modint& p) {
		u64 t;
		is >> t;
		p = modint(t);
		return is;
	}
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

