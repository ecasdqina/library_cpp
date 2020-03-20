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


# :heavy_check_mark: test/yosupo/convolution_mod.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0b58406058f6619a0f31a172defc0230">test/yosupo</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/convolution_mod.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-20 11:09:12+09:00


* see: <a href="https://judge.yosupo.jp/problem/convolution_mod">https://judge.yosupo.jp/problem/convolution_mod</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/math/modint.hpp.html">math/modint.hpp</a>
* :heavy_check_mark: <a href="../../../library/math/number_theoritic_transform.hpp.html">math/number_theoritic_transform.hpp</a>
* :heavy_check_mark: <a href="../../../library/math/polynomial.hpp.html">math/polynomial.hpp</a>
* :question: <a href="../../../library/other/fast_io.hpp.html">other/fast_io.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../math/number_theoritic_transform.hpp"
#include "../../other/fast_io.hpp"

using mint = modint<998244353>;

int main() {
	int n, m; fin.scan(n, m);
	number_theoritic_transform<mint> a(n), b(m);
	for(int i = 0; i < n; i++) {
		int x; fin.scan(x);
		a[i] = x;
	}
	for(int i = 0; i < m; i++) {
		int x; fin.scan(x);
		b[i] = x;
	}

	for(auto v: a * b) fout.print(v.value(), ' ');
	fout.println();
	return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/convolution_mod.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

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


#line 1 "other/fast_io.hpp"



#include <cstdio>
#line 6 "other/fast_io.hpp"
#include <cstddef>
#include <cstring>
#include <limits>
#include <string>
#include <type_traits>
#include <utility>
#line 13 "other/fast_io.hpp"

namespace fast_io {
	// fast I/O by rsk0315 (update: 2020-03-02 01:10:54).
	static size_t constexpr buf_size = 1 << 17;
	static size_t constexpr margin = 1;
	static char inbuf[buf_size + margin] = {};
	static char outbuf[buf_size + margin] = {};
	static __attribute__((aligned(8))) char minibuf[32];
	static size_t constexpr int_digits = 20;	// 18446744073709551615
	static uintmax_t constexpr digit_mask = 0x3030303030303030;
	static uintmax_t constexpr first_mask = 0x00FF00FF00FF00FF;
	static uintmax_t constexpr second_mask = 0x0000FFFF0000FFFF;
	static uintmax_t constexpr third_mask = 0x00000000FFFFFFFF;
	static uintmax_t constexpr tenpow[] = {
		1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000
	};
	template <typename Tp>
	using enable_if_integral = std::enable_if<std::is_integral<Tp>::value, Tp>;

	class scanner {
		char* pos = inbuf;
		char* endpos = inbuf + buf_size;

		void M_read_from_stdin() {
			endpos = inbuf + fread(pos, 1, buf_size, stdin);
		}
		void M_reread_from_stdin() {
			ptrdiff_t len = endpos - pos;
			if (!(inbuf + len <= pos)) return;
			memcpy(inbuf, pos, len);
			char* tmp = inbuf + len;
			endpos = tmp + fread(tmp, 1, buf_size-len, stdin);
			*endpos = 0;
			pos = inbuf;
		}

	public:
		scanner() { M_read_from_stdin(); }

		template <typename Integral,
							typename enable_if_integral<Integral>::type* = nullptr>
		void scan_parallel(Integral& x) {
			// See https://qiita.com/rsk0315_h4x/items/17a9cb12e0de5fd918f4
			if (__builtin_expect(endpos <= pos + int_digits, 0))
				M_reread_from_stdin();
			bool ends = false;
			typename std::make_unsigned<Integral>::type y = 0;
			bool neg = false;
			if (std::is_signed<Integral>::value && *pos == '-') {
				neg = true;
				++pos;
			}
			do {
				memcpy(minibuf, pos, 8);
				long c = *(long*)minibuf;
				long d = (c & digit_mask) ^ digit_mask;
				int skip = 8;
				int shift = 8;
				if (d) {
					int ctz = __builtin_ctzl(d);
					if (ctz == 4) break;
					c &= (1L << (ctz-5)) - 1;
					int discarded = (68-ctz) / 8;
					shift -= discarded;
					c <<= discarded * 8;
					skip -= discarded;
					ends = true;
				}
				c |= digit_mask;
				c ^= digit_mask;
				c = ((c >> 8) + c*10) & first_mask;
				c = ((c >> 16) + c*100) & second_mask;
				c = ((c >> 32) + c*10000) & third_mask;
				y = y*tenpow[shift] + c;
				pos += skip;
			} while (!ends);
			x = (neg? -y: y);
			++pos;
		}

		template <typename Integral,
							typename enable_if_integral<Integral>::type* = nullptr>
		void scan_serial(Integral& x) {
			if (__builtin_expect(endpos <= pos + int_digits, 0))
				M_reread_from_stdin();
			bool neg = false;
			if (std::is_signed<Integral>::value && *pos == '-') {
				neg = true;
				++pos;
			}
			typename std::make_unsigned<Integral>::type y = *pos-'0';
			while (*++pos >= '0') y = 10*y + *pos-'0';
			x = (neg? -y: y);
			++pos;
		}

		template <typename Integral,
							typename enable_if_integral<Integral>::type* = nullptr>
		// Use scan_parallel(x) only when x may be too large (about 10^12).
		// Otherwise, even when x <= 10^9, scan_serial(x) may be faster.
		void scan(Integral& x) { scan_parallel(x); }

		void scan_serial(std::string& s) {
			// until first whitespace
			s = "";
			do {
				char* startpos = pos;
				while (*pos > ' ') ++pos;
				s += std::string(startpos, pos);
				if (*pos != 0) {
					++pos;	// skip the space
					break;
				}
				M_reread_from_stdin();
			} while (true);
		}

		void scan(std::string& s) { scan_serial(s); }

		void scan(char& c) {
			if (__builtin_expect(endpos <= pos + 2, 0))
				M_reread_from_stdin();
			c = *pos++;
			++pos;
		}

		template<class H, class... T>
		void scan(H& h, T&... t) {
			scan(h);
			scan(t...);
		}
	};

	class printer {
		char* pos = outbuf;

		void M_flush_stdout() {
			fwrite(outbuf, 1, pos-outbuf, stdout);
			pos = outbuf;
		}

		template <typename ... Args>
		char* format(const std::string& fmt, Args ... args ) {
			size_t len = std::snprintf( nullptr, 0, fmt.c_str(), args ... );
			char* buf = new char[len + 1];
			std::snprintf(&buf[0], len + 1, fmt.c_str(), args ... );
			return std::move(buf);
		}

	public:
		printer() = default;
		~printer() { M_flush_stdout(); }

		void print(char c) {
			if (__builtin_expect(pos + 1 >= outbuf + buf_size, 0)) M_flush_stdout();
			*pos++ = c;
		}

		template <size_t N>
		void print(char const(&s)[N]) {
			if (__builtin_expect(pos + N >= outbuf + buf_size, 0)) M_flush_stdout();
			memcpy(pos, s, N-1);
			pos += N-1;
		}

		void print(char const* s) {
			while (*s != 0) {
				*pos++ = *s++;
				if (pos == outbuf + buf_size) M_flush_stdout();
			}
		}
		void print(const bool& x) {
			if(x) print(1);
			else print(0);
		}

		template <typename Integral,
							typename enable_if_integral<Integral>::type* = nullptr>
		void print(Integral x) {
			if (__builtin_expect(pos + int_digits >= outbuf + buf_size, 0))
				M_flush_stdout();
			if (x == 0) {
				*pos++ = '0';
				return;
			}
			if (x < 0) {
				*pos++ = '-';
				if (__builtin_expect(x == std::numeric_limits<Integral>::min(), 0)) {
					switch (sizeof x) {
					case 2: print("32768"); return;
					case 4: print("2147483648"); return;
					case 8: print("9223372036854775808"); return;
					}
				}
				x = -x;
			}
			char* mp = minibuf + sizeof minibuf;
			*--mp = x % 10 + '0';
			size_t len = 1;
			typename std::make_unsigned<Integral>::type y = x / 10;
			while (y > 0) {
				*--mp = y % 10 + '0';
				y /= 10;
				++len;
			}
			memcpy(pos, mp, len);
			pos += len;
		}

		template <typename Tp>
		void println(Tp const& x) { print(x), print('\n'); }

		template<class H, class... T>
		void print(const H& h, const T&... t) {
			print(h);
			print(' ');
			print(t...);
		}
		template<class T>
		void print(const std::vector<T>& t) {
			for(size_t i = 0; i < t.size(); i++) {
				print(t[i]);
				if(i + 1 != t.size()) print(' ');
			}
		}
		template<class... T>
		void println(const T&... t) { print(t...); print('\n'); }
		template<class T>
		void println(const std::vector<T>& t) { print(t); print('\n'); }
		void println() { print('\n'); }
	};
}
fast_io::scanner fin;
fast_io::printer fout;


#line 5 "test/yosupo/convolution_mod.test.cpp"

using mint = modint<998244353>;

int main() {
	int n, m; fin.scan(n, m);
	number_theoritic_transform<mint> a(n), b(m);
	for(int i = 0; i < n; i++) {
		int x; fin.scan(x);
		a[i] = x;
	}
	for(int i = 0; i < m; i++) {
		int x; fin.scan(x);
		b[i] = x;
	}

	for(auto v: a * b) fout.print(v.value(), ' ');
	fout.println();
	return 0;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

