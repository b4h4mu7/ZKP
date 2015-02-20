#ifndef ZKP_Log_Proof_H
#define ZKP_Log_Proof_H

#include "Proof.h"
#include <crypto++/integer.h>

namespace ZKP
{

namespace Log
{

//! Implementation for the discrete log ZKP.
class Proof:public ZKP::Proof
{
public:
	/*!
	   \brief Ctor.
	   \param c The proof.
	 */
	Proof(const CryptoPP::Integer& c) noexcept;

	Cloneable* clone() const noexcept override;

	//! Getter for C
	const CryptoPP::Integer& C() const noexcept;
private:
	/*!
	   \brief The value revealed to the Verifier.

	   C=g^r mod p.
	 */
	const CryptoPP::Integer m_C;
};

}

}

#endif // ZKP_Log_Proof_H
