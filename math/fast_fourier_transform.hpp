#ifndef INCLUDED_FAST_FOURIER_TRANSFORM_HPP
#define INCLUDED_FAST_FOURIER_TRANSFORM_HPP

#include "../math/polynomial.hpp"
#include <complex>

template<class T, class Real = double, class Complex = std::complex<Real>>
class fast_fourier_transform: public polynomial<T> {
public:
	using polynomial<T>::polynomial;
	using value_type = typename polynomial<T>::value_type;
	using reference = typename polynomial<T>::reference;
	using const_reference = typename polynomial<T>::const_reference;
	using size_type = typename polynomial<T>::size_type;

private:
	// constexpr Real PI = std::numbers::pi_v<Real>;
	static constexpr Real PI = std::acos(Real(-1));;
	
	void transform(polynomial<Complex>& a, bool inverse = false) {
		size_type n = 0;
		while((1 << n) < a.size()) n++;
		size_type N = 1 << n;
		a.resize(N);

		size_type mask = N - 1;
		polynomial<Complex> tmp(N);
		for(int i = N >> 1; i >= 1; i >>= 1) {
			Real theta = 2 * PI * i * (inverse ? -1 : 1) / N;
			Complex zeta(std::cos(theta), std::sin(theta));
			Complex powZeta(1);

			for(int j = 0; j < N; j += i) {
				for(int k = 0; k < i; k++) {
					tmp[j + k] = a[((j << 1) & mask) | k] + powZeta * a[(((j << 1) | i) & mask) | k];
				}
				powZeta *= zeta;
			}
			a.swap(tmp);
		}

		if(n & 1) {
			std::swap(a, tmp);
			for(int i = 0; i < N; i++) a[i] = tmp[i];
		}
		if(inverse) for(int i = 0; i < N; i++) a[i] /= N;
	}
	fast_fourier_transform convolution(const fast_fourier_transform& ar, const fast_fourier_transform& br) {
		size_type size = ar.degree() + br.degree() + 1;
		polynomial<Complex> a(size);
		for(int i = 0; i < ar.size(); i++) a[i].real(ar[i]);
		for(int i = 0; i < br.size(); i++) a[i].imag(br[i]);
		transform(a, false);
		
		int N = a.size();
		polynomial<Complex> c(N);
		for(int i = 0; i < N; i++) {
			int j = (i == 0 ? 0 : N - i);
			c[i] = (a[i] + conj(a[j])) * (a[i] - conj(a[j])) * Complex(0, -.25);
		}
		transform(c, true);

		fast_fourier_transform ret(size);
		for(int i = 0; i < size; i++) ret[i] = round(c[i].real());
		return ret;
		
	}
public:
	fast_fourier_transform(const polynomial<T>& p): polynomial<T>(p) {}

	fast_fourier_transform operator*(const_reference r) const { return fast_fourier_transform(*this) *= r; }
	fast_fourier_transform& operator*=(const_reference r) {
		for(int i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] * r;
		return *this;
	}
	fast_fourier_transform operator*(const fast_fourier_transform& r) const { return fast_fourier_transform(*this) *= r; }
	fast_fourier_transform& operator*=(const fast_fourier_transform& r) {
		return (*this) = convolution((*this), r);
	}
};

// @docs docs/fast_fourier_transform.md

#endif
