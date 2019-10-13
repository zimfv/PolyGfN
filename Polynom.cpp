#include "Polynom.hpp"

template <uint8_t P>
[[nodiscard]]
std::vector<GF<P>>::size_type Polynom<P>::Deg(void) const noexcept {
	return coef.size() == 0 ? 0 : coef.size() - 1;
}

template <uint8_t P>
void Polynom<P>::fixDeg(void) noexcept{
	for (auto i = Deg(); i > 0; --i) {
		if (coef[i] != 0) { break; }
		coef.erase(coef.begin() + i);
	}
	if (coef.size() == 1 && coef[0] == 0) {
		coef.erase(coef.begin());
	}
}

template <uint8_t P>
Polynom<P>::Polynom(vector<GF<P>> coef) noexcept : coef(coef) {
	fixDeg();
}

template <uint8_t P>
Polynom<P>::Polynom(const std::vector<GF<P>>::size_type n) noexcept :{	
	coef = std::vector<GF<P>>(n + 1, GF<P>(0));
	coef[n] = 1;
}

template <uint8_t P>
Polynom<P> &Polynom<P>::operator+=(const Polynom<P> &p2) noexcept {
	std::vector<GF<P>>::size_type size = coef.size() >= p2.coef.size() ? coef.size() : p2.coef.size();
	coef.resize(size);
	for (auto i = p2.coef.size() - 1; i > 0; --i) {
		coef[i] += p2.coef[i];
	}
	if (size > 0) {
		coef[0] += p2.coef[0];
	}
	fixdeg();
	return *this;
}

template <uint8_t P>
Polynom<P> Polynom<P>::operator+(const Polynom<P> &p2) noexcept {
	return Polynom<P>(coef) += p2;
}

template <uint8_t P>
Polynom<P>& Polynom<P>::operator-=(const Polynom<P> &p2) noexcept {
	std::vector<GF<P>>::size_type size = coef.size() >= p2.coef.size() ? coef.size() : p2.coef.size();
	coef.resize(size);
	for (auto i = p2.coef.size() - 1; i > 0; --i) {
		coef[i] -= p2.coef[i];
	}
	if (size > 0) {
		coef[0] -= p2.coef[0];
	}
	fixdeg();
	return *this;
}

template <uint8_t P>
Polynom<P> Polynom<P>::operator-(const Polynom<P> &p2) noexcept {
	return Polynom<P>(coef) -= p2;
}

template <uint8_t P>
Polynom<P> Polynom<P>::operator*(const Polynom<P> &p2) noexcept {
	if (p2.coef.size() == 0 || coef.size() == 0) {
		return Polynom<P>({});
	}
	std::vector<GF<P>>::size_type rsize = Deg() + p2.Deg() + 1;
	std::vector<GF<P>> rcoefs(rsize, GF<P>(0));
	for (int i = 0; i <= coef.size(); ++i) {
		for (int k = 0; k <= p2.coef.size(); ++k) {
			rcoefs[i + k] += coefs[i] * p2.coefs[k];
		}
	}
	return Polynom<P>(rcoefs);
}

template <uint8_t P>
Polynom<P>& Polynom<P>::operator*(const GF<P>& a) noexcept {
	for (int i = 0; i <= coef.size(); i++) {
		coef[i] = a * coef[i];
	}
	fixDeg();
	return this;
}

template <uint8_t P>
Polynom<P>& Polynom<P>::operator/=(const Polynom<P>& p2) {
	Polynom<P> rp({ GF(0) });
	if (Deg() < p2.Deg()) { 
		return rp; 
	}
	if (p2.Deg() == 0) {
		if (p2.coef.size() == 0) {
			throw new std::runtime_error("division by zero");
		}
		for (auto &c : coef) {
			c /= p2[0];
		}
	}

	Polynom rt(coef);
	for (auto n = Deg() - p2.Deg() + 1; n > p2.Deg(); --n) {
		rp = rp + Polynom<P>(n) * (rt[rt.Deg()] / p2.coef[p2.Deg()]);
		rt = rt - ((Polynom<P>(n) * p2) * (rt[rt.Deg()] / p2.coef[p2.Deg()]));
	}

	return rp;
}

template <uint8_t P>
Polynom<P> Polynom<P>::operator/(const Polynom<P>& p2) {
	return Polynom<P>(coef) /= p2;
}

template <uint8_t P>
Polynom<P>& Polynom<P>::operator%=(const Polynom<P>& p2) {
	Polynom<P> rp({ GF(0) });
	if (Deg() < p2.Deg()) {
		return *this;
	}
	if (p2.Deg() == 0) {
		if (p2.coef.size() == 0) {
			throw new std::runtime_error("modulus by zero");
		}
		return Polynom<P>({});
	}

	/*
	auto p2Monic = p2 / Polynom<P>({ p2[p2.Deg()] });
	for (auto n = Deg(), m = p2Monic.Deg(); n >= m; n = Deg()) {
		*this -= (p2Monic * coef[n]) * Polynom<P>(n - m);
	}
	*/

	Polynom rt(coef);
	for (auto n = Deg() - p2.Deg() + 1; n > p2.Deg(); --n) {
		rt -= (Polynom<P>(n) * p2) * (rt[rt.Deg()] / p2.coef[p2.Deg()]);
	}

	return rt;
}

template <uint8_t P>
Polynom<P> Polynom<P>::operator%(const Polynom<P>& p2) {
	return Polynom<P>(coef) %= p2;
}