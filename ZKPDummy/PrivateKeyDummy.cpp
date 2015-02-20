#include "PrivateKeyDummy.h"
#include "PublicKeyDummy.h"

namespace ZKP
{

namespace Dummy
{

bool PrivateKey::s_locked=false;

void PrivateKey::lock() noexcept
{
	s_locked=true;
}

void PrivateKey::unlock() noexcept
{
	s_locked=false;
}

const ZKP::PublicKey* PrivateKey::generatePublicKeyHelper() const noexcept
{
	return s_locked?nullptr:new PublicKey;
}

}

}
