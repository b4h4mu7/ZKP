#include <QSignalSpy>
#include <QtTest>
#include "QtIterativeProver.h"
#include "QtIterativeVerifier.h"
#include "ProofDummy.h"
#include "ResponseDummy.h"
#include "ProverDummy.h"
#include "VerifierDummy.h"
#include "PublicKeyDummy.h"
#include "PrivateKeyDummy.h"

Q_DECLARE_METATYPE(const ZKP::Response*)
Q_DECLARE_METATYPE(ZKP::IterativeVerifier::Error)
Q_DECLARE_METATYPE(ZKP::Challenge)
Q_DECLARE_METATYPE(const ZKP::Proof*)
Q_DECLARE_METATYPE(ZKP::IterativeProver::Error)

using namespace ZKP::Dummy;

class IterativeProver:public ZKP::Qt::IterativeProver
{
public:
	IterativeProver(const ZKP::PrivateKey& privateKey):
		ZKP::Qt::IterativeProver(privateKey)
	{
	}
private:
	ZKP::Prover* constructProver(const ZKP::PrivateKey& privateKey) noexcept override
	{
		return new Prover(dynamic_cast<const PrivateKey&>(privateKey));
	}
};

class IterativeVerifier:public ZKP::Qt::IterativeVerifier
{
public:
	explicit IterativeVerifier(const ZKP::PublicKey& publicKey,const uint64_t rounds) noexcept:
		ZKP::Qt::IterativeVerifier(publicKey,rounds)
	{
	}
private:
	ZKP::Verifier* constructVerifier(const ZKP::PublicKey& publicKey,const ZKP::Proof& proof) const noexcept override
	{
		return new Verifier(dynamic_cast<const PublicKey&>(publicKey),dynamic_cast<const Proof&>(proof));
	}
};

class ZKPUnitTest:public QObject
{
	Q_OBJECT
public:
	ZKPUnitTest();
private Q_SLOTS:
	void publicKey();
	void privateKey();
	void response();
	void proof();
	void prover();
	void verifier();
	void iterativeProver();
	void iterativeVerifier();
};

ZKPUnitTest::ZKPUnitTest()
{
}

void ZKPUnitTest::publicKey()
{
	const PublicKey key;
	std::unique_ptr<const PublicKey> keyPtr(dynamic_cast<const PublicKey*>(key.clone()));
	QVERIFY(keyPtr.get());
}

void ZKPUnitTest::privateKey()
{
	const PrivateKey key;
	const ZKP::PublicKey& public1=key.publicKey();
	const ZKP::PublicKey& public2=key.publicKey();
	QVERIFY(&public1==&public2);
	const PrivateKey keyLocked;
	key.lock();
	try
	{
		keyLocked.publicKey();
		QVERIFY(false);
	}
	catch(const PrivateKey::Exception&)
	{
	}
	key.unlock();
}

void ZKPUnitTest::response()
{
	const Response response1(true);
	const Response response2(not response1.value());
	const std::unique_ptr<const ZKP::Cloneable> clone1(response1.clone());
	const std::unique_ptr<const ZKP::Cloneable> clone2(response2.clone());
	std::vector<std::pair<const Response*,const Response*>> responses;
	responses.push_back(std::make_pair(&response1,&response2));
	responses.push_back(std::make_pair(dynamic_cast<const Response*>(clone1.get()),dynamic_cast<const Response*>(clone2.get())));
	for(const auto& p:responses)
	{
		const Response& response1=*p.first;
		const Response& response2=*p.second;
		QVERIFY(response1.value());
		QVERIFY(not response2.value());
	}
}

void ZKPUnitTest::proof()
{
	const Proof proof;
	const std::unique_ptr<const ZKP::Cloneable> clone(proof.clone());
	QVERIFY(clone.get());
}

void ZKPUnitTest::prover()
{
	const PrivateKey privateKey;
	Prover prover(privateKey);
	prover.constructProof();
	const ZKP::Challenge challengeLeft(ZKP::Challenge::Left);
	const Response response1(dynamic_cast<const Response&>(prover.respond(challengeLeft)));
	const ZKP::Response& response2=prover.respond(ZKP::Challenge::Right);
	QVERIFY(response1.value()!=dynamic_cast<const Response&>(response2).value());
}

void ZKPUnitTest::verifier()
{
	const PrivateKey privateKey;
	const PublicKey& publicKey=dynamic_cast<const PublicKey&>(privateKey.publicKey());
	const Proof proof;
	for(unsigned int i=0;i<100;++i)
	{
		Prover prover(privateKey);
		const Verifier verifier(publicKey,proof);
		QVERIFY(verifier.verify(prover.respond(verifier.challenge())));
	}
}

