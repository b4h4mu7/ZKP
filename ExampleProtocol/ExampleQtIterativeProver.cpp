#include "ExampleQtIterativeProver.h"
#include "ProverLog.h"
#include "PrivateKeyLog.h"

namespace ZKP
{

namespace Qt
{

namespace Example
{

IterativeProver::IterativeProver(const PrivateKey& privateKey, QObject*const parent) noexcept:
	Qt::IterativeProver(privateKey,parent)
{
}

ZKP::Prover* IterativeProver::constructProver(const PrivateKey& privateKey) noexcept
{
	return new Log::Prover(dynamic_cast<const Log::PrivateKey&>(privateKey));
}

}

}

}
