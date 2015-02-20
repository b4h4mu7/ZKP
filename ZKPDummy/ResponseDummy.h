#ifndef ZKP_Dummy_Response_H
#define ZKP_Dummy_Response_H

#include "Response.h"

namespace ZKP
{

namespace Dummy
{

class Response:public ZKP::Response
{
public:
	Response(const bool value) noexcept;

	bool value() const noexcept;

	Cloneable* clone() const noexcept override;
private:
	const bool m_value;
};

}

}

#endif // ZKP_Dummy_Response_H
