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


# :heavy_check_mark: math/polynomial.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/polynomial.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-19 17:03:37+09:00




## Required by

* :heavy_check_mark: <a href="arbitary_mod_number_theoritic_transform.hpp.html">math/arbitary_mod_number_theoritic_transform.hpp</a>
* :warning: <a href="fast_fourier_transform.hpp.html">math/fast_fourier_transform.hpp</a>
* :heavy_check_mark: <a href="number_theoritic_transform.hpp.html">math/number_theoritic_transform.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/yosupo/convolution_mod.test.cpp.html">test/yosupo/convolution_mod.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp.html">test/yosupo/convolution_mod_1000000007.arbitary_mod_ntt.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/exp_of_formal_power_series.ntt.test.cpp.html">test/yosupo/exp_of_formal_power_series.ntt.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/inv_of_formal_power_series.ntt.test.cpp.html">test/yosupo/inv_of_formal_power_series.ntt.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/log_of_formal_power_series.ntt.test.cpp.html">test/yosupo/log_of_formal_power_series.ntt.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef INCLUDED_POLYNOMIAL_HPP
#define INCLUDED_POLYNOMIAL_HPP

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

#endif

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

