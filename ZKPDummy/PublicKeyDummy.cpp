#include "PublicKeyDummy.h"

namespace ZKP
{

namespace Dummy
{

Cloneable* PublicKey::clone() const noexcept
{
	return new PublicKey(*this);
}

}

}
