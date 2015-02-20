#ifndef ZKP_Log_PrivateKey_H
#define ZKP_Log_PrivateKey_H

#include "PrivateKey.h"
#include <crypto++/integer.h>

namespace ZKP
{

namespace Log
{

//! Implementation for the discrete log ZKP.
class PrivateKey:public ZKP::PrivateKey
{
public:
	/*!
	   \brief Create a PrivateKey with random values and default parameters.

	   The parameter values are delta=1, p bits=2048 and q bits=256.
	 */
	PrivateKey() noexcept;

	/*!
	   \brief Create a PrivateKey with random values and default parameters.

	   Generates a prime of the form p=2*r*q+delta.
	   \param delta
	   \param pbits
	   \param qbits
	 */
	PrivateKey(const int delta,const unsigned int pbits,const unsigned int qbits) noexcept;

	//! Getter for g.
	const CryptoPP::Integer& g() const noexcept;

	//! Getter for p.
	const CryptoPP::Integer& p() const noexcept;

	//! Getter for q.
	const CryptoPP::Integer& q() const noexcept;

	//! Getter for x.
	const CryptoPP::Integer& x() const noexcept;

	//! Getter for the number of prime bits.
	unsigned int bits() const noexcept;
private:
	const ZKP::PublicKey* generatePublicKeyHelper()  const noexcept override;

	//! The number of bits for p.
	const unsigned int m_bits;

	CryptoPP::Integer m_p;

	CryptoPP::Integer m_q;

	CryptoPP::Integer m_g;

	CryptoPP::Integer m_x;
};

}

}

#endif // ZKP_Log_PrivateKey_H
