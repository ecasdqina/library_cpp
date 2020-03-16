#include <cstdint>
#include <cstring>
#include <vector>
#include <algorithm>

template<class T, std::uint_fast32_t K = 20>
class persistent_array {
	using u32 = std::uint_fast32_t;

public:
	using value_type = T;
	using size_type = u32;

private:
	struct node {
		T data;
		node* child[K];

		node() = default;
	};
	using node_ptr = node*;
	std::vector<node_ptr> root;

	node_ptr set(size_type idx, const T&& val, const node_ptr& t) {
		node_ptr ret = new node();
		if(t) {
			std::memcpy(ret->child, t->child, sizeof(t->child));
			ret->data = t->data;
		}

		if(!idx) ret->data = val;
		else ret->child[idx % K] = set(idx / K, std::move(val), ret->child[idx % K]);
		return ret;
	}
	T get(size_type idx, const node_ptr& t) const {
		if(!t) return T{};
		if(idx == 0) return t->data;
		return get(idx / K, t->child[idx % K]);
	}

public:
	persistent_array(persistent_array&&) = default;
	persistent_array(const persistent_array &) = default;

	persistent_array(): root(1, nullptr) {}

	size_type set(size_type idx, const T&& val, int time = -1) {
		if(time == -1) root.push_back(set(idx, std::move(val), root.back()));
		else root.push_back(set(idx, std::move(val), root[time]));
		return root.size() - 1;
	}
	T get(size_type idx, int time = -1) const {
		if(time == -1) return get(idx, root.back());
		return get(idx, root[time]);
	}

	const T operator[](size_type k) const { return get(k); }
	bool empty() const { return (root.size() == 1 and root[0] == nullptr); }
	size_type now() const { return root.size() - 1; }
	void clear() { root.assign(1, nullptr); }
	void swap(const persistent_array& r) { root.swap(r.root); }
};
