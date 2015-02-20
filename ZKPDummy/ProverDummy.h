#ifndef ZKP_Dummy_Prover_H
#define ZKP_Dummy_Prover_H

#include "Prover.h"

namespace ZKP
{

namespace Dummy
{

class PrivateKey;

class Prover:public ZKP::Prover
{
public:
	Prover(const PrivateKey& privateKey) noexcept;
private:
	ZKP::Proof* constructProofHelper(const ZKP::PrivateKey&) const noexcept override;

	const ZKP::Response* left(const ZKP::PrivateKey&) const noexcept override;

	const ZKP::Response* right(const ZKP::PrivateKey&) const noexcept override;
};

}

}

#endif // ZKP_Dummy_Prover_H
