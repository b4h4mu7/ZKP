#ifndef ZKP_Dummy_PrivateKey_H
#define ZKP_Dummy_PrivateKey_H

#include "PrivateKey.h"

namespace ZKP
{

namespace Dummy
{

class PrivateKey:public ZKP::PrivateKey
{
public:
	static void lock() noexcept;

	static void unlock() noexcept;
private:
	const ZKP::PublicKey* generatePublicKeyHelper() const noexcept override;

	static bool s_locked;
};

}

}

#endif // ZKP_Dummy_PrivateKey_H
