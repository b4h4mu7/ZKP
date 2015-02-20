#include "QtIterativeProver.h"
#include <QMetaType>
#include "Proof.h"
#include "Response.h"

Q_DECLARE_METATYPE(ZKP::Challenge)
Q_DECLARE_METATYPE(ZKP::Proof*)
Q_DECLARE_METATYPE(ZKP::Response*)
Q_DECLARE_METATYPE(ZKP::IterativeProver::Error)

namespace ZKP
{

namespace Qt
{

IterativeProver::IterativeProver(const PrivateKey& privateKey, QObject*const parent) noexcept:
	QObject(parent),
	ZKP::IterativeProver(privateKey)
{
	qRegisterMetaType<ZKP::Challenge>("ZKP::Challenge");
	qRegisterMetaType<const ZKP::Proof*>("const ZKP::Proof*");
	qRegisterMetaType<const ZKP::Response*>("const ZKP::Response*");
	qRegisterMetaType<ZKP::IterativeProver::Error>("ZKP::IterativeProver::Error");
}

void IterativeProver::processNextRound() noexcept
{
	ZKP::IterativeProver::processNextRound();
}

void IterativeProver::processChallenge(const ZKP::Challenge challenge) noexcept
{
	ZKP::IterativeProver::processChallenge(challenge);
}

void IterativeProver::notifyProof(const Proof& proofV) noexcept
{
	emit proof(&proofV);
}

void IterativeProver::notifyError(const Error errorV) noexcept
{
	emit error(errorV);
}

void IterativeProver::notifyResponse(const Response& responseV) noexcept
{
	emit response(&responseV);
}

}

}
