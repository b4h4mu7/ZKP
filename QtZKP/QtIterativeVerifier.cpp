#include "QtIterativeVerifier.h"
#include <QMetaType>
#include "Proof.h"
#include "Response.h"

Q_DECLARE_METATYPE(ZKP::Challenge)
Q_DECLARE_METATYPE(ZKP::Proof*)
Q_DECLARE_METATYPE(ZKP::Response*)
Q_DECLARE_METATYPE(ZKP::IterativeVerifier::Error)

namespace ZKP
{

namespace Qt
{

IterativeVerifier::IterativeVerifier(const PublicKey& publicKey, const uint64_t rounds, QObject*const parent) noexcept:
	QObject(parent),
	ZKP::IterativeVerifier(publicKey,rounds)
{
	qRegisterMetaType<ZKP::Challenge>("ZKP::Challenge");
	qRegisterMetaType<const ZKP::Proof*>("const ZKP::Proof*");
	qRegisterMetaType<const ZKP::Response*>("const ZKP::Response*");
	qRegisterMetaType<ZKP::IterativeVerifier::Error>("ZKP::IterativeVerifier::Error");
	qRegisterMetaType<uint64_t>("uint64_t");
}

void IterativeVerifier::processProof(const ZKP::Proof* proof) noexcept
{
	if(not proof)
	{
		emit error(Error::InvalidMessage);
		return;
	}
	ZKP::IterativeVerifier::processProof(*proof);
}

void IterativeVerifier::processResponse(const ZKP::Response* response) noexcept
{
	if(not response)
	{
		emit error(Error::InvalidMessage);
		return;
	}
	ZKP::IterativeVerifier::processResponse(*response);
}

void IterativeVerifier::notifyProgress(const uint64_t passed) noexcept
{
	emit progress(passed);
}

void IterativeVerifier::notifyError(const IterativeVerifier::Error errorV) noexcept
{
	emit error(errorV);
}

void IterativeVerifier::notifyChallenge(const Challenge challengeV) noexcept
{
	emit challenge(challengeV);
}

void IterativeVerifier::notifySuccess() noexcept
{
	emit success();
}

void IterativeVerifier::notifyNextRound() noexcept
{
	emit nextRound();
}

}

}
