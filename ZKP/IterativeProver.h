#ifndef ZKP_IterativeProver_H
#define ZKP_IterativeProver_H

#include <memory>
#include "Prover.h"

namespace ZKP
{

class PrivateKey;
class Proof;
class Response;

/*!
   \brief Runs a Prover iteratively. Iterations are executed sequentially.
 */
class IterativeProver
{
public:
	/*!
	   \brief Ctor
	   \param privateKey The PrivateKey for the protocol.
	 */
	IterativeProver(const PrivateKey& privateKey) noexcept;

	virtual ~IterativeProver() noexcept = default;

	//! Error types emitted by notifyError().
	enum class Error
	{
		//! The message arrived out of order.
		InvalidMessageOrder
	};
protected:
	/*!
	   \brief Create a new Prover and issue a Proof.

	   It should precede a processChallenge(). Emits a notifyProof().
	 */
	void processNextRound() noexcept;

	/*!
	   \brief Create a Response to a Challenge.

	   It should follow a processNextRound(). Emits a notifyResponse().
	   \param challenge
	 */
	void processChallenge(const Challenge challenge) noexcept;
private:
	virtual void notifyProof(const Proof& proof) noexcept = 0;

	virtual void notifyError(const Error error) noexcept = 0;

	virtual void notifyResponse(const Response& response) noexcept = 0;

	std::unique_ptr<Prover> m_prover;

	//! Internal helper to construct the concrete Prover.
	virtual Prover* constructProver(const PrivateKey& privateKey) noexcept = 0;

	//! The PrivateKey for the protocol.
	const PrivateKey& m_privateKey;
};

}

#endif // ZKP_IterativeProver_H
