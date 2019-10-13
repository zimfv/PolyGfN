#pragma once

#include <cstdint>
#include <vector>

#include "GF.hpp"

template <uint8_t P>
class Polynom {
	std::vector<GF<P>> coef;

	void fixDeg(void) noexcept; //< Delete highest zeros, if they are.

public:
	Polynom(std::vector<GF<P>>) noexcept;

	Polynom(std::vector<GF<P>>::size_type >) noexcept;

	[[nodiscard]]
	std::vector<GF<P>>::size_type Deg(void) const noexcept;

	Polynom operator+(const Polynom &) noexcept;

	Polynom &operator+=(const Polynom &) noexcept;

	Polynom operator-(const Polynom &) noexcept;

	Polynom &operator-=(const Polynom &) noexcept;

	Polynom operator*(const Polynom &) noexcept;

	Polynom &operator*=(const Polynom &) noexcept;

	Polynom operator*(const GF<P> &) noexcept;

	Polynom &operator*=(const GF<P> &) noexcept;

	Polynom operator/(const Polynom &) noexcept(false);

	Polynom &operator/=(const Polynom &) noexcept(false);

	Polynom operator%(const Polynom&) noexcept;

	Polynom &operator%=(const Polynom&) noexcept;

	GF<P> &operator[](std::vector<GF<P>>::size_type)

	static
	Polynom &GCD(const Polynom&, const Polynom&) noexcept;
};
