#include "ExampleProtocol.h"
#include "ExampleQtIterativeProver.h"
#include "ExampleQtIterativeVerifier.h"
#include <iostream>

namespace ZKP
{

namespace Example
{

Protocol::Protocol(const uint64_t numberOfRounds,QObject* const parent):
	QObject(parent),
	m_prover(new Qt::Example::IterativeProver(m_privateKey,this)),
	m_verifier(new Qt::Example::IterativeVerifier(m_privateKey.publicKey(),numberOfRounds,this)),
	m_numberOfRounds(numberOfRounds)
{
	connect();
}

void Protocol::run() noexcept
{
	m_verifier->start();
}

void Protocol::connect() noexcept
{
	QObject::connect(m_verifier,SIGNAL(nextRound()),m_prover,SLOT(processNextRound()),::Qt::QueuedConnection);
	QObject::connect(m_prover,SIGNAL(proof(const ZKP::Proof*)),m_verifier,SLOT(processProof(const ZKP::Proof*)),::Qt::QueuedConnection);
	QObject::connect(m_verifier,SIGNAL(challenge(const ZKP::Challenge)),m_prover,SLOT(processChallenge(const ZKP::Challenge)),::Qt::QueuedConnection);
	QObject::connect(m_prover,SIGNAL(response(const ZKP::Response*)),m_verifier,SLOT(processResponse(const ZKP::Response*)),::Qt::QueuedConnection);
	QObject::connect(m_prover,SIGNAL(error(ZKP::IterativeProver::Error)),this,SLOT(error(ZKP::IterativeProver::Error)),::Qt::QueuedConnection);
	QObject::connect(m_verifier,SIGNAL(error(ZKP::IterativeVerifier::Error)),this,SLOT(error(ZKP::IterativeVerifier::Error)),::Qt::QueuedConnection);
	QObject::connect(m_verifier,SIGNAL(success()),this,SLOT(done()),::Qt::QueuedConnection);
	QObject::connect(m_verifier,SIGNAL(progress(uint64_t)),this,SLOT(progress(uint64_t)),::Qt::QueuedConnection);
}

void Protocol::done() noexcept
{
	std::cout<<"Success"<<std::endl;
	emit finished();
}

void Protocol::error(const std::string& errorString) noexcept
{
	std::cerr<<errorString<<std::endl;
	emit finished();
}

void Protocol::error(const ZKP::IterativeProver::Error errorV) noexcept
{
	std::cerr<<"Prover error: ";
	error(errorV);
}

void Protocol::error(const ZKP::IterativeVerifier::Error errorV) noexcept
{
	std::cerr<<"Verifier error: ";
	error(errorV);
}

void Protocol::progress(const uint64_t round) const noexcept
{
	std::cout<<"Round "<<round<<" / "<<m_numberOfRounds<<" completed"<<std::endl;
}

std::string Protocol::toString(const ZKP::IterativeProver::Error errorV) noexcept
{
	switch(errorV)
	{
	case ZKP::IterativeProver::Error::InvalidMessageOrder:
		return "Invalid message order";
	default:
		return "Unknown";
	}
}

std::string Protocol::toString(const ZKP::IterativeVerifier::Error errorV) noexcept
{
	switch(errorV)
	{
	case ZKP::IterativeVerifier::Error::InvalidMessage:
		return "Invalid message";
	case ZKP::IterativeVerifier::Error::InvalidMessageOrder:
		return "Invalid message order";
	case ZKP::IterativeVerifier::Error::VerificationFailed:
		return "Verification failed";
	default:
		return "Unknown";
	}
}

}

}
