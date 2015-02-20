#include "PrivateKeyLog.h"
#include <crypto++/osrng.h>
#include <crypto++/nbtheory.h>
#include "PublicKeyLog.h"

namespace ZKP
{

namespace Log
{

PrivateKey::PrivateKey(const int delta,const unsigned int pbits,const unsigned int qbits) noexcept:
	m_bits(pbits)
{
	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::PrimeAndGenerator generator(delta,rng,pbits,qbits);
	m_p=generator.Prime();
	m_q=generator.SubPrime();
	m_g=generator.Generator();
	m_x.Randomize(rng,0,m_p.Minus(CryptoPP::Integer::One()));
}

const CryptoPP::Integer&PrivateKey::g() const noexcept
{
	return m_g;
}

const CryptoPP::Integer&PrivateKey::p() const noexcept
{
	return m_p;
}

const CryptoPP::Integer&PrivateKey::q() const noexcept
{
	return m_q;
}

const CryptoPP::Integer&PrivateKey::x() const noexcept
{
	return m_x;
}

unsigned int PrivateKey::bits() const noexcept
{
	return m_bits;
}

PrivateKey::PrivateKey() noexcept:
	PrivateKey(1,2048,256)
{
}

const ZKP::PublicKey* PrivateKey::generatePublicKeyHelper() const noexcept
{
	return new PublicKey(m_g,m_p,m_q,a_exp_b_mod_c(m_g,m_x,m_p));
}

}

}
