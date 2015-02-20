#ifndef ZKP_Dummy_PublicKey_H
#define ZKP_Dummy_PublicKey_H

#include "PublicKey.h"

namespace ZKP
{

namespace Dummy
{

class PublicKey:public ZKP::PublicKey
{
public:
	ZKP::Cloneable* clone() const noexcept override;
};

}

}

#endif // ZKP_Dummy_PrivateKey_H
