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
