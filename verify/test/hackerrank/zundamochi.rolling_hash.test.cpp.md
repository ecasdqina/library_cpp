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
    - Last commit date: 2020-03-20 11:14:02+09:00


* see: <a href="https://www.hackerrank.com/contests/kiritan-birthday-contest-2020/challenges/zundamochi">https://www.hackerrank.com/contests/kiritan-birthday-contest-2020/challenges/zundamochi</a>


## Depends on

* :question: <a href="../../../library/other/fast_io.hpp.html">other/fast_io.hpp</a>
* :question: <a href="../../../library/string/rolling_hash.hpp.html">string/rolling_hash.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://www.hackerrank.com/contests/kiritan-birthday-contest-2020/challenges/zundamochi"

#include <map>
#include "../../string/rolling_hash.hpp"
#include "../../other/fast_io.hpp"

int main() {
    int n, k; fin.scan(n, k);
    std::string s; fin.scan(s);

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

	fout.println(ans);
    return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/hackerrank/zundamochi.rolling_hash.test.cpp"
#define PROBLEM "https://www.hackerrank.com/contests/kiritan-birthday-contest-2020/challenges/zundamochi"

#include <map>
#line 1 "string/rolling_hash.hpp"



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


#line 1 "other/fast_io.hpp"



#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <limits>
#line 10 "other/fast_io.hpp"
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


#line 6 "test/hackerrank/zundamochi.rolling_hash.test.cpp"

int main() {
    int n, k; fin.scan(n, k);
    std::string s; fin.scan(s);

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

	fout.println(ans);
    return 0;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

