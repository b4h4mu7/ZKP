#ifndef ZKP_Qt_IterativeVerifier_H
#define ZKP_Qt_IterativeVerifier_H

#include "IterativeVerifier.h"
#include <QObject>

namespace ZKP
{

namespace Qt
{

/*!
   \brief Qt transport implementation for IterativeVerifier.

   Emited structures are owned internally by the object (challenge()). Structures that are passed to the slots are owned by
   the caller (processProof() and processResponse()).
 */
class IterativeVerifier:public QObject,public ZKP::IterativeVerifier
{
	Q_OBJECT
public:
	/*!
	   \brief Ctor specifying the number of rounds to be executed.
	   \param publicKey The PublicKey used for the protocol.
	   \param rounds The number of rounds the protocol is going to be run for.
	   \param parent The QObject parent.
	 */
	IterativeVerifier(const PublicKey& publicKey, const uint64_t rounds,QObject*const parent=nullptr) noexcept;
signals:
	/*!
	   \brief A round has been completed, but not all the rounds have.
	   \param passed The number of rounds completed.
	 */
	void progress(const uint64_t passed);

	//! An error has occured. See IterativeVerifier::Error for the meaning of each value.
	void error(const ZKP::IterativeVerifier::Error errorV);

	//! A Challenge is ready.
	void challenge(const ZKP::Challenge challengeV);

	//! All rounds are complete.
	void success();

	//! Emited when a new round can start.
	void nextRound();
public slots:
	/*!
	   \brief Receive a Proof and issue a Challenge.

	   Emits challenge().
	 */
	void processProof(const ZKP::Proof* proof) noexcept;

	/*!
	   \brief Receive a Response and verify it.

	   Emits progress() and nextRound() if the verification succeeded, but not all iterations. Emits success() when the
	   verification succeeds and all iterations are done. Emits error() when the verification fails.
	 */
	void processResponse(const ZKP::Response* response) noexcept;
private:
	void notifyProgress(const uint64_t passed) noexcept override final;

	void notifyError(const IterativeVerifier::Error errorV) noexcept override final;

	void notifyChallenge(const Challenge challengeV) noexcept override final;

	void notifySuccess() noexcept override final;

	void notifyNextRound() noexcept override final;
};

}

}

#endif // ZKP_Qt_IterativeVerifier_H
