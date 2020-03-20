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


# :heavy_check_mark: test/yosupo/exp_of_formal_power_series.ntt.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0b58406058f6619a0f31a172defc0230">test/yosupo</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/exp_of_formal_power_series.ntt.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-19 22:54:58+09:00


* see: <a href="https://judge.yosupo.jp/problem/exp_of_formal_power_series">https://judge.yosupo.jp/problem/exp_of_formal_power_series</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/math/formal_power_series.hpp.html">math/formal_power_series.hpp</a>
* :heavy_check_mark: <a href="../../../library/math/modint.hpp.html">math/modint.hpp</a>
* :heavy_check_mark: <a href="../../../library/math/number_theoritic_transform.hpp.html">math/number_theoritic_transform.hpp</a>
* :heavy_check_mark: <a href="../../../library/math/polynomial.hpp.html">math/polynomial.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include <stdio.h>
#include "../../math/number_theoritic_transform.hpp"
#include "../../math/formal_power_series.hpp"

using fps = formal_power_series<number_theoritic_transform<modint<998244353>>>;

int main() {
	int n; scanf("%d", &n);
	fps a(n);
	for(int i = 0; i < n; i++) {
		int x; scanf("%d", &x);

		a[i] = x;
	}

	for(auto v: a.exp()) printf("%d ", v.value());
	printf("\n");
	return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/exp_of_formal_power_series.ntt.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include <stdio.h>
#line 1 "math/number_theoritic_transform.hpp"



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


#line 1 "math/polynomial.hpp"



#include <cstdint>
#include <vector>

template<class T>
class polynomial: public std::vector<T> {
public:
	using std::vector<T>::vector;
	using value_type = typename std::vector<T>::value_type;
	using reference = typename std::vector<T>::reference;
	using const_reference = typename std::vector<T>::const_reference;
	using size_type = typename std::vector<T>::size_type;

private:
	T eval(T x) const {
		T ret = (*this)[0], tmp = x;
		for(int i = 1; i < this->size(); i++) {
			ret = ret + (*this)[i] * tmp;
			tmp = tmp * x;
		}
		return ret;
	}

public:
	polynomial(): std::vector<T>(1, T{}) {}
	polynomial(const std::vector<T>& p): std::vector<T>(p) {}

	polynomial operator+(const polynomial& r) const { return polynomial(*this) += r; }
	polynomial operator-(const polynomial& r) const { return polynomial(*this) -= r; }
	polynomial operator*(const_reference r) const { return polynomial(*this) *= r; }
	polynomial operator/(const_reference r) const { return polynomial(*this) /= r; }
	polynomial operator<<(size_type r) const { return polynomial(*this) <<= r; }
	polynomial operator>>(size_type r) const { return polynomial(*this) >>= r; }
	polynomial operator-() const {
		polynomial ret(this->size());
		for(int i = 0; i < this->size(); i++) ret[i] = -(*this)[i];
		return ret;
	}
	polynomial& operator+=(const polynomial& r) {
		if(r.size() > this->size()) this->resize(r.size());
		for(int i = 0; i < r.size(); i++) (*this)[i] = (*this)[i] + r[i];
		return *this;
	}
	polynomial& operator-=(const polynomial& r) {
		if(r.size() > this->size()) this->resize(r.size());
		for(int i = 0; i < r.size(); i++) (*this)[i] = (*this)[i] - r[i];
		return *this;
	}
	polynomial& operator*=(const_reference r) {
		for(int i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] * r;
		return *this;
	}
	polynomial& operator/=(const_reference r) {
		for(int i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] / r;
		return *this;
	}
	polynomial& operator<<=(size_type r) {
		this->insert(begin(*this), r, T{});
		return *this;
	}
	polynomial& operator>>=(size_type r) {
		if(r >= this->size()) clear();
		else this->erase(begin(*this), begin(*this) + r);
		return *this;
	}

	polynomial differential(size_type k) const {
		polynomial ret(*this);
		for(int i = 0; i < k; i++) ret = ret.differential();
		return ret;
	}
	polynomial differential() const {
		if(degree() < 1) return polynomial();
		polynomial ret(this->size() - 1);
		for(int i = 1; i < this->size(); i++) ret[i - 1] = (*this)[i] * T{i};
		return ret;
	}
	polynomial integral(size_type k) const {
		polynomial ret(*this);
		for(int i = 0; i < k; i++) ret = ret.integral();
		return ret;
	}
	polynomial integral() const {
		polynomial ret(this->size() + 1);
		for(int i = 0; i < this->size(); i++) ret[i + 1] = (*this)[i] / T{i + 1};
		return ret;
	}
	polynomial prefix(size_type size) const {
		if(size == 0) return polynomial();
		return polynomial(begin(*this), begin(*this) + std::min(this->size(), size));
	}
	
	void shrink() {
		while(this->size() > 1 and this->back() == T{}) this->pop_back();
	}
	
	T operator()(T x) const { return eval(x); }
	size_type degree() const { return this->size() - 1; }
	void clear() { this->assign(1, T{}); }
};


#line 6 "math/number_theoritic_transform.hpp"

template<class T, int primitive_root = 3>
class number_theoritic_transform: public polynomial<T> {
public:
	using polynomial<T>::polynomial;
	using value_type = typename polynomial<T>::value_type;
	using reference = typename polynomial<T>::reference;
	using const_reference = typename polynomial<T>::const_reference;
	using size_type = typename polynomial<T>::size_type;

private:
	void ntt(number_theoritic_transform& a) const {
		int N = a.size();
		static std::vector<T> dw;
		if(dw.size() < N) {
			int n = dw.size();
			dw.resize(N);
			for(int i = n; i < N; i++) dw[i] = -(T(primitive_root) ^ ((T::mod - 1) >> i + 2));
		}

		for(int m = N; m >>= 1;) {
			T w = 1;
			for(int s = 0, k = 0; s < N; s += 2 * m) {
				for(int i = s, j = s + m; i < s + m; i++, j++) {
					T x = a[i], y = a[j] * w;
					a[i] = x + y;
					a[j] = x - y;
				}
				w *= dw[__builtin_ctz(++k)];
			}
		}
	}
	void intt(number_theoritic_transform& a) const {
		int N = a.size();
		static std::vector<T> idw;
		if(idw.size() < N) {
			int n = idw.size();
			idw.resize(N);
			for(int i = n; i < N; i++) idw[i] = (-(T(primitive_root) ^ ((T::mod - 1) >> i + 2))).inverse();
		}

		for(int m = 1; m < N; m *= 2) {
			T w = 1;
			for(int s = 0, k = 0; s < N; s += 2 * m) {
				for(int i = s, j = s + m; i < s + m; i++, j++) {
					T x = a[i], y = a[j];
					a[i] = x + y;
					a[j] = (x - y) * w;
				}
				w *= idw[__builtin_ctz(++k)];
			}
		}
	}
	void transform(number_theoritic_transform& a, bool inverse = false) const {
		size_type n = 0;
		while((1 << n) < a.size()) n++;
		size_type N = 1 << n;
		a.resize(N);

		if(!inverse) {
			ntt(a);
		} else {
			intt(a);
			T inv = T(N).inverse();
			for(int i = 0; i < a.size(); i++) a[i] *= inv;
		}
	}

	number_theoritic_transform convolution(const number_theoritic_transform& ar, const number_theoritic_transform& br) const {
		size_type size = ar.degree() + br.degree() + 1;
		number_theoritic_transform a(ar), b(br);
		a.resize(size);
		b.resize(size);
		transform(a, false);
		transform(b, false);

		for(int i = 0; i < a.size(); i++) a[i] *= b[i];
		transform(a, true);
		a.resize(size);
		return a;
	}

public:
	number_theoritic_transform(const polynomial<T>& p): polynomial<T>(p) {}
	
	number_theoritic_transform operator*(const_reference r) const { return number_theoritic_transform(*this) *= r; }
	number_theoritic_transform& operator*=(const_reference r) {
		for(int i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] * r;
		return *this;
	}
	number_theoritic_transform operator*(const number_theoritic_transform& r) const { return number_theoritic_transform(*this) *= r; }
	number_theoritic_transform& operator*=(const number_theoritic_transform& r) {
		return (*this) = convolution((*this), r);
	}
};


#line 1 "math/formal_power_series.hpp"



#include <cassert>
#include <utility>

template<class T>
class formal_power_series: public T {
public:
	using T::T;
	using value_type = typename T::value_type;
	using reference = typename T::reference;
	using const_reference = typename T::const_reference;
	using size_type = typename T::size_type;

private:
	formal_power_series(): T(1) {}
	formal_power_series(const T& p): T(p) {}

public:
	formal_power_series inverse() const {
		assert((*this)[0] != value_type{});

		formal_power_series ret(1, (*this)[0].inverse());
		for(int i = 1; i < this->size(); i <<= 1) {
			auto tmp = ret * this->prefix(i << 1);
			for(int j = 0; j < i; j++) {
				tmp[j] = value_type{};
				if(j + i < tmp.size()) tmp[j + i] *= value_type(-1);
			}
			tmp = tmp * ret;
			for(int j = 0; j < i; j++) tmp[j] = ret[j];
			ret = std::move(tmp).prefix(i << 1);
		}
		return ret.prefix(this->size());
	}
	formal_power_series log() const {
		assert((*this)[0] == value_type(1));
		
		return (formal_power_series(this->differential()) * this->inverse()).integral().prefix(this->size());
	}
	formal_power_series exp() const {
		assert((*this)[0] == value_type{});

		formal_power_series f(1, value_type(1)), g(1, value_type(1));
		for(int i = 1; i < this->size(); i <<= 1) {
			g = (g * value_type(2) - f * g * g).prefix(i);
			formal_power_series q = this->differential().prefix(i - 1);
			formal_power_series w = (q + g * (f.differential() - f * q)).prefix((i << 1) - 1);
			f = (f + f * (*this - w.integral()).prefix(i << 1)).prefix(i << 1);

		}
		return f.prefix(this->size());
	}
	formal_power_series pow(size_type k) const {
		for(size_type i = 0; i < this->size(); i++) {
			if((*this)[i] != value_type{}) {
				value_type inv = (*this)[i].inverse();
				formal_power_series f(*this * inv);
				formal_power_series g(f >> i);
				g = formal_power_series(g.log() * value_type(k)).exp() * (*this)[i].pow(k);
				if(i * k > this->size()) return formal_power_series(this->size());

				return (g << (i * k)).prefix(this->size());
			}
		}
		return *this;
	}
};


#line 6 "test/yosupo/exp_of_formal_power_series.ntt.test.cpp"

using fps = formal_power_series<number_theoritic_transform<modint<998244353>>>;

int main() {
	int n; scanf("%d", &n);
	fps a(n);
	for(int i = 0; i < n; i++) {
		int x; scanf("%d", &x);

		a[i] = x;
	}

	for(auto v: a.exp()) printf("%d ", v.value());
	printf("\n");
	return 0;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
