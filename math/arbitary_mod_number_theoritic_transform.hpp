#pragma once
#ifndef INCLUDED_ARBITARY_MOD_NUMBER_THEORITIC_TRANSFORM_HPP
#define INCLUDED_ARBITARY_MOD_NUMBER_THEORITIC_TRANSFORM_HPP

#include "../math/modint.hpp"
#include "../math/polynomial.hpp"
#include "../math/number_theoritic_transform.hpp"

namespace amnttlib {
	using u64 = std::uint_fast64_t;

	// https://lumakernel.github.io/ecasdqina/math/FFT/NTT
	constexpr u64 ntt_primes[][2] = {
		{1224736769, 3}, // 2^24 * 73 + 1,
		{1053818881, 7}, // 2^20 * 3 * 5 * 67 + 1
		{1051721729, 6}, // 2^20 * 17 * 59 + 1
		{1045430273, 3}, // 2^20 * 997 + 1
		{1012924417, 5}, // 2^21 * 3 * 7 * 23 + 1
		{1007681537, 3}, // 2^20 * 31^2 + 1
		{1004535809, 3}, // 2^21 * 479 + 1
		{998244353, 3},  // 2^23 * 7 * 17 + 1
		{985661441, 3},  // 2^22 * 5 * 47 + 1
		{976224257, 3},  // 2^20 * 7^2 * 19 + 1
		{975175681, 17}, // 2^21 * 3 * 5 * 31 + 1
		{962592769, 7},  // 2^21 * 3^3 * 17 + 1
		{950009857, 7},  // 2^21 * 4 * 151 + 1
		{943718401, 7},  // 2^22 * 3^2 * 5^2 + 1
		{935329793, 3},  // 2^22 * 223 + 1
		{924844033, 5},  // 2^21 * 3^2 * 7^2 + 1
		{469762049, 3},  // 2^26 * 7 + 1
		{167772161, 3},  // 2^25 * 5 + 1
	};
};

template<class T,
	amnttlib::u64 MOD_1 = amnttlib::ntt_primes[0][0],
	amnttlib::u64 PRR_1 = amnttlib::ntt_primes[0][1],
	amnttlib::u64 MOD_2 = amnttlib::ntt_primes[2][0],
	amnttlib::u64 PRR_2 = amnttlib::ntt_primes[2][1],
	amnttlib::u64 MOD_3 = amnttlib::ntt_primes[3][0],
	amnttlib::u64 PRR_3 = amnttlib::ntt_primes[3][1]
> class arbitary_mod_number_theoritic_transform: public polynomial<T> {
public:
	using polynomial<T>::polynomial;
	using value_type = typename polynomial<T>::value_type;
	using reference = typename polynomial<T>::reference;
	using const_reference = typename polynomial<T>::const_reference;
	using size_type = typename polynomial<T>::size_type;

	using amntt = arbitary_mod_number_theoritic_transform;
	using m1 = modint<MOD_1>;
	using m2 = modint<MOD_2>;
	using m3 = modint<MOD_3>;

private:
	amntt convolution(const amntt& ar, const amntt& br) {
		number_theoritic_transform<m1, PRR_1> ntt1_a(ar.size()), ntt1_b(br.size());
		number_theoritic_transform<m2, PRR_2> ntt2_a(ar.size()), ntt2_b(br.size());
		number_theoritic_transform<m3, PRR_3> ntt3_a(ar.size()), ntt3_b(br.size());
		for(int i = 0; i < ar.size(); i++) {
			ntt1_a[i] = m1(ar[i].value());
			ntt2_a[i] = m2(ar[i].value());
			ntt3_a[i] = m3(ar[i].value());
		}
		for(int i = 0; i < br.size(); i++) {
			ntt1_b[i] = m1(br[i].value());
			ntt2_b[i] = m2(br[i].value());
			ntt3_b[i] = m3(br[i].value());
		}
		auto x = ntt1_a * ntt1_b;
		auto y = ntt2_a * ntt2_b;
		auto z = ntt3_a * ntt3_b;

		amntt ret(x.size());
		const m2 m1_inv_m2 = m2(MOD_1).inverse();
		const m3 m12_inv_m3 = (m3(MOD_1) * m3(MOD_2)).inverse();
		const T m12 = T(MOD_1) * T(MOD_2);
		for(int i = 0; i < ret.size(); i++) {
			m2 v1 = (m2(y[i].value()) - m2(x[i].value())) * m1_inv_m2;
			m3 v2 = (m3(z[i].value()) - (m3(x[i].value()) + m3(MOD_1) * m3(v1.value()))) * m12_inv_m3;
			ret[i] = (T(x[i].value()) + T(MOD_1) * T(v1.value()) + m12 * T(v2.value()));
		}
		ret.resize(ar.degree() + br.degree() + 1);
		return ret;
	}
	
public:
	arbitary_mod_number_theoritic_transform(const polynomial<T>& p): polynomial<T>(p) {}


	amntt operator*(const_reference r) const { return amntt(*this) *= r; }
	amntt& operator*=(const_reference r) {
		for(int i = 0; i < this->size(); i++) (*this)[i] = (*this)[i] * r;
		return *this;
	}
	amntt operator*(const amntt& r) const { return amntt(*this) *= r; }
	amntt& operator*=(const amntt& r) {
		return (*this) = convolution((*this), r);
	}
};

#endif
