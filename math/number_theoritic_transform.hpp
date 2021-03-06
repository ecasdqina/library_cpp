#ifndef INCLUDED_NUMBER_THEORITIC_TRANSFORM_HPP
#define INCLUDED_NUMBER_THEORITIC_TRANSFORM_HPP

#include <queue>
#include "../math/modint.hpp"
#include "../math/polynomial.hpp"

namespace cplib {
template<std::uint_fast64_t MOD,
	int primitive_root = 3,
	class T = modint<MOD>>
class number_theoritic_transform: public polynomial<T> {
public:
	using polynomial<T>::polynomial;
	using value_type 	  = typename polynomial<T>::value_type;
	using reference 	  = typename polynomial<T>::reference;
	using const_reference = typename polynomial<T>::const_reference;
	using size_type 	  = typename polynomial<T>::size_type;

public:
	number_theoritic_transform(const polynomial<T>& p): polynomial<T>(p) {}

protected:
	static void ntt(number_theoritic_transform& a) {
		size_t N = a.size();
		static std::vector<T> dw;
		if(dw.size() < N) {
			int n = dw.size();
			dw.resize(N);
			for(size_t i = n; i < N; i++) dw[i] = -(T(primitive_root) ^ ((T::mod - 1) >> (i + 2)));
		}

		for(size_t m = N; m >>= 1;) {
			T w = 1;
			for(size_t s = 0, k = 0; s < N; s += 2 * m) {
				for(size_t i = s, j = s + m; i < s + m; i++, j++) {
					T x = a[i], y = a[j] * w;
					a[i] = x + y;
					a[j] = x - y;
				}
				w *= dw[__builtin_ctz(++k)];
			}
		}
	}
	static void intt(number_theoritic_transform& a) {
		size_t N = a.size();
		static std::vector<T> idw;
		if(idw.size() < N) {
			size_t n = idw.size();
			idw.resize(N);
			for(size_t i = n; i < N; i++) idw[i] = (-(T(primitive_root) ^ ((T::mod - 1) >> (i + 2)))).inverse();
		}

		for(size_t m = 1; m < N; m *= 2) {
			T w = 1;
			for(size_t s = 0, k = 0; s < N; s += 2 * m) {
				for(size_t i = s, j = s + m; i < s + m; i++, j++) {
					T x = a[i], y = a[j];
					a[i] = x + y;
					a[j] = (x - y) * w;
				}
				w *= idw[__builtin_ctz(++k)];
			}
		}
	}
	static void transform(number_theoritic_transform& a, bool inverse = false) {
		size_type n = 0;
		while((1ul << n) < a.size()) n++;
		size_type N = 1 << n;
		a.resize(N);

		if(!inverse) {
			ntt(a);
		} else {
			intt(a);
			T inv = T(N).inverse();
			for(size_t i = 0; i < a.size(); i++) a[i] *= inv;
		}
	}

	static number_theoritic_transform convolution(const number_theoritic_transform& ar, const number_theoritic_transform& br) {
		size_type size = ar.degree() + br.degree() + 1;
		number_theoritic_transform a(ar), b(br);
		a.resize(size);
		b.resize(size);

		transform(a, false);
		transform(b, false);

		for(size_t i = 0; i < a.size(); i++) a[i] *= b[i];
		transform(a, true);
		a.resize(size);
		return a;
	}

public:
	number_theoritic_transform convex(const number_theoritic_transform& r) const { return (*this) * r; }
	number_theoritic_transform operator*(const number_theoritic_transform& r) const { return number_theoritic_transform(*this) *= r; }
	number_theoritic_transform& operator*=(const number_theoritic_transform& r) {
		return (*this) = convolution((*this), r);
	}
	number_theoritic_transform operator*(const_reference r) const { return number_theoritic_transform(*this) *= r; }
	number_theoritic_transform& operator*=(const_reference r) {
		for(size_t i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] * r;
		return *this;
	}

};
}
// @docs docs/number_theoritic_transform.md

#endif
