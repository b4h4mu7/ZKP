#ifndef ZKP_Prover_H
#define ZKP_Prover_H

#include <memory>
#include "Proof.h"
#include "Response.h"
#include "Challenge.h"

namespace ZKP
{

class PrivateKey;

/*!
   \brief Base class for prover implementations.

   Prover generates a Proof and responds to challenges.
 */
class Prover
{
public:
	/*!
	   \brief Ctor.
	   \param privateKey The PrivateKey for the protocol.
	 */
	Prover(const PrivateKey& privateKey) noexcept;

	virtual ~Prover() = default;

	/*!
	   \brief Generate a proof. It must be called before respond().
	   \return A Proof object that is owned by the Prover object.
	 */
	const Proof& constructProof() noexcept;

	/*!
	   \brief Respond to a Challenge based on a generated Proof.
	   \param challenge The Challenge issued by a Verifier.
	   \return The Response to be sent to the Verifier.
	 */
	const Response& respond(const Challenge challenge) noexcept;
private:
	//! Override this method for constructing the concrete Proof.
	virtual Proof* constructProofHelper(const PrivateKey& privateKey) const noexcept = 0;

	//! Abstract method generating a Response for a left Challenge.
	virtual const Response* left(const PrivateKey& privateKey) const noexcept = 0;

	//! Abstract method generating a Response for a Right Challenge.
	virtual const Response* right(const PrivateKey& privateKey) const noexcept = 0;

	//! Smart pointer to the Proof.
	std::unique_ptr<const Proof> m_proof;

	//! Smart pointer to the Response.
	std::unique_ptr<const Response> m_response;

	//! The PrivateKey for the protocol.
	const PrivateKey& m_privateKey;
};

}

#endif // ZKP_Prover_H
