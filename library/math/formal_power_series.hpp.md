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


# :heavy_check_mark: math/formal_power_series.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7e676e9e663beb40fd133f5ee24487c2">math</a>
* <a href="{{ site.github.repository_url }}/blob/master/math/formal_power_series.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-19 18:16:27+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/yosupo/exp_of_formal_power_series.ntt.test.cpp.html">test/yosupo/exp_of_formal_power_series.ntt.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/inv_of_formal_power_series.ntt.test.cpp.html">test/yosupo/inv_of_formal_power_series.ntt.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/log_of_formal_power_series.ntt.test.cpp.html">test/yosupo/log_of_formal_power_series.ntt.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef INCLUDED_FORMAL_POWER_SERIES_HPP
#define INCLUDED_FORMAL_POWER_SERIES_HPP

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

#endif

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

