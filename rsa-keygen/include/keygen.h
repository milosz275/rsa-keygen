#ifndef KEYGEN_H
#define KEYGEN_H

#include <iostream>
#include <gmp.h>

namespace RSA
{
	class Keygen
	{
		mpz_t privateKey;

		mpz_t publicKey;
	public:
		Keygen();

		~Keygen();

		void generateKeyPair(void);

		mpz_t* getPublicKey(void);

		mpz_t* getPrivateKey(void);

		void encrypt(std::string text);

		void decrypt(std::string text);
	};
}

#endif // !KEYGEN_H
