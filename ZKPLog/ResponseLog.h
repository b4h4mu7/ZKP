#ifndef ZKP_Log_Response_H
#define ZKP_Log_Response_H

#include "Response.h"
#include <crypto++/integer.h>

namespace ZKP
{

namespace Log
{

//! Implementation for the discrete log ZKP.
class Response:public ZKP::Response
{
public:
	/*!
	   \brief Ctor.
	   \param i The response integer.
	 */
	Response(const CryptoPP::Integer& i) noexcept;

	Cloneable* clone() const noexcept override;

	//! Getter for the response integer.
	const CryptoPP::Integer& integer() const noexcept;
private:
	//! The response integer.
	const CryptoPP::Integer m_i;
};

}

}

#endif // ZKP_Log_Response_H
