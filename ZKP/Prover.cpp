#include "Prover.h"

namespace ZKP
{

Prover::Prover(const PrivateKey& privateKey) noexcept:
	m_privateKey(privateKey)
{
}

const Proof& Prover::constructProof() noexcept
{
	m_proof.reset(constructProofHelper(m_privateKey));
	return *m_proof;
}

const Response& Prover::respond(const Challenge challenge) noexcept
{
	m_response.reset(challenge==Challenge::Left?left(m_privateKey):right(m_privateKey));
	return *m_response;
}

}
