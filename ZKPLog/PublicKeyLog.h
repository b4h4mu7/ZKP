#ifndef ZKP_Log_PublicKey_H
#define ZKP_Log_PublicKey_H

#include "PublicKey.h"
#include <crypto++/integer.h>

namespace ZKP
{

namespace Log
{

//! Implementation for the discrete log ZKP.
class PublicKey:public ZKP::PublicKey
{
public:
	/*!
	   \brief Ctor.

	   The public key is such that y=g^x mod p.
	   \param g
	   \param p
	   \param q
	   \param y
	   \throw std::invalid_argument If the parameters don't pass the security check.
	 */
	explicit PublicKey(const CryptoPP::Integer& g, const CryptoPP::Integer& p, const CryptoPP::Integer& q, const CryptoPP::Integer& y);

	ZKP::Cloneable* clone() const noexcept override;

	//! Getter for g.
	const CryptoPP::Integer& g() const noexcept;

	//! Getter for p.
	const CryptoPP::Integer& p() const noexcept;

	//! Getter for y.
	const CryptoPP::Integer& y() const noexcept;
private:
	const CryptoPP::Integer m_g;

	const CryptoPP::Integer m_p;

	const CryptoPP::Integer m_y;
};

}

}

#endif // PUBLICKEYLOG_H
