#ifndef ZKP_Proof_H
#define ZKP_Proof_H

#include "Cloneable.h"

namespace ZKP
{

/*!
   \brief Base class for the proof issued by the prover.
 */
class Proof:public Cloneable
{
public:
	Proof() noexcept = default;

	virtual ~Proof() = default;
};

}

#endif // ZKP_Proof_H
