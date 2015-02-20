#ifndef ZKP_PublicKey_H
#define ZKP_PublicKey_H

#include "Cloneable.h"

namespace ZKP
{

class Proof;

//! Base class for zero-knowledge public key.
class PublicKey:public Cloneable
{
public:
	virtual ~PublicKey() noexcept = default;
};

}

#endif // ZKP_PublicKey_H
