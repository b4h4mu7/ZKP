#ifndef ZKP_IterativeVerifier_H
#define ZKP_IterativeVerifier_H

#include <memory>
#include "Verifier.h"

namespace ZKP
{

/*!
   \brief Runs a Verifier iteratively. Iterations are executed sequentially.
 */
class IterativeVerifier
{
public:
	//! Error types emitted by notifyError().
	enum class Error
	{
		//! The response verification failed. It is emited when processResponse() fails to verify the Response.
		VerificationFailed,
		//! An out-of-order message arrived.
		InvalidMessageOrder,
		//! The message is corrupted.
		InvalidMessage
	};

	/*!
	   \brief Ctor specifying the number of rounds to be executed.
	   \param publicKey The PublicKey used for the protocol.
	   \param rounds The number of rounds the protocol is going to be run for.
	 */
	IterativeVerifier(const PublicKey& publicKey, const uint64_t rounds) noexcept;

	virtual ~IterativeVerifier() noexcept = default;

	/*!
	   \brief Start the verifier.

	   Emits notifyNextRound().
	 */
	void start() noexcept;
protected:
	/*!
	   \brief Process a Proof.

	   Emits a notifyChallenge().
	   \param proof The Proof to be processed.
	 */
	void processProof(const Proof& proof) noexcept;

	/*!
	   \brief Process a Response.

	   Verifies the Response. If it is fails, emits a notifyError(). If it succeeds and it is the last round,
	   it emits a notifySuccess(). Otherwise, it emits a notifyProgress() with the number of successful rounds and
	   notifyNextRound() to start the next iteration.
	   \param response The Response to be processed.
	 */
	void processResponse(const Response& response) noexcept;
private:
	virtual void notifyProgress(const uint64_t passed) noexcept = 0;

	virtual void notifyError(const Error error) noexcept = 0;

	virtual void notifyChallenge(const Challenge challenge) noexcept = 0;

	virtual void notifySuccess() noexcept = 0;

	virtual void notifyNextRound() noexcept = 0;

	//! Smart pointer to the current Verifier.
	std::unique_ptr<Verifier> m_verifier;

	/*!
	   \brief Internal helper to construct the concrete Verifier.
	   \param publicKey The PublicKey for the protocol.
	   \param proof The Proof from Prover.
	   \return The Verifier.
	 */
	virtual Verifier* constructVerifier(const PublicKey& publicKey,const Proof& proof) const noexcept = 0;

	//! The number of protocol rounds completed.
	uint64_t m_counter;

	//! The number of rounds to repeat the protocol.
	const uint64_t m_rounds;

	//! The PublicKey for the protocol.
	const PublicKey& m_publicKey;
};

}

#endif // ZKP_IterativeVerifier_H
