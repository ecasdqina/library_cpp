#ifndef INCLUDED_POLYNOMIAL_HPP
#define INCLUDED_POLYNOMIAL_HPP

#include <cstdint>
#include <functional>
#include <vector>
#include <queue>

namespace cplib {
template<class T>
class polynomial: public std::vector<T> {
public:
	using std::vector<T>::vector;
	using value_type = typename std::vector<T>::value_type;
	using reference = typename std::vector<T>::reference;
	using const_reference = typename std::vector<T>::const_reference;
	using size_type = typename std::vector<T>::size_type;

public:
	polynomial(const std::vector<T>& r): std::vector<T>(r) {}
	polynomial(size_t size, std::function<T(size_t)> f): std::vector<T>(size) {
		for(size_t i = 0; i < size; i++) (*this)[i] = f(i);
	}

	polynomial operator+(const polynomial& r) const { return polynomial(*this) += r; }
	polynomial operator+(const_reference r) const { return polynomial(*this) += r; }
	friend polynomial operator+(const_reference l, polynomial r) { return r += l; }
	polynomial operator-(const polynomial& r) const { return polynomial(*this) -= r; }
	polynomial operator-(const_reference r) const { return polynomial(*this) -= r; }
	friend polynomial operator-(const_reference l, polynomial r) { return r -= l; }
	polynomial operator*(const_reference r) const { return polynomial(*this) *= r; }
	friend polynomial operator*(const_reference l, polynomial r) { return r *= l; }
	polynomial operator*(const polynomial& r) const { return polynomial(*this) *= r; }
	polynomial operator/(const_reference r) const { return polynomial(*this) /= r; }
	polynomial operator<<(size_type r) const { return polynomial(*this) <<= r; }
	polynomial operator>>(size_type r) const { return polynomial(*this) >>= r; }
	polynomial operator-() const {
		polynomial ret(this->size());
		for(size_t i = 0; i < this->size(); i++) ret[i] = -(*this)[i];
		return ret;
	}
	polynomial& operator+=(const polynomial& r) {
		if(r.size() > this->size()) this->resize(r.size());
		for(size_t i = 0; i < r.size(); i++) (*this)[i] = (*this)[i] + r[i];
		return *this;
	}
	polynomial& operator+=(const_reference r) {
		if(this->empty()) this->push_back(T{});
		(*this)[0] += r;
		return *this;
	}
	polynomial& operator-=(const polynomial& r) {
		if(r.size() > this->size()) this->resize(r.size());
		for(size_t i = 0; i < r.size(); i++) (*this)[i] = (*this)[i] - r[i];
		return *this;
	}
	polynomial& operator-=(const_reference r) {
		if(this->empty()) this->push_back(T{});
		(*this)[0] -= r;
		return *this;
	}
	polynomial& operator*=(const_reference r) {
		for(size_t i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] * r;
		return *this;
	}
	polynomial& operator/=(const_reference r) {
		for(size_t i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] / r;
		return *this;
	}
	polynomial& operator<<=(size_type r) {
		this->insert(begin(*this), r, T{});
		return *this;
	}
	polynomial& operator>>=(size_type r) {
		if(r >= this->size()) this->clear();
		else this->erase(begin(*this), begin(*this) + r);
		return *this;
	}
	polynomial& operator*=(const polynomial& r) {
		polynomial ret(this->degree() + r.degree() + 1);
		for(size_t i = 0; i < this->size(); i++) {
			if((*this)[i] == T{}) continue;
			for(size_t j = 0; j < r.size(); j++) ret[i + j] += (*this)[i] * r[j];
		}
		return *this = std::move(ret);
	};

	polynomial differential(size_type k) const {
		polynomial ret(*this);
		for(size_t i = 0; i < k; i++) ret = ret.differential();
		return ret;
	}
	polynomial differential() const {
		if(degree() < 1) return polynomial();
		polynomial ret(this->size() - 1);
		for(size_t i = 1; i < this->size(); i++) ret[i - 1] = (*this)[i] * T(i);
		return ret;
	}
	polynomial integral(size_type k) const {
		polynomial ret(*this);
		for(size_t i = 0; i < k; i++) ret = ret.integral();
		return ret;
	}
	polynomial integral() const {
		polynomial ret(this->size() + 1);
		for(size_t i = 0; i < this->size(); i++) ret[i + 1] = (*this)[i] / T(i + 1);
		return ret;
	}
	polynomial prefix(size_type size) const {
		return polynomial(begin(*this), begin(*this) + std::min(this->size(), size));
	}
	void shrink() {
		while(!this->empty() and this->back() == T{}) this->pop_back();
	}

public:
	polynomial sparse_convex(const polynomial& r) const {
		if(this->nonzeros() < r.nonzeros()) return (*this) * r;
		return r * (*this);
	}
	size_type degree() const { return std::max<size_type>(1, this->size()) - 1; }
	size_type nonzeros() const {
		size_type ret = 0;
		for(size_t i = 0; i < this->size(); i++) {
			if((*this)[i] != T{}) ret++;
		}
		return ret;
	}
	T operator()(T x) const { return eval(x); }
	T eval(T x) const {
		T ret = (*this)[0], tmp = x;
		for(size_t i = 1; i < this->size(); i++) {
			ret = ret + (*this)[i] * tmp;
			tmp = tmp * x;
		}
		return ret;
	}

	static polynomial<T> one() { return term(0); }
	static polynomial<T> zero() { return polynomial<T>({T{0}}); }
	static polynomial<T> term(int k) { return polynomial<T>({T{1}}) << k; }
};

template<class T> T convex_all(std::vector<T> polies, int size = -1) {
	if(polies.empty()) return T::zero();

	std::deque<int> qu;
	for(int i = 0; i < polies.size(); i++) qu.push_back(i);
	while(qu.size() > 1) {
		int a = qu.front(); qu.pop_front();
		int b = qu.front(); qu.pop_front();

		polies.push_back(polies[a] * polies[b]);
		if(size != -1) polies.back().resize(size);
		qu.push_back((int)polies.size() - 1);
	}
	return polies.back();
}
}

#endif
