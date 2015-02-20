#include "PublicKeyLog.h"
#include <crypto++/nbtheory.h>
#include <crypto++/osrng.h>

namespace ZKP
{

namespace Log
{

PublicKey::PublicKey(const CryptoPP::Integer& g, const CryptoPP::Integer& p, const CryptoPP::Integer& q, const CryptoPP::Integer& y):
	m_g(g),
	m_p(p),
	m_y(y)
{
	CryptoPP::AutoSeededRandomPool rng;
	// The level is set to 2 in VerifyPrime, because anything larger than 1 runs the Rabin-Miller test for 10 rounds
	if(not CryptoPP::VerifyPrime(rng,m_p,2))
	{
		throw std::invalid_argument("p is not prime");
	}
	if(not CryptoPP::VerifyPrime(rng,q,2))
	{
		throw std::invalid_argument("q is not prime");
	}
	if(m_g==CryptoPP::Integer::One())
	{
		throw std::invalid_argument("g is one");
	}
	if(a_exp_b_mod_c(m_g,q,m_p)!=CryptoPP::Integer::One())
	{
		throw std::invalid_argument("g^q is not one");
	}
}

Cloneable* PublicKey::clone() const noexcept
{
	return new PublicKey(*this);
}

const CryptoPP::Integer&PublicKey::g() const noexcept
{
	return m_g;
}

const CryptoPP::Integer&PublicKey::p() const noexcept
{
	return m_p;
}

const CryptoPP::Integer&PublicKey::y() const noexcept
{
	return m_y;
}

}

}
