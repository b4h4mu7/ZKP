#ifndef ZKP_ExampleProtocol_H
#define ZKP_ExampleProtocol_H

#include <QObject>
#include "PrivateKeyLog.h"
#include "IterativeProver.h"
#include "IterativeVerifier.h"

namespace ZKP
{

namespace Qt
{

namespace Example
{

class IterativeProver;
class IterativeVerifier;

}

}

namespace Example
{

class Protocol:public QObject
{
	Q_OBJECT
public:
	explicit Protocol(const uint64_t numberOfRounds,QObject*const parent=nullptr);
signals:
	void finished();
public slots:
	void run() noexcept;
private:
	const ZKP::Log::PrivateKey m_privateKey;
	Qt::Example::IterativeProver*const m_prover;
	Qt::Example::IterativeVerifier*const m_verifier;
	inline void connect() noexcept;
	void inline error(const std::string& errorString) noexcept;
	const uint64_t m_numberOfRounds;
	static std::string toString(const ZKP::IterativeProver::Error errorV) noexcept;
	static std::string toString(const ZKP::IterativeVerifier::Error errorV) noexcept;
private slots:
	void done() noexcept;
	void error(const ZKP::IterativeProver::Error errorV) noexcept;
	void error(const ZKP::IterativeVerifier::Error errorV) noexcept;
	void progress(const uint64_t round) const noexcept;
};

}

}

#endif // ZKP_ExampleProtocol_H
