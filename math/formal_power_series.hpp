#pragma once
#ifndef INCLUDED_FORMAL_POWER_SERIES_HPP
#define INCLUDED_FORMAL_POWER_SERIES_HPP

#include <cassert>
#include <utility>

template<class T>
class formal_power_series: public T {
public:
	using T::T;
	using value_type = typename T::value_type;
	using reference = typename T::reference;
	using const_reference = typename T::const_reference;
	using size_type = typename T::size_type;

private:
	formal_power_series(): T(1) {}
	formal_power_series(const T& p): T(p) {}

public:
	formal_power_series inverse() const {
		assert((*this)[0] != value_type{});

		formal_power_series ret(1, (*this)[0].inverse());
		for(int i = 1; i < this->size(); i <<= 1) {
			auto tmp = ret * this->prefix(i << 1);
			for(int j = 0; j < i; j++) {
				tmp[j] = value_type{};
				if(j + i < tmp.size()) tmp[j + i] *= value_type(-1);
			}
			tmp = tmp * ret;
			for(int j = 0; j < i; j++) tmp[j] = ret[j];
			ret = std::move(tmp).prefix(i << 1);
		}
		return ret.prefix(this->size());
	}
};

#endif
