#ifndef ZKP_Verifier_H
#define ZKP_Verifier_H

#include "Challenge.h"

namespace ZKP
{

class PublicKey;
class Proof;
class Response;

/*!
   \brief A Verifier receives a Proof from a Prover, issues a Challenge and verifies the Response.
 */
class Verifier
{
public:
	/*!
	   \brief Ctor.
	   \param publicKey The PublicKey used for the verification.
	   \param proof The Proof from Prover.
	 */
	Verifier(const PublicKey& publicKey,const Proof& proof) noexcept;

	virtual ~Verifier() = default;

	//! Getter for the challenge.
	Challenge challenge() const noexcept;

	/*!
	   \brief Verify a Response sent by a Prover.
	   \param response
	   \return Whether the verification succeeded.
	   \throw Exception When challenge() hasn't been invoked.
	 */
	bool verify(const Response& response) const noexcept;
private:
	//! The Proof created by the Prover.
	const Proof& m_proof;

	//! The PublicKey used for the verification.
	const PublicKey& m_publicKey;

	//! The Challenge
	const Challenge m_challenge;

	//! Verification helper method for left challenges
	virtual bool verifyHelperLeft(const PublicKey& pubicKey, const Proof& proof, const Response& response) const noexcept = 0;

	//! Verification helper method for right challenges
	virtual bool verifyHelperRight(const PublicKey& pubicKey, const Proof& proof, const Response& response) const noexcept = 0;
};

}

#endif // ZKP_Verifier_H
