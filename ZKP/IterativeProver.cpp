#include "IterativeProver.h"

namespace ZKP
{

IterativeProver::IterativeProver(const PrivateKey& privateKey) noexcept:
	m_privateKey(privateKey)
{
}

void IterativeProver::processNextRound() noexcept
{
	m_prover.reset(constructProver(m_privateKey));
	notifyProof(m_prover->constructProof());
}

void IterativeProver::processChallenge(const Challenge challenge) noexcept
{
	if(not m_prover)
	{
		notifyError(Error::InvalidMessageOrder);
		return;
	}
	notifyResponse(m_prover->respond(challenge));
}

}
