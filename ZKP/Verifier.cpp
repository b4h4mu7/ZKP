#include "Verifier.h"
#include <crypto++/osrng.h>

namespace ZKP
{

Verifier::Verifier(const PublicKey& publicKey,const Proof& proof) noexcept:
	m_proof(proof),
	m_publicKey(publicKey),
	m_challenge([]
	{
		CryptoPP::AutoSeededRandomPool rng;
		return rng.GenerateBit()?Challenge::Left:Challenge::Right;
	}())
{
}

Challenge Verifier::challenge() const noexcept
{
	return m_challenge;
}

bool Verifier::verify(const Response& response) const noexcept
{
	return m_challenge==Challenge::Left?verifyHelperLeft(m_publicKey,m_proof,response):verifyHelperRight(m_publicKey,m_proof,response);
}

}
