#ifndef KEYGEN_H
#define KEYGEN_H

#include <iostream>
#include <gmpxx.h>
#include <cassert>

namespace rsa
{
	// RSA exponent
	static const mpz_class e("65537");
	// macro encoding text in octal
	std::string text_to_oct(std::string text);
	// macro decoding octal to text
	std::string oct_to_text(std::string text);

	class keygen
	{
		// private key
		mpz_class m_private_key;
		// public key
		mpz_class m_public_key;
		// bits of a number to generate
		const int m_size = 1024;
	public:
		// creates key generator
		keygen(int size = 1024);
		// deletes the key generator
		~keygen();
		// generates both private and public keys
		void generate_key_pair(void);
		// returns generated public key
		mpz_class get_public_key(void);
		// returns generated private key
		mpz_class get_private_key(void);
		// encrypts given text
		std::string encrypt(std::string text);
		// decrypts given text
		std::string decrypt(std::string text, mpz_class private_key, mpz_class public_key);
	};
}

#endif // !KEYGEN_H
