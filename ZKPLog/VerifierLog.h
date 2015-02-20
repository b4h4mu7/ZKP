#ifndef ZKP_Log_Verifier_H
#define ZKP_Log_Verifier_H

#include "Verifier.h"

namespace ZKP
{

namespace Log
{

class PublicKey;
class Proof;

//! Implementation for the discrete log ZKP.
class Verifier:public ZKP::Verifier
{
public:
	/*!
	   \brief Ctor.
	   \param publicKey See ZKP::Verifier::Verifier().
	   \param proof See ZKP::Verifier::Verifier().
	 */
	Verifier(const PublicKey& publicKey,const Proof& proof) noexcept;
private:
	bool verifyHelperLeft(const ZKP::PublicKey& publicKey, const ZKP::Proof& proof, const ZKP::Response& response) const noexcept override;

	bool verifyHelperRight(const ZKP::PublicKey& publicKey, const ZKP::Proof& proof, const ZKP::Response& response) const noexcept override;
};

}

}

#endif // ZKP_Log_Verifier_H
