#ifndef ZKP_Dummy_Proof_H
#define ZKP_Dummy_Proof_H

#include "Proof.h"

namespace ZKP
{

namespace Dummy
{

class Proof:public ZKP::Proof
{
public:
	Proof() noexcept = default;

	Cloneable* clone() const noexcept override;
};

}

}

#endif // ZKP_Dummy_Proof_H
