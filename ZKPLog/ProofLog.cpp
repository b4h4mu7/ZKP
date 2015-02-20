#include "ProofLog.h"

namespace ZKP
{

namespace Log
{

Proof::Proof(const CryptoPP::Integer& c) noexcept:
	m_C(c)
{
}

Cloneable* Proof::clone() const noexcept
{
	return new Proof(*this);
}

const CryptoPP::Integer& Proof::C() const noexcept
{
	return m_C;
}

}

}
