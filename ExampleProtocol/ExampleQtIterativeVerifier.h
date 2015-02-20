#ifndef ZKP_Qt_Example_IterativeVerifier_H
#define ZKP_Qt_Example_IterativeVerifier_H

#include "QtIterativeVerifier.h"

namespace ZKP
{

namespace Qt
{

namespace Example
{

class IterativeVerifier:public Qt::IterativeVerifier
{
public:
	explicit IterativeVerifier(const PublicKey& publicKey, const uint64_t rounds,QObject*const parent=nullptr) noexcept;
private:
	Verifier* constructVerifier(const PublicKey& publicKey,const Proof& proof) const noexcept override;
};

}

}

}

#endif // ZKP_Qt_Example_IterativeVerifier_H
