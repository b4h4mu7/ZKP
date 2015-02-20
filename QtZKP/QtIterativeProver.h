#ifndef ZKP_Qt_IterativeProver_H
#define ZKP_Qt_IterativeProver_H

#include "IterativeProver.h"
#include <QObject>

namespace ZKP
{

namespace Qt
{

/*!
   \brief Qt transport implementation for IterativeProver.

   Emited structures are owned internally by the object (proof() and response()). Structures that are passed to the
   slots are owned by the caller (processChallenge()).
 */
class IterativeProver:public QObject,public ZKP::IterativeProver
{
	Q_OBJECT
public:
	/*!
	   \brief Ctor.
	   \param privateKey The PrivateKey for the protocol.
	   \param parent The QObject parent.
	 */
	explicit IterativeProver(const PrivateKey& privateKey, QObject*const parent=nullptr) noexcept;
signals:
	//! A Proof is ready.
	void proof(const ZKP::Proof* proof);

	//! An error has occured.
	void error(const ZKP::IterativeProver::Error error);

	//! A Response is ready.
	void response(const ZKP::Response* response);
public slots:
	//! Start a new round for the IterativeProver.
	void processNextRound() noexcept;

	//! The IterativeProver creates a challenge.
	void processChallenge(const ZKP::Challenge challenge) noexcept;
private:
	void notifyProof(const Proof& proofV) noexcept override final;

	void notifyError(const Error errorV) noexcept override final;

	void notifyResponse(const Response& responseV) noexcept override final;
};

}

}

#endif // ZKP_Qt_IterativeProver_H
