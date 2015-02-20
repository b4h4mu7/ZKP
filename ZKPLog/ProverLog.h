#ifndef ZKP_Log_Prover_H
#define ZKP_Log_Prover_H

#include "Prover.h"
#include <crypto++/integer.h>

namespace ZKP
{

class PrivateKey;

namespace Log
{

class PrivateKey;

//! Implementation for the discrete log ZKP.
class Prover:public ZKP::Prover
{
public:
	/*!
	   \brief Ctor.
	   \param privateKey See ZKP::Prover::Prover().
	 */
	Prover(const PrivateKey& privateKey) noexcept;
private:
	ZKP::Proof* constructProofHelper(const ZKP::PrivateKey& privateKey) const noexcept override;

	const ZKP::Response* left(const ZKP::PrivateKey&) const noexcept override;

	const ZKP::Response* right(const ZKP::PrivateKey& privateKey) const noexcept override;

	//! The random integer
	const CryptoPP::Integer m_r;
};

}

}

#endif // ZKP_Log_Prover_H
