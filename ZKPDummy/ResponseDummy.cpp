#include "ResponseDummy.h"

namespace ZKP
{

namespace Dummy
{

Response::Response(const bool value) noexcept:
	m_value(value)
{
}

bool Response::value() const noexcept
{
	return m_value;
}

Cloneable *Response::clone() const noexcept
{
	return new Response(*this);
}

}

}
