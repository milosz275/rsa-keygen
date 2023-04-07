#ifndef KEYGEN_H
#define KEYGEN_H

#include <iostream>
//#include <gmp.h>
#include <gmpxx.h>
#include <cassert>

namespace RSA
{
	class Keygen
	{
		//
		mpz_class privateKey;
		//
		mpz_class publicKey;
		// RSA exponent
		mpz_class e;
	public:
		// creates key generator
		Keygen();
		// deletes the key generator
		~Keygen();
		//
		void generateKeyPair(int size = 1024);
		//
		mpz_class getPublicKey(void);
		//
		mpz_class getPrivateKey(void);
		//
		std::string encrypt(std::string text);
		//
		std::string decrypt(std::string text, mpz_class m_privateKey, mpz_class m_publicKey);
	};
}

#endif // !KEYGEN_H