void ZKPUnitTest::iterativeProver()
{
	const PrivateKey privateKey;
	{
	IterativeProver prover(privateKey);
	QSignalSpy nextRoundSignal(&prover,SIGNAL(proof(const ZKP::Proof*)));
	QSignalSpy errorSignal(&prover,SIGNAL(error(ZKP::IterativeProver::Error)));
	prover.processNextRound();
	QVERIFY(nextRoundSignal.count()==1);
	QVERIFY(errorSignal.count()==0);
	QVERIFY(dynamic_cast<const Proof*>(qvariant_cast<const ZKP::Proof*>(nextRoundSignal.takeFirst().at(0))));
	prover.processNextRound();
	QVERIFY(nextRoundSignal.count()==1);
	QVERIFY(errorSignal.count()==0);
	}
	{
	IterativeProver prover(privateKey);
	QSignalSpy responseSignal(&prover,SIGNAL(response(const ZKP::Response*)));
	QSignalSpy errorSignal(&prover,SIGNAL(error(ZKP::IterativeProver::Error)));
	const ZKP::Challenge challenge(ZKP::Challenge::Left);
	prover.processChallenge(challenge);
	QVERIFY(responseSignal.count()==0);
	QVERIFY(errorSignal.count()==1);
	QVERIFY(qvariant_cast<ZKP::IterativeProver::Error>(errorSignal.takeFirst().at(0))==ZKP::IterativeProver::Error::InvalidMessageOrder);
	prover.processNextRound();
	prover.processChallenge(challenge);
	QVERIFY(responseSignal.count()==1);
	QVERIFY(errorSignal.count()==0);
	const Response*const response=dynamic_cast<const Response*>(qvariant_cast<const ZKP::Response*>(responseSignal.takeFirst().at(0)));
	QVERIFY(response);
	QVERIFY(response->value());
	}
}

void ZKPUnitTest::iterativeVerifier()
{
	const PrivateKey privateKey;
	const ZKP::PublicKey& publicKey=privateKey.publicKey();
	const uint64_t rounds=3;
	IterativeVerifier verifier(publicKey,rounds);
	QSignalSpy progressSignal(&verifier,SIGNAL(progress(const uint64_t)));
	QSignalSpy errorSignal(&verifier,SIGNAL(error(const ZKP::IterativeVerifier::Error)));
	QSignalSpy challengeSignal(&verifier,SIGNAL(challenge(const ZKP::Challenge)));
	QSignalSpy successSignal(&verifier,SIGNAL(success()));
	QSignalSpy nextRoundSignal(&verifier,SIGNAL(nextRound()));
	verifier.processProof(nullptr);
	QVERIFY(errorSignal.count()==1);
	QVERIFY(qvariant_cast<ZKP::IterativeVerifier::Error>(errorSignal.takeFirst().at(0))==ZKP::IterativeVerifier::Error::InvalidMessage);
	verifier.processResponse(nullptr);
	QVERIFY(errorSignal.count()==1);
	QVERIFY(qvariant_cast<ZKP::IterativeVerifier::Error>(errorSignal.takeFirst().at(0))==ZKP::IterativeVerifier::Error::InvalidMessage);
	const Response responseOutOfOrder(true);
	verifier.processResponse(&responseOutOfOrder);
	QVERIFY(errorSignal.count()==1);
	QVERIFY(qvariant_cast<ZKP::IterativeVerifier::Error>(errorSignal.takeFirst().at(0))==ZKP::IterativeVerifier::Error::InvalidMessageOrder);
	for(uint64_t i=0;i<rounds+1;++i)
	{
		const Proof proof;
		verifier.processProof(&proof);
		QVERIFY(challengeSignal.count()==1);
		const ZKP::Challenge challenge=qvariant_cast<ZKP::Challenge>(challengeSignal.takeFirst().at(0));
		Prover prover(privateKey);
		const ZKP::Response& response=prover.respond(challenge);
		if(i<rounds)
		{
			verifier.processResponse(&response);
			if(i+1<rounds)
			{
				QVERIFY(unsigned(nextRoundSignal.count())==i+1);
				QVERIFY(progressSignal.count()==1);
				QVERIFY(qvariant_cast<uint64_t>(progressSignal.takeFirst().at(0))==i+1);
			}
			else
			{
				QVERIFY(successSignal.count()==1);
			}
		}
		else
		{
			const Response flipped(not dynamic_cast<const Response&>(response).value());
			verifier.processResponse(&flipped);
			QVERIFY(errorSignal.count()==1);
			QVERIFY(qvariant_cast<ZKP::IterativeVerifier::Error>(errorSignal.takeFirst().at(0))==ZKP::IterativeVerifier::Error::VerificationFailed);
		}
	}
}

QTEST_APPLESS_MAIN(ZKPUnitTest)

#include "tst_ZKPUnitTest.moc"
