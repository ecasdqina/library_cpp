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


# :heavy_check_mark: data_structure/segment_tree.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/segment_tree.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-09 09:19:19+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/yosupo/point_add_range_sum.segment_tree.test.cpp.html">test/yosupo/point_add_range_sum.segment_tree.test.cpp</a>
* :x: <a href="../../verify/test/yosupo/staticrmq.segment_tree.test.cpp.html">test/yosupo/staticrmq.segment_tree.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/segment_tree.hpp"
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
