#include "PrivateKey.h"

namespace ZKP
{

const PublicKey& PrivateKey::publicKey() const
{
	if(not m_publicKey)
	{
		m_publicKey.reset(generatePublicKeyHelper());
	}
	if(not m_publicKey)
	{
		throw Exception("Unable to construct a public key");
	}
	return *m_publicKey;
}

}
