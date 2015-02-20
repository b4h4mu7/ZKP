#ifndef ZKP_PrivateKey_H
#define ZKP_PrivateKey_H

#include <memory>
#include "PublicKey.h"

namespace ZKP
{

//! Base class for zero-knowledge private keys.
class PrivateKey
{
public:
	//! Exception class thrown when publicKey() cannot construct a key.
	class Exception:public std::runtime_error
	{
	public:
		using std::runtime_error::runtime_error;
	};

	virtual ~PrivateKey() noexcept = default;

	/*!
	   \brief Construct a PublicKey for this PrivateKey.

	   This is a laze construction, meaning that a PrivateKey is constructed at the first invokation and only then.
	   \return The PublicKey.
	   \throw Exception If the PublicKey cannot be constructed.
	 */
	const PublicKey& publicKey() const;
private:
	//! Internal helper for creating a PublicKey for the concrete PrivatKey class.
	virtual const PublicKey* generatePublicKeyHelper() const noexcept = 0;

	//! Cache for PublicKey.
	mutable std::unique_ptr<const PublicKey> m_publicKey;
};

}

#endif // ZKP_PrivateKey_H
