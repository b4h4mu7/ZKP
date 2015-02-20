#ifndef ZKP_Qt_Example_IterativeProver_H
#define ZKP_Qt_Example_IterativeProver_H

#include "QtIterativeProver.h"

namespace ZKP
{

namespace Qt
{

namespace Example
{

class IterativeProver:public Qt::IterativeProver
{
public:
	explicit IterativeProver(const PrivateKey& privateKey, QObject*const parent=nullptr) noexcept;
private:
	ZKP::Prover* constructProver(const PrivateKey& privateKey) noexcept override;
};

}

}

}

#endif // ZKP_Qt_Example_IterativeProver_H
