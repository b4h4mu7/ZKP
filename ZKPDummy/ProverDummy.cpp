#include "ProverDummy.h"
#include "ProofDummy.h"
#include "ResponseDummy.h"
#include "PrivateKeyDummy.h"

namespace ZKP
{

namespace Dummy
{

Prover::Prover(const PrivateKey& privateKey) noexcept:
	ZKP::Prover(privateKey)
{

}

ZKP::Proof* Prover::constructProofHelper(const ZKP::PrivateKey&) const noexcept
{
	return new Proof;
}

const ZKP::Response* Prover::left(const ZKP::PrivateKey&) const noexcept
{
	return new Response(true);
}

const ZKP::Response* Prover::right(const ZKP::PrivateKey&) const noexcept
{
	return new Response(false);
}

}

}
