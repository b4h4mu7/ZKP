#include "VerifierDummy.h"
#include "ResponseDummy.h"
#include "PublicKeyDummy.h"
#include "ProofDummy.h"

namespace ZKP
{

namespace Dummy
{

Verifier::Verifier(const PublicKey& publicKey, const Proof& proof) noexcept:
	ZKP::Verifier(publicKey,proof)
{

}

bool Verifier::verifyHelperLeft(const ZKP::PublicKey&, const ZKP::Proof&, const ZKP::Response& response) const noexcept
{
	const Response& dummyResponse=dynamic_cast<const Response&>(response);
	return dummyResponse.value();
}

bool Verifier::verifyHelperRight(const ZKP::PublicKey&, const ZKP::Proof&, const ZKP::Response& response) const noexcept
{
	const Response& dummyResponse=dynamic_cast<const Response&>(response);
	return not dummyResponse.value();
}

}

}
