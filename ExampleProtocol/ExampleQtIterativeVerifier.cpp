#include "ExampleQtIterativeVerifier.h"
#include "VerifierLog.h"
#include "PublicKeyLog.h"
#include "ProofLog.h"

namespace ZKP
{

namespace Qt
{

namespace Example
{

IterativeVerifier::IterativeVerifier(const PublicKey& publicKey, const uint64_t rounds,QObject*const parent) noexcept:
	ZKP::Qt::IterativeVerifier(publicKey,rounds,parent)
{
}

Verifier* IterativeVerifier::constructVerifier(const PublicKey& publicKey, const Proof& proof) const noexcept
{
	return new Log::Verifier(dynamic_cast<const Log::PublicKey&>(publicKey),dynamic_cast<const Log::Proof&>(proof));
}

}

}

}
