#include "IterativeVerifier.h"

namespace ZKP
{

IterativeVerifier::IterativeVerifier(const PublicKey& publicKey,const uint64_t rounds) noexcept:
	m_counter(0),
	m_rounds(rounds),
	m_publicKey(publicKey)
{
}

void IterativeVerifier::processProof(const Proof& proof) noexcept
{
	m_verifier.reset(constructVerifier(m_publicKey,proof));
	notifyChallenge(m_verifier->challenge());
}

void IterativeVerifier::processResponse(const Response& response) noexcept
{
	if(not m_verifier)
	{
		notifyError(Error::InvalidMessageOrder);
		return;
	}
	if(m_verifier->verify(response))
	{
		if(++m_counter==m_rounds)
		{
			notifySuccess();
		}
		else
		{
			notifyProgress(m_counter);
			notifyNextRound();
		}
	}
	else
	{
		notifyError(Error::VerificationFailed);
	}
}

void IterativeVerifier::start() noexcept
{
	notifyNextRound();
}

}
