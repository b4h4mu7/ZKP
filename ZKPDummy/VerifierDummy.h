#ifndef ZKP_Dummy_Verifier_H
#define ZKP_Dummy_Verifier_H

#include "Verifier.h"

namespace ZKP
{

namespace Dummy
{

class PublicKey;
class Proof;

class Verifier:public ZKP::Verifier
{
public:
	Verifier(const PublicKey& publicKey,const Proof& proof) noexcept;
private:
	bool verifyHelperLeft(const ZKP::PublicKey&, const ZKP::Proof&, const ZKP::Response& response) const noexcept override;

	bool verifyHelperRight(const ZKP::PublicKey&, const ZKP::Proof&, const ZKP::Response& response) const noexcept override;
};

}

}

#endif // ZKP_Dummy_Verifier_H
