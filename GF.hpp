#pragma once

#include <cstdint>

template <uint8_t P>
class GF {
	int64_t v;

	void fix(void) noexcept;

protected:
	GF<P>& GF<P>::MulInv(const GF<P>&);

public:
	implicit
	GF(int64_t = 0) noexcept(false);

	GF operator+(const GF &) noexcept;

	GF &operator+=(const GF &) noexcept;

	GF operator-(const GF &) noexcept;

	GF &operator-=(const GF &) noexcept;

	GF operator*(const GF &) noexcept;

	GF &operator*=(const GF &) noexcept;

	GF operator/(const GF &) noexcept(false);

	GF &operator/=(const GF &) noexcept;

	bool operator==(const GF &) const noexcept;

	bool operator!=(const GF &) const noexcept;
}
