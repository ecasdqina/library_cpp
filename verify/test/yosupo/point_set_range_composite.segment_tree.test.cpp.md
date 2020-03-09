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


# :heavy_check_mark: test/yosupo/point_set_range_composite.segment_tree.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/point_set_range_composite.segment_tree.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-09 16:03:42+09:00


* see: <a href="https://judge.yosupo.jp/problem/point_set_range_composite">https://judge.yosupo.jp/problem/point_set_range_composite</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/data_structure/segment_tree.hpp.html">data_structure/segment_tree.hpp</a>
* :heavy_check_mark: <a href="../../../library/math/modint.hpp.html">math/modint.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include <stdio.h>
#include "../../data_structure/segment_tree.hpp"
#include "../../math/modint.hpp"

using mint = modint<998244353>;

struct node {
	mint a, b;

	node(mint a = 1, mint b = 0): a(a), b(b) {}
	node operator+(node r) const { return node(r.a * a, r.a * b + r.b); }
	mint eval(mint x) { return a * x + b; }
};

int main() {
	int n, q; scanf("%d%d", &n, &q);
	segment_tree<monoid<node>> seg(n);
	for(int i = 0; i < n; i++) {
		int a, b; scanf("%d%d", &a, &b);

		seg.change(i, node(a, b));
	}

	while(q--) {
		int type, x, y, z; scanf("%d%d%d%d", &type, &x, &y, &z);

		if(type == 0) seg.change(x, node(y, z));
		if(type == 1) printf("%llu\n", seg.fold(x, y).eval(z));
	}
	return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/point_set_range_composite.segment_tree.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include <stdio.h>
#line 1 "test/yosupo/../../data_structure/segment_tree.hpp"
#include <cstdint>
#include <vector>
#include <functional>

template<class Monoid>
class segment_tree {
public:
	using T = typename Monoid::value_type;
	using size_type = std::uint_fast32_t;

	using updator = std::function<T(T)>;
	using checker = std::function<bool(T)>;
	
private:
	const size_type size_;
	size_type height_;

public:
	std::vector<T> data;
	
private:
	const size_type get_height(size_type size) const {
		size_type height = 1;
		while(1 << height <= size) height++;
		return height;
	}
	const size_type base_size() const { return 1 << height_; }

	void meld(size_type index) {
		data[index] = Monoid::operation(data[index << 1 ^ 0], data[index << 1 ^ 1]);
	}

public:
	segment_tree() = default;
	segment_tree(segment_tree&&) = default;
	segment_tree(const segment_tree&) = default;
	
	segment_tree(size_type size)
		: size_(size) {
		height_ = get_height(size);
		data.assign(base_size() << 1, T{});
	}
	T fold(size_type left, size_type right) {
		T l_value = T{};
		T r_value = T{};

		for(left += base_size(), right += base_size();
			left < right;
			left >>= 1, right >>= 1) {
			if(left & 1)  l_value = Monoid::operation(l_value, data[left++]);
			if(right & 1) r_value = Monoid::operation(data[--right], r_value); 
		}
		return Monoid::operation(std::move(l_value), std::move(r_value));
	}

	void update(size_type index, const updator& update) {
		index += base_size();
		data[index] = update(data[index]);

		while(index >>= 1) meld(index);
	}
	void update(size_type index, const T& value) { update(index, [&value](const T& x) { return Monoid::operation(x, value); }); }
	void change(size_type index, const T& value) { update(index, [&value](const T& x) { return value; }); }
	
	const size_type search(size_type left, const checker& check) {
		T val = T{};
		size_type k = left + base_size();
		while(true) {
			if(check(Monoid::operation(val, data[k]))) {
				val = Monoid::operation(val, data[k]);
				if(k & 1) {
					if((k + 1) & k) k = (k + 1) >> 1;
					else return size();
				} else {
					k = k + 1;
				}
			} else {
				if(k < base_size()) {
					k = k << 1 ^ 0;
				} else {
					return k - base_size();
				}
			}
		}
	}
	
	const T operator[](size_type index) const { return data[index + base_size()]; }
	const size_type size() const { return size_; }
	const bool empty() const { return data.empty(); }
};

template<class T>
struct monoid {
	using value_type = T;

	static value_type operation(const value_type& a, const value_type& b) { return a + b; };
};

// @docs docs/segment_tree.md
#line 1 "test/yosupo/../../math/modint.hpp"
#include <iostream>

template <std::uint_fast64_t Modulus>
class modint {
	using u32 = std::uint_fast32_t;
	using u64 = std::uint_fast64_t;
	using i64 = std::int_fast64_t;

	inline u64 apply(i64 x) { return (x >= 0 ? x : x + Modulus); };

public:
	u64 a;
	static constexpr u64 mod = Modulus;

	constexpr modint(const u64 & x = 0) noexcept : a(x % Modulus) {}

	constexpr u64 &value() noexcept { return a; }
	constexpr const u64 &value() const noexcept { return a; }

	const modint inverse() const {
		return modint(1) / *this;
	}
	const modint pow(i64 k) const {
		return modint(*this) ^ k;
	}

	constexpr modint & operator+=(const modint & rhs) noexcept {
		a += rhs.a;
		if (a >= Modulus) a -= Modulus;
		return *this;
	}
	constexpr modint & operator-=(const modint & rhs) noexcept {
		if (a < rhs.a) a += Modulus;
		a -= rhs.a;
		return *this;
	}
	constexpr modint & operator*=(const modint & rhs) noexcept {
		a = a * rhs.a % Modulus;
		return *this;
	}
	constexpr modint & operator/=(modint rhs) noexcept {
		u64 exp = Modulus - 2;
		while (exp) {
			if (exp % 2) (*this) *= rhs;
			
			rhs *= rhs;
			exp /= 2;
		}
		return *this;
	}
	constexpr modint & operator^=(u64 k) noexcept {
		auto b = modint(1);
		while(k) {
			if(k & 1) b = b * (*this);
			(*this) *= (*this);
			k >>= 1;
		}
		return (*this) = b;
	}
	constexpr modint & operator=(const modint & rhs) noexcept {
		a = rhs.a;
		return (*this);
	}
	constexpr modint operator+(const modint & rhs) const noexcept { return modint(*this) += rhs; }
	constexpr modint operator-(const modint & rhs) const noexcept { return modint(*this) -= rhs; }	
	constexpr modint operator*(const modint & rhs) const noexcept { return modint(*this) *= rhs; }
	constexpr modint operator/(const modint & rhs) const noexcept { return modint(*this) /= rhs; }
	constexpr modint operator^(const u64 & k) const noexcept { return modint(*this) ^= k; }
	constexpr modint operator-() const noexcept { return modint(Modulus - a); }
	constexpr modint operator++() noexcept { return (*this) = modint(*this) + 1; }
	constexpr modint operator--() noexcept { return (*this) = modint(*this) - 1; }
	const bool operator==(const modint & rhs) const noexcept { return a == rhs.a; };
	const bool operator!=(const modint & rhs) const noexcept { return a != rhs.a; };
	const bool operator<=(const modint & rhs) const noexcept { return a <= rhs.a; };
	const bool operator>=(const modint & rhs) const noexcept { return a >= rhs.a; };
	const bool operator<(const modint & rhs) const noexcept { return a < rhs.a; };
	const bool operator>(const modint & rhs) const noexcept { return a > rhs.a; };
	explicit operator bool() const { return a; }
	explicit operator u32() const { return a; }

	friend std::ostream & operator<<(std::ostream & os, const modint & p) {
		return os << p.a;
	}
	friend std::istream & operator>>(std::istream & is, modint & p) {
		u64 t;
		is >> t;
		p = modint(t);
		return is;
	}
};
#line 6 "test/yosupo/point_set_range_composite.segment_tree.test.cpp"

using mint = modint<998244353>;

struct node {
	mint a, b;

	node(mint a = 1, mint b = 0): a(a), b(b) {}
	node operator+(node r) const { return node(r.a * a, r.a * b + r.b); }
	mint eval(mint x) { return a * x + b; }
};

int main() {
	int n, q; scanf("%d%d", &n, &q);
	segment_tree<monoid<node>> seg(n);
	for(int i = 0; i < n; i++) {
		int a, b; scanf("%d%d", &a, &b);

		seg.change(i, node(a, b));
	}

	while(q--) {
		int type, x, y, z; scanf("%d%d%d%d", &type, &x, &y, &z);

		if(type == 0) seg.change(x, node(y, z));
		if(type == 1) printf("%llu\n", seg.fold(x, y).eval(z));
	}
	return 0;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

