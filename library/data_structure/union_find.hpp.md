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


# :heavy_check_mark: data_structure/union_find.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/union_find.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-19 17:03:37+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/yosupo/unionfind.union_find.test.cpp.html">test/yosupo/unionfind.union_find.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef INCLUDED_UNION_FIND_HPP
#define INCLUDED_UNION_FIND_HPP

#include <cstdint>
#include <vector>

class union_find {
public:
	using size_type = std::int_fast32_t;
	using container = std::vector<size_type>;
	
	container data;
	size_type comp_cnt;

private:
	const size_type find(size_type k) {
		if(data[k] < 0) return k;
		return data[k] = find(data[k]);
	}

public:
	union_find() = default;
	union_find(const union_find &) = default;
	union_find(union_find&&) = default;

	union_find & operator=(const union_find &) = default;
	union_find & operator=(union_find &&) = default;

	union_find(size_type N): data(N, -1), comp_cnt(N) {}

	bool unite(size_type x, size_type y) {
		x = find(x); y = find(y);
		if(x == y) return false;
		if(data[x] > data[y]) std::swap(x, y);
		
		data[x] += data[y];
		data[y] = x;
		comp_cnt--;
		return true;
	}
	
	bool is_united(size_type x, size_type y) { return find(x) == find(y); }
	size_type size() const { return data.size(); }
	size_type size(size_type k) { return -data[find(k)]; }
	size_type comp(size_type k) { return find(k); };
	size_type count() const { return comp_cnt; }
	size_type operator[](size_type k) { return find(k); }
	
	void swap(union_find & r) {
		data.swap(r.data);
		std::swap(comp_cnt, r.comp_cnt);
	}
};

#endif

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/union_find.hpp"



#include <cstdint>
#include <vector>

class union_find {
public:
	using size_type = std::int_fast32_t;
	using container = std::vector<size_type>;
	
	container data;
	size_type comp_cnt;

private:
	const size_type find(size_type k) {
		if(data[k] < 0) return k;
		return data[k] = find(data[k]);
	}

public:
	union_find() = default;
	union_find(const union_find &) = default;
	union_find(union_find&&) = default;

	union_find & operator=(const union_find &) = default;
	union_find & operator=(union_find &&) = default;

	union_find(size_type N): data(N, -1), comp_cnt(N) {}

	bool unite(size_type x, size_type y) {
		x = find(x); y = find(y);
		if(x == y) return false;
		if(data[x] > data[y]) std::swap(x, y);
		
		data[x] += data[y];
		data[y] = x;
		comp_cnt--;
		return true;
	}
	
	bool is_united(size_type x, size_type y) { return find(x) == find(y); }
	size_type size() const { return data.size(); }
	size_type size(size_type k) { return -data[find(k)]; }
	size_type comp(size_type k) { return find(k); };
	size_type count() const { return comp_cnt; }
	size_type operator[](size_type k) { return find(k); }
	
	void swap(union_find & r) {
		data.swap(r.data);
		std::swap(comp_cnt, r.comp_cnt);
	}
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

