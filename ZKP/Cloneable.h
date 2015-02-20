#ifndef ZKP_Cloneable_H
#define ZKP_Cloneable_H

namespace ZKP
{

//! Interface for cloneable objects.
class Cloneable
{
public:
	virtual ~Cloneable() noexcept = default;

	//! Clone method to be implemented by the concrete classes.
	virtual Cloneable* clone() const noexcept = 0;
};

}

#endif // ZKP_Cloneable_H
