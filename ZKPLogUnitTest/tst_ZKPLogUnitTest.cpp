#include <QtTest>
#include "PrivateKeyLog.h"
#include "ProofLog.h"
#include "ProverLog.h"
#include "PublicKeyLog.h"
#include "ResponseLog.h"
#include "VerifierLog.h"

using namespace ZKP::Log;

class ZKPLogUnitTest:public QObject
{
	Q_OBJECT
public:
	ZKPLogUnitTest() = default;
private Q_SLOTS:
	void privateKey();
	void proof();
	void prover();
	void publicKey();
	void invalidKey();
	void response();
	void verifier();
};

void ZKPLogUnitTest::privateKey()
{
	const unsigned int b=1024;
	const PrivateKey k1(1,b,256);
	QVERIFY(k1.bits()==b);
	const PrivateKey k2;
	QVERIFY(k2.bits()==2048);
	QVERIFY(CryptoPP::Integer::One()==a_exp_b_mod_c(k2.g(),k2.q(),k2.p()));
}

void ZKPLogUnitTest::proof()
{
	const Proof proof(CryptoPP::Integer::One());
	QVERIFY(proof.C()==CryptoPP::Integer::One());
	const std::unique_ptr<const Proof> clone(dynamic_cast<const Proof*>(proof.clone()));
	QVERIFY(clone.get());
	QVERIFY(proof.C()==clone->C());
}

void ZKPLogUnitTest::prover()
{
	const PrivateKey key;
	Prover prover(key);
	const Proof& proof=dynamic_cast<const Proof&>(prover.constructProof());
	const Response& response1=dynamic_cast<const Response&>(prover.respond(ZKP::Challenge::Left));
	const CryptoPP::Integer& C=proof.C();
	const CryptoPP::Integer& g=key.g();
	const CryptoPP::Integer& p=key.p();
	const CryptoPP::Integer& y=dynamic_cast<const PublicKey&>(key.publicKey()).y();
	QVERIFY(C==a_exp_b_mod_c(g,response1.integer(),p));
	const Response& response2=dynamic_cast<const Response&>(prover.respond(ZKP::Challenge::Right));
	QVERIFY(C.Times(y).Modulo(p)==a_exp_b_mod_c(g,response2.integer(),p));
}

void ZKPLogUnitTest::publicKey()
{
	const PrivateKey privateKey;
	const PublicKey& publicKey=dynamic_cast<const PublicKey&>(privateKey.publicKey());
	QVERIFY(publicKey.g()==privateKey.g());
	QVERIFY(publicKey.p()==privateKey.p());
	QVERIFY(publicKey.y()==a_exp_b_mod_c(publicKey.g(),privateKey.x(),publicKey.p()));
	const std::unique_ptr<const PublicKey> clone(dynamic_cast<const PublicKey*>(publicKey.clone()));
	QVERIFY(clone.get());
	QVERIFY(publicKey.g()==clone->g());
	QVERIFY(publicKey.p()==clone->p());
	QVERIFY(publicKey.y()==clone->y());
}

void ZKPLogUnitTest::invalidKey()
{
	const PrivateKey key;
	const CryptoPP::Integer y=a_exp_b_mod_c(key.g(),key.x(),key.p());
	try
	{
		PublicKey(CryptoPP::Integer::One(),key.p(),key.q(),y);
		QVERIFY(false);
	}
	catch(const std::invalid_argument&)
	{
	}
	try
	{
		PublicKey(key.g(),2048,key.q(),y);
	}
	catch(const std::invalid_argument&)
	{
	}
	try
	{
		PublicKey(key.g(),key.p(),2048,y);
	}
	catch(const std::invalid_argument&)
	{
	}
	try
	{
		PublicKey(key.g(),key.p(),key.q()==3?5:3,y);
	}
	catch(const std::invalid_argument&)
	{
	}
}

void ZKPLogUnitTest::response()
{
	const CryptoPP::Integer i(1000);
	const Response response(i);
	QVERIFY(response.integer()==i);
	const std::unique_ptr<const Response> clone(dynamic_cast<const Response*>(response.clone()));
	QVERIFY(clone.get());
	QVERIFY(response.integer()==clone->integer());
}

void ZKPLogUnitTest::verifier()
{
	const PrivateKey privateKey;
	Prover prover(privateKey);
	const Verifier verifier(dynamic_cast<const PublicKey&>(privateKey.publicKey()),dynamic_cast<const Proof&>(prover.constructProof()));
	const ZKP::Challenge challenge=verifier.challenge();
	QVERIFY(verifier.verify(dynamic_cast<const Response&>(prover.respond(challenge))));
	const ZKP::Challenge challengeWrong(challenge==ZKP::Challenge::Left?ZKP::Challenge::Right:ZKP::Challenge::Left);
	QVERIFY(not verifier.verify(dynamic_cast<const Response&>(prover.respond(challengeWrong))));
}

QTEST_APPLESS_MAIN(ZKPLogUnitTest)

#include "tst_ZKPLogUnitTest.moc"
