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


# :warning: math/fast_fourier_transform.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/fast_fourier_transform.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-19 17:03:37+09:00




## Depends on

* :question: <a href="polynomial.hpp.html">math/polynomial.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef INCLUDED_FAST_FOURIER_TRANSFORM_HPP
#define INCLUDED_FAST_FOURIER_TRANSFORM_HPP

#include "../math/polynomial.hpp"
#include <complex>

template<class T, class Real = double, class Complex = std::complex<Real>>
class fast_fourier_transform: public polynomial<T> {
public:
	using polynomial<T>::polynomial;
	using value_type = typename polynomial<T>::value_type;
	using reference = typename polynomial<T>::reference;
	using const_reference = typename polynomial<T>::const_reference;
	using size_type = typename polynomial<T>::size_type;

private:
	// constexpr Real PI = std::numbers::pi_v<Real>;
	static constexpr Real PI = std::acos(Real(-1));;
	
	void transform(polynomial<Complex>& a, bool inverse = false) {
		size_type n = 0;
		while((1 << n) < a.size()) n++;
		size_type N = 1 << n;
		a.resize(N);

		size_type mask = N - 1;
		polynomial<Complex> tmp(N);
		for(int i = N >> 1; i >= 1; i >>= 1) {
			Real theta = 2 * PI * i * (inverse ? -1 : 1) / N;
			Complex zeta(std::cos(theta), std::sin(theta));
			Complex powZeta(1);

			for(int j = 0; j < N; j += i) {
				for(int k = 0; k < i; k++) {
					tmp[j + k] = a[((j << 1) & mask) | k] + powZeta * a[(((j << 1) | i) & mask) | k];
				}
				powZeta *= zeta;
			}
			a.swap(tmp);
		}

		if(n & 1) {
			std::swap(a, tmp);
			for(int i = 0; i < N; i++) a[i] = tmp[i];
		}
		if(inverse) for(int i = 0; i < N; i++) a[i] /= N;
	}
	fast_fourier_transform convolution(const fast_fourier_transform& ar, const fast_fourier_transform& br) {
		size_type size = ar.degree() + br.degree() + 1;
		polynomial<Complex> a(size);
		for(int i = 0; i < ar.size(); i++) a[i].real(ar[i]);
		for(int i = 0; i < br.size(); i++) a[i].imag(br[i]);
		transform(a, false);
		
		int N = a.size();
		polynomial<Complex> c(N);
		for(int i = 0; i < N; i++) {
			int j = (i == 0 ? 0 : N - i);
			c[i] = (a[i] + conj(a[j])) * (a[i] - conj(a[j])) * Complex(0, -.25);
		}
		transform(c, true);

		fast_fourier_transform ret(size);
		for(int i = 0; i < size; i++) ret[i] = round(c[i].real());
		return ret;
		
	}
public:
	fast_fourier_transform(const polynomial<T>& p): polynomial<T>(p) {}

	fast_fourier_transform operator*(const_reference r) const { return fast_fourier_transform(*this) *= r; }
	fast_fourier_transform& operator*=(const_reference r) {
		for(int i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] * r;
		return *this;
	}
	fast_fourier_transform operator*(const fast_fourier_transform& r) const { return fast_fourier_transform(*this) *= r; }
	fast_fourier_transform& operator*=(const fast_fourier_transform& r) {
		return (*this) = convolution((*this), r);
	}
};

#endif

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math/fast_fourier_transform.hpp"



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


#line 5 "math/fast_fourier_transform.hpp"
#include <complex>

template<class T, class Real = double, class Complex = std::complex<Real>>
class fast_fourier_transform: public polynomial<T> {
public:
	using polynomial<T>::polynomial;
	using value_type = typename polynomial<T>::value_type;
	using reference = typename polynomial<T>::reference;
	using const_reference = typename polynomial<T>::const_reference;
	using size_type = typename polynomial<T>::size_type;

private:
	// constexpr Real PI = std::numbers::pi_v<Real>;
	static constexpr Real PI = std::acos(Real(-1));;
	
	void transform(polynomial<Complex>& a, bool inverse = false) {
		size_type n = 0;
		while((1 << n) < a.size()) n++;
		size_type N = 1 << n;
		a.resize(N);

		size_type mask = N - 1;
		polynomial<Complex> tmp(N);
		for(int i = N >> 1; i >= 1; i >>= 1) {
			Real theta = 2 * PI * i * (inverse ? -1 : 1) / N;
			Complex zeta(std::cos(theta), std::sin(theta));
			Complex powZeta(1);

			for(int j = 0; j < N; j += i) {
				for(int k = 0; k < i; k++) {
					tmp[j + k] = a[((j << 1) & mask) | k] + powZeta * a[(((j << 1) | i) & mask) | k];
				}
				powZeta *= zeta;
			}
			a.swap(tmp);
		}

		if(n & 1) {
			std::swap(a, tmp);
			for(int i = 0; i < N; i++) a[i] = tmp[i];
		}
		if(inverse) for(int i = 0; i < N; i++) a[i] /= N;
	}
	fast_fourier_transform convolution(const fast_fourier_transform& ar, const fast_fourier_transform& br) {
		size_type size = ar.degree() + br.degree() + 1;
		polynomial<Complex> a(size);
		for(int i = 0; i < ar.size(); i++) a[i].real(ar[i]);
		for(int i = 0; i < br.size(); i++) a[i].imag(br[i]);
		transform(a, false);
		
		int N = a.size();
		polynomial<Complex> c(N);
		for(int i = 0; i < N; i++) {
			int j = (i == 0 ? 0 : N - i);
			c[i] = (a[i] + conj(a[j])) * (a[i] - conj(a[j])) * Complex(0, -.25);
		}
		transform(c, true);

		fast_fourier_transform ret(size);
		for(int i = 0; i < size; i++) ret[i] = round(c[i].real());
		return ret;
		
	}
public:
	fast_fourier_transform(const polynomial<T>& p): polynomial<T>(p) {}

	fast_fourier_transform operator*(const_reference r) const { return fast_fourier_transform(*this) *= r; }
	fast_fourier_transform& operator*=(const_reference r) {
		for(int i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] * r;
		return *this;
	}
	fast_fourier_transform operator*(const fast_fourier_transform& r) const { return fast_fourier_transform(*this) *= r; }
	fast_fourier_transform& operator*=(const fast_fourier_transform& r) {
		return (*this) = convolution((*this), r);
	}
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

