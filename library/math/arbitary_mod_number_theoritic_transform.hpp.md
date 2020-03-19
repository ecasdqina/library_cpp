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


# :heavy_check_mark: math/arbitary_mod_number_theoritic_transform.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/arbitary_mod_number_theoritic_transform.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-19 17:03:37+09:00




## Depends on

* :heavy_check_mark: <a href="modint.hpp.html">math/modint.hpp</a>
* :heavy_check_mark: <a href="number_theoritic_transform.hpp.html">math/number_theoritic_transform.hpp</a>
* :heavy_check_mark: <a href="polynomial.hpp.html">math/polynomial.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp.html">test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef INCLUDED_ARBITARY_MOD_NUMBER_THEORITIC_TRANSFORM_HPP
#define INCLUDED_ARBITARY_MOD_NUMBER_THEORITIC_TRANSFORM_HPP

#include "../math/modint.hpp"
#include "../math/polynomial.hpp"
#include "../math/number_theoritic_transform.hpp"

namespace amnttlib {
	using u64 = std::uint_fast64_t;

	// https://lumakernel.github.io/ecasdqina/math/FFT/NTT
	constexpr u64 ntt_primes[][2] = {
		{1224736769, 3}, // 2^24 * 73 + 1,
		{1053818881, 7}, // 2^20 * 3 * 5 * 67 + 1
		{1051721729, 6}, // 2^20 * 17 * 59 + 1
		{1045430273, 3}, // 2^20 * 997 + 1
		{1012924417, 5}, // 2^21 * 3 * 7 * 23 + 1
		{1007681537, 3}, // 2^20 * 31^2 + 1
		{1004535809, 3}, // 2^21 * 479 + 1
		{998244353, 3},  // 2^23 * 7 * 17 + 1
		{985661441, 3},  // 2^22 * 5 * 47 + 1
		{976224257, 3},  // 2^20 * 7^2 * 19 + 1
		{975175681, 17}, // 2^21 * 3 * 5 * 31 + 1
		{962592769, 7},  // 2^21 * 3^3 * 17 + 1
		{950009857, 7},  // 2^21 * 4 * 151 + 1
		{943718401, 7},  // 2^22 * 3^2 * 5^2 + 1
		{935329793, 3},  // 2^22 * 223 + 1
		{924844033, 5},  // 2^21 * 3^2 * 7^2 + 1
		{469762049, 3},  // 2^26 * 7 + 1
		{167772161, 3},  // 2^25 * 5 + 1
	};
};

template<class T,
	amnttlib::u64 MOD_1 = amnttlib::ntt_primes[0][0],
	amnttlib::u64 PRR_1 = amnttlib::ntt_primes[0][1],
	amnttlib::u64 MOD_2 = amnttlib::ntt_primes[2][0],
	amnttlib::u64 PRR_2 = amnttlib::ntt_primes[2][1],
	amnttlib::u64 MOD_3 = amnttlib::ntt_primes[3][0],
	amnttlib::u64 PRR_3 = amnttlib::ntt_primes[3][1]
> class arbitary_mod_number_theoritic_transform: public polynomial<T> {
public:
	using polynomial<T>::polynomial;
	using value_type = typename polynomial<T>::value_type;
	using reference = typename polynomial<T>::reference;
	using const_reference = typename polynomial<T>::const_reference;
	using size_type = typename polynomial<T>::size_type;

	using amntt = arbitary_mod_number_theoritic_transform;
	using m1 = modint<MOD_1>;
	using m2 = modint<MOD_2>;
	using m3 = modint<MOD_3>;

private:
	amntt convolution(const amntt& ar, const amntt& br) {
		number_theoritic_transform<m1, PRR_1> ntt1_a(ar.size()), ntt1_b(br.size());
		number_theoritic_transform<m2, PRR_2> ntt2_a(ar.size()), ntt2_b(br.size());
		number_theoritic_transform<m3, PRR_3> ntt3_a(ar.size()), ntt3_b(br.size());
		for(int i = 0; i < ar.size(); i++) {
			ntt1_a[i] = m1(ar[i].value());
			ntt2_a[i] = m2(ar[i].value());
			ntt3_a[i] = m3(ar[i].value());
		}
		for(int i = 0; i < br.size(); i++) {
			ntt1_b[i] = m1(br[i].value());
			ntt2_b[i] = m2(br[i].value());
			ntt3_b[i] = m3(br[i].value());
		}
		auto x = ntt1_a * ntt1_b;
		auto y = ntt2_a * ntt2_b;
		auto z = ntt3_a * ntt3_b;

		amntt ret(x.size());
		const m2 m1_inv_m2 = m2(MOD_1).inverse();
		const m3 m12_inv_m3 = (m3(MOD_1) * m3(MOD_2)).inverse();
		const T m12 = T(MOD_1) * T(MOD_2);
		for(int i = 0; i < ret.size(); i++) {
			m2 v1 = (m2(y[i].value()) - m2(x[i].value())) * m1_inv_m2;
			m3 v2 = (m3(z[i].value()) - (m3(x[i].value()) + m3(MOD_1) * m3(v1.value()))) * m12_inv_m3;
			ret[i] = (T(x[i].value()) + T(MOD_1) * T(v1.value()) + m12 * T(v2.value()));
		}
		ret.resize(ar.degree() + br.degree() + 1);
		return ret;
	}
	
public:
	arbitary_mod_number_theoritic_transform(const polynomial<T>& p): polynomial<T>(p) {}


	amntt operator*(const_reference r) const { return amntt(*this) *= r; }
	amntt& operator*=(const_reference r) {
		for(int i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] * r;
		return *this;
	}
	amntt operator*(const amntt& r) const { return amntt(*this) *= r; }
	amntt& operator*=(const amntt& r) {
		return (*this) = convolution((*this), r);
	}
};

