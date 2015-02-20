#include "VerifierLog.h"
#include "PublicKeyLog.h"
#include "ProofLog.h"
#include "ResponseLog.h"

namespace ZKP
{

namespace Log
{

Verifier::Verifier(const PublicKey& publicKey,const Proof& proof) noexcept:
	ZKP::Verifier(publicKey,proof)
{
}

bool Verifier::verifyHelperLeft(const ZKP::PublicKey& publicKey, const ZKP::Proof& proof,const ZKP::Response& response) const noexcept
{
	const PublicKey& key=dynamic_cast<const PublicKey&>(publicKey);
	const CryptoPP::Integer& modulo=key.p();
	const CryptoPP::Integer leftSide=a_exp_b_mod_c(key.g(),dynamic_cast<const Response&>(response).integer(),modulo);
	const CryptoPP::Integer& C=dynamic_cast<const Proof&>(proof).C();
	const CryptoPP::Integer rightSide=C;
	return leftSide==rightSide;
}

bool Verifier::verifyHelperRight(const ZKP::PublicKey& publicKey, const ZKP::Proof& proof, const ZKP::Response& response) const noexcept
{
	const PublicKey& key=dynamic_cast<const PublicKey&>(publicKey);
	const CryptoPP::Integer& modulo=key.p();
	const CryptoPP::Integer leftSide=a_exp_b_mod_c(key.g(),dynamic_cast<const Response&>(response).integer(),modulo);
	const CryptoPP::Integer& C=dynamic_cast<const Proof&>(proof).C();
	const CryptoPP::Integer rightSide=C.Times(key.y()).Modulo(modulo);
	return leftSide==rightSide;
}

}

}
