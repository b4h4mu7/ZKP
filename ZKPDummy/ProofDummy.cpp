#include "ProofDummy.h"

namespace ZKP
{

namespace Dummy
{

Cloneable *Proof::clone() const noexcept
{
	return new Proof(*this);
}

}

}