#endif

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/arbitary_mod_number_theoritic_transform.hpp"



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


#line 1 "math/number_theoritic_transform.hpp"



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


#line 7 "math/arbitary_mod_number_theoritic_transform.hpp"

namespace amnttlib {
	using u64 = std::uint_fast64_t;

	// https://lumakernel.github.io/ecasdqina/math/FFT/NTT
	constexpr u64 ntt_primes[][2] = {
		{1224736769, 3}, // 2^24 * 73 + 1,
		{1053818881, 7}, // 2^20 * 3 * 5 * 67 + 1
		{1051721729, 6}, // 2^20 * 17 * 59 + 1
		{1045430273, 3}, // 2^20 * 997 + 1
		{1012924417, 5}, // 2^21 * 3 * 7 * 23 + 1
		{1007681537, 3}, // 2^20 * 31^2 + 1
		{1004535809, 3}, // 2^21 * 479 + 1
		{998244353, 3},  // 2^23 * 7 * 17 + 1
		{985661441, 3},  // 2^22 * 5 * 47 + 1
		{976224257, 3},  // 2^20 * 7^2 * 19 + 1
		{975175681, 17}, // 2^21 * 3 * 5 * 31 + 1
		{962592769, 7},  // 2^21 * 3^3 * 17 + 1
		{950009857, 7},  // 2^21 * 4 * 151 + 1
		{943718401, 7},  // 2^22 * 3^2 * 5^2 + 1
		{935329793, 3},  // 2^22 * 223 + 1
		{924844033, 5},  // 2^21 * 3^2 * 7^2 + 1
		{469762049, 3},  // 2^26 * 7 + 1
		{167772161, 3},  // 2^25 * 5 + 1
	};
};

template<class T,
	amnttlib::u64 MOD_1 = amnttlib::ntt_primes[0][0],
	amnttlib::u64 PRR_1 = amnttlib::ntt_primes[0][1],
	amnttlib::u64 MOD_2 = amnttlib::ntt_primes[2][0],
	amnttlib::u64 PRR_2 = amnttlib::ntt_primes[2][1],
	amnttlib::u64 MOD_3 = amnttlib::ntt_primes[3][0],
	amnttlib::u64 PRR_3 = amnttlib::ntt_primes[3][1]
> class arbitary_mod_number_theoritic_transform: public polynomial<T> {
public:
	using polynomial<T>::polynomial;
	using value_type = typename polynomial<T>::value_type;
	using reference = typename polynomial<T>::reference;
	using const_reference = typename polynomial<T>::const_reference;
	using size_type = typename polynomial<T>::size_type;

	using amntt = arbitary_mod_number_theoritic_transform;
	using m1 = modint<MOD_1>;
	using m2 = modint<MOD_2>;
	using m3 = modint<MOD_3>;

private:
	amntt convolution(const amntt& ar, const amntt& br) {
		number_theoritic_transform<m1, PRR_1> ntt1_a(ar.size()), ntt1_b(br.size());
		number_theoritic_transform<m2, PRR_2> ntt2_a(ar.size()), ntt2_b(br.size());
		number_theoritic_transform<m3, PRR_3> ntt3_a(ar.size()), ntt3_b(br.size());
		for(int i = 0; i < ar.size(); i++) {
			ntt1_a[i] = m1(ar[i].value());
			ntt2_a[i] = m2(ar[i].value());
			ntt3_a[i] = m3(ar[i].value());
		}
		for(int i = 0; i < br.size(); i++) {
			ntt1_b[i] = m1(br[i].value());
			ntt2_b[i] = m2(br[i].value());
			ntt3_b[i] = m3(br[i].value());
		}
		auto x = ntt1_a * ntt1_b;
		auto y = ntt2_a * ntt2_b;
		auto z = ntt3_a * ntt3_b;

		amntt ret(x.size());
		const m2 m1_inv_m2 = m2(MOD_1).inverse();
		const m3 m12_inv_m3 = (m3(MOD_1) * m3(MOD_2)).inverse();
		const T m12 = T(MOD_1) * T(MOD_2);
		for(int i = 0; i < ret.size(); i++) {
			m2 v1 = (m2(y[i].value()) - m2(x[i].value())) * m1_inv_m2;
			m3 v2 = (m3(z[i].value()) - (m3(x[i].value()) + m3(MOD_1) * m3(v1.value()))) * m12_inv_m3;
			ret[i] = (T(x[i].value()) + T(MOD_1) * T(v1.value()) + m12 * T(v2.value()));
		}
		ret.resize(ar.degree() + br.degree() + 1);
		return ret;
	}
	
public:
	arbitary_mod_number_theoritic_transform(const polynomial<T>& p): polynomial<T>(p) {}


	amntt operator*(const_reference r) const { return amntt(*this) *= r; }
	amntt& operator*=(const_reference r) {
		for(int i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] * r;
		return *this;
	}
	amntt operator*(const amntt& r) const { return amntt(*this) *= r; }
	amntt& operator*=(const amntt& r) {
		return (*this) = convolution((*this), r);
	}
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

