#include <exception>
#include <numeric>

#include "GF.hpp"

template <uint8_t P>
void GF<P>::fix(void) {
	v = val % P;
	v = v >= 0 ? v : P - v;
}

template <uint8_t P>
GF<P>::GF(const int64_t val) noexcept : v(val) {
	if (P == 0) { throw new std::runtime_error("field must have at list one element"); }
	fix();
}

template <uint8_t P>
GF<P> &GF<P>::operator+=(const GF<P> &val) noexcept {
	v += val.v;
	fix();
	return *this;
}

template <uint8_t P>
GF<P> GF<P>::operator+(const GF<P> &val) noexcept {
	return GF<P>(v) += val;
}

template <uint8_t P>
GF<P> &GF<P>::operator-=(const GF<P> &val) noexcept {
	v -= val.v;
	fix();
	return *this;
}

template <uint8_t P>
GF<P> GF<P>::operator-(const GF<P> &val) noexcept {
	return GF<P>(v) -= val;
}

template <uint8_t P>
GF<P> &GF<P>::operator*=(const GF<P> &val) noexcept {
	v *= val.v;
	fix();
	return *this;
}

template <uint8_t P>
GF<P> GF<P>::operator*(const GF<P> &val) noexcept {
	return GF<P>(v) *= val;
}

template <uint8_t P>
GF<P> &GF<P>::MulInv(const GF<P> &val) {
	int64_t a = val.v, b = P, x, y, q, r, x1 = 0, x2 = 1, y1 = 1, y2 = 0;
	while (b > 0) {
		q = a / b, r = a % b;
		x = x2 - q * x1, y = y2 - q * y1;
		a = b, b = r, x2 = x1, x1 = x, y2 = y1, y1 = y;
	}
	if (a != 1) { throw new std::runtime_error("multiplicative inverse not exists"); }
	return new GC<p>(x2);
}

template <uint8_t P>
GF<P> &GF<P>::operator/=(const GF<P> &val) noexcept(false) {
	if (val.v == 0) { throw new std::runtime_error("division by zero"); }
	v *= MulInv(val.v);
	return *this;
}

template <uint8_t P>
GF<P> GF<P>::operator/(const GF<P> &val) noexcept {
	return GF<P>(v) /= val;
}

template <uint8_t P>
bool GF<P>::operator==(const GF<P> &val) const noexcept {
	return v == val.v;
}

template <uint8_t P>
bool GF<P>::operator!=(const GF<P> &val) const noexcept {
	return v != val.v;
}
