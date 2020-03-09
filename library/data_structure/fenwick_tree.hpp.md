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


# :heavy_check_mark: data_structure/fenwick_tree.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/fenwick_tree.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-09 14:42:34+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/yosupo/point_add_range_sum.fenwick_tree.test.cpp.html">test/yosupo/point_add_range_sum.fenwick_tree.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <functional>
#include <vector>

template<class CommutativeMonoid>
class fenwick_tree {
public:
	using T = typename CommutativeMonoid::value_type;
	using size_type = std::uint_fast32_t;

	using checker = std::function<bool(T)>;

	std::vector<T> data;
	
private:
	size_type get_lsb(size_type i) const { return i & (~i + 1); }
	
public:
	fenwick_tree() = default;
	fenwick_tree(const fenwick_tree &) = default;
	fenwick_tree(fenwick_tree &&) = default;

	fenwick_tree(size_type size): data(size + 1, T{}) {}

	template<class InputIt>
	fenwick_tree(InputIt first, InputIt last) : fenwick_tree(std::distance(first, last)) {
		for(int index = 0; first != last; first++, index++) add(index, *first);
	}
	
	fenwick_tree & operator=(const fenwick_tree &) = default;
	fenwick_tree & operator=(fenwick_tree &&) = default;

	T fold(size_type last) const {
		T acc{};
		while(last) {
			acc = CommutativeMonoid::operation(data[last], acc);

			last -= get_lsb(last);
		}
		
		return acc;
	}
	T fold(size_type first, size_type last) const {
		T acc{};
		while(first < last) {
			acc = CommutativeMonoid::operation(data[last], acc);

			last -= get_lsb(last);
		}

		while(last < first) {
			acc = CommutativeMonoid::operation(CommutativeMonoid::inverse(data[first]), acc);

			first -= get_lsb(first);
		}
		
		return acc;
	}
	void update(size_type index, const T& value) {
		for(++index; index < data.size(); index += get_lsb(index)) {
			data[index] = CommutativeMonoid::operation(data[index], value);
		}
	}
	void change(size_type index, const T& value) {
		update(index, CommutativeMonoid::operation(CommutativeMonoid::inverse((*this)[index]), value));
	}

	// min{x | f(fold(x)) = true}
	template<class F>
	size_type search(const F & f) {
		if(f(T{})) return 0;

		T acc{};
		size_type i = 0, k = data.size();
		while(k >>= 1) {
			if((i | k) < data.size() and !f(CommutativeMonoid::operation(acc, data[i | k]))) {
				acc = CommutativeMonoid::operation(acc, data[i | k]);
				i |= k;
			}
		}
		return i + 1;
	}

	T operator[](const size_type& k) const { return fold(k, k + 1); };

	bool empty() const { return size() == 0; }
	size_type size() const { return data.size() - 1; }
	void swap(fenwick_tree & r) { data.swap(r.data); }
};

template<class T>
struct monoid {
	using value_type = T;

	static value_type operation(const value_type& a, const value_type& b) { return a + b; };
	static value_type inverse(const value_type& x) { return -x; }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/fenwick_tree.hpp"
#include <functional>
#include <vector>

template<class CommutativeMonoid>
class fenwick_tree {
public:
	using T = typename CommutativeMonoid::value_type;
	using size_type = std::uint_fast32_t;

	using checker = std::function<bool(T)>;

	std::vector<T> data;
	
private:
	size_type get_lsb(size_type i) const { return i & (~i + 1); }
	
public:
	fenwick_tree() = default;
	fenwick_tree(const fenwick_tree &) = default;
	fenwick_tree(fenwick_tree &&) = default;

	fenwick_tree(size_type size): data(size + 1, T{}) {}

	template<class InputIt>
	fenwick_tree(InputIt first, InputIt last) : fenwick_tree(std::distance(first, last)) {
		for(int index = 0; first != last; first++, index++) add(index, *first);
	}
	
	fenwick_tree & operator=(const fenwick_tree &) = default;
	fenwick_tree & operator=(fenwick_tree &&) = default;

	T fold(size_type last) const {
		T acc{};
		while(last) {
			acc = CommutativeMonoid::operation(data[last], acc);

			last -= get_lsb(last);
		}
		
		return acc;
	}
	T fold(size_type first, size_type last) const {
		T acc{};
		while(first < last) {
			acc = CommutativeMonoid::operation(data[last], acc);

			last -= get_lsb(last);
		}

		while(last < first) {
			acc = CommutativeMonoid::operation(CommutativeMonoid::inverse(data[first]), acc);

			first -= get_lsb(first);
		}
		
		return acc;
	}
	void update(size_type index, const T& value) {
		for(++index; index < data.size(); index += get_lsb(index)) {
			data[index] = CommutativeMonoid::operation(data[index], value);
		}
	}
	void change(size_type index, const T& value) {
		update(index, CommutativeMonoid::operation(CommutativeMonoid::inverse((*this)[index]), value));
	}

	// min{x | f(fold(x)) = true}
	template<class F>
	size_type search(const F & f) {
		if(f(T{})) return 0;

		T acc{};
		size_type i = 0, k = data.size();
		while(k >>= 1) {
			if((i | k) < data.size() and !f(CommutativeMonoid::operation(acc, data[i | k]))) {
				acc = CommutativeMonoid::operation(acc, data[i | k]);
				i |= k;
			}
		}
		return i + 1;
	}

	T operator[](const size_type& k) const { return fold(k, k + 1); };

	bool empty() const { return size() == 0; }
	size_type size() const { return data.size() - 1; }
	void swap(fenwick_tree & r) { data.swap(r.data); }
};

template<class T>
struct monoid {
	using value_type = T;

	static value_type operation(const value_type& a, const value_type& b) { return a + b; };
	static value_type inverse(const value_type& x) { return -x; }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

