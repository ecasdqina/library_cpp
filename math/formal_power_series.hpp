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
	formal_power_series log() const {
		assert((*this)[0] == value_type(1));
		
		return (formal_power_series(this->differential()) * this->inverse()).integral().prefix(this->size());
	}
	formal_power_series exp() const {
		assert((*this)[0] == value_type{});

		formal_power_series f(1, value_type(1)), g(1, value_type(1));
		for(int i = 1; i < this->size(); i <<= 1) {
			g = (g * value_type(2) - f * g * g).prefix(i);
			formal_power_series q = this->differential().prefix(i - 1);
			formal_power_series w = (q + g * (f.differential() - f * q)).prefix((i << 1) - 1);
			f = (f + f * (*this - w.integral()).prefix(i << 1)).prefix(i << 1);

		}
		return f.prefix(this->size());
	}
	formal_power_series pow(size_type k) const {
		for(size_type i = 0; i < this->size(); i++) {
			if((*this)[i] != value_type{}) {
				value_type inv = (*this)[i].inverse();
				formal_power_series f(*this * inv);
				formal_power_series g(f >> i);
				g = formal_power_series(g.log() * value_type(k)).exp() * (*this)[i].pow(k);
				if(i * k > this->size()) return formal_power_series(this->size());

				return (g << (i * k)).prefix(this->size());
			}
		}
		return *this;
	}
};

// @docs docs/formal_power_series.md

#endif
