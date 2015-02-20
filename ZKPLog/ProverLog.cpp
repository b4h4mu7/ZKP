#include "ProverLog.h"
#include "ProofLog.h"
#include "PrivateKeyLog.h"
#include <crypto++/osrng.h>
#include "ResponseLog.h"

namespace ZKP
{

namespace Log
{

Prover::Prover(const PrivateKey& privateKey) noexcept:
	ZKP::Prover(privateKey),
	m_r([&privateKey]
	{
		CryptoPP::AutoSeededRandomPool rng;
		return CryptoPP::Integer(rng,privateKey.bits());
	}())
{
}

ZKP::Proof* Prover::constructProofHelper(const ZKP::PrivateKey& privateKey) const noexcept
{
	const PrivateKey& p=dynamic_cast<const PrivateKey&>(privateKey);
	return new Proof(a_exp_b_mod_c(p.g(),m_r,p.p()));
}

const ZKP::Response* Prover::left(const ZKP::PrivateKey&) const noexcept
{
	return new Response(m_r);
}

const ZKP::Response* Prover::right(const ZKP::PrivateKey& privateKey) const noexcept
{
	const PrivateKey& k=dynamic_cast<const PrivateKey&>(privateKey);
	return new Response(k.x().Plus(m_r).Modulo(k.p()-1));
}

}

}
