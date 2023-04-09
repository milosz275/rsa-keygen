#ifndef KEYGEN_H
#define KEYGEN_H

#include <iostream>
#include <gmpxx.h>
#include <cassert>

namespace RSA
{
	// RSA exponent
	static const mpz_class e("65537");
	// macro encoding text in octal
	std::string textToOct(std::string text);
	// macro decoding octal to text
	std::string octToText(std::string text);

	class Keygen
	{
		// private key
		mpz_class privateKey;
		// public key
		mpz_class publicKey;
		// bits of a number to generate
		const int m_size = 1024;
	public:
		// creates key generator
		Keygen(int size = 1024);
		// deletes the key generator
		~Keygen();
		// generates both private and public keys
		void generateKeyPair(void);
		// returns generated public key
		mpz_class getPublicKey(void);
		// returns generated private key
		mpz_class getPrivateKey(void);
		// encrypts given text
		std::string encrypt(std::string text);
		// decrypts given text
		std::string decrypt(std::string text, mpz_class m_privateKey, mpz_class m_publicKey);
	};
}

#endif // !KEYGEN_H
