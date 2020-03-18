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
