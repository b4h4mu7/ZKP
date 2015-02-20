#include "ResponseLog.h"

namespace ZKP
{

namespace Log
{

Response::Response(const CryptoPP::Integer& i) noexcept:
	m_i(i)
{
}

Cloneable* Response::clone() const noexcept
{
	return new Response(*this);
}

const CryptoPP::Integer&Response::integer() const noexcept
{
	return m_i;
}

}

}
