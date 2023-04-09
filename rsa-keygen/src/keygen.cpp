#include "include/keygen.h"

namespace RSA
{
	Keygen::Keygen(int size) : m_size(size), publicKey(0), privateKey(0) {}

	Keygen::~Keygen() {}

	mpz_class Keygen::getPublicKey(void) { return publicKey; }

	mpz_class Keygen::getPrivateKey(void) { return privateKey; }

	void Keygen::generateKeyPair(void)
	{
		// check if the keys are already created
		if (publicKey != 0 || privateKey != 0)
			std::cout << "Regenerating key pair" << std::endl;
		else
			std::cout << "Generating key pair" << std::endl;
		std::cout << "Using " << m_size << "-bit encryption" << std::endl;
		if (m_size >= 2048)
			std::cout << "It may take some time..." << std::endl;

		// initialize random state
		gmp_randstate_t state;
		gmp_randinit_default(state);
		
		// generate p and q
		mpz_t p_raw, q_raw;
		mpz_init(p_raw);
		mpz_init(q_raw);
		mpz_urandomb(p_raw, state, m_size);
		mpz_urandomb(q_raw, state, m_size);

		// set least significant bit to 1 to ensure odd primes
		mpz_setbit(p_raw, 0);
		mpz_setbit(q_raw, 0);

		// find and set next prime after p and q
		while (1)
		{
			mpz_nextprime(p_raw, p_raw);
			if (mpz_probab_prime_p(p_raw, 32))
				break;
		}
		while (1)
		{
			mpz_nextprime(q_raw, q_raw);
			if (mpz_probab_prime_p(q_raw, 32))
				break;
		}

		// convert to mpz_class
		mpz_class p(p_raw);
		mpz_class q(q_raw);

		// clear mpz_t tmp variables
		mpz_clear(p_raw);
		mpz_clear(q_raw);

		// assert p and q are equal
		assert(p != q);

		// clear random state
		gmp_randclear(state);

		// calculate n = p * q
		mpz_class n = p * q;
		publicKey = n;

		// calculate phi_n
		mpz_class phi_n = (p - 1) * (q - 1);
		
		// calculate d
		mpz_t d_raw;
		mpz_init(d_raw);
		mpz_invert(d_raw, e.get_mpz_t(), phi_n.get_mpz_t());
		mpz_class d(d_raw);
		mpz_clear(d_raw);

		// set private key
		privateKey = d;
	}

	std::string Keygen::encrypt(std::string text)
	{
		// check and generate new key if needed
		if (publicKey == 0 || privateKey == 0)
		{
			std::cout << "Key pair is not created!" << std::endl;
			std::cout << "Creating now..." << std::endl;
			generateKeyPair();
		}
		std::cout << "Encrypting..." << std::endl;

		// initialize message as encoded mpz
		mpz_t message_raw;
		mpz_init(message_raw);
		std::string message = textToOct(text);
		mpz_init_set_str(message_raw, message.c_str(), 10);

		// initialize encrypted message
		mpz_t encrypted_raw;
		mpz_init(encrypted_raw);
		
		// encrypt message
		mpz_powm(encrypted_raw, message_raw, e.get_mpz_t(), publicKey.get_mpz_t());
		mpz_clear(message_raw);

		// return string
		mpz_class encrypted(encrypted_raw);
		mpz_clear(encrypted_raw);
		return encrypted.get_str();
		//return textToOct(std::string(message.get_str()));
	}

	std::string Keygen::decrypt(std::string text, mpz_class m_privateKey, mpz_class m_publicKey)
	{
		// check and throw exception
		if (m_publicKey == 0 || m_privateKey == 0)
			throw std::runtime_error("Key pair is not created! Cannot decrypt message");
		std::cout << "Decrypting..." << std::endl;

		// initialize encrypted message
		mpz_t encrypted_raw;
		mpz_init(encrypted_raw);
		mpz_init_set_str(encrypted_raw, text.c_str(), 10);

		// initialize message as mpz
		mpz_t message_raw;
		mpz_init(message_raw);

		// decrypt message
		mpz_powm(message_raw, encrypted_raw, m_privateKey.get_mpz_t(), m_publicKey.get_mpz_t());
		mpz_clear(encrypted_raw);

		// create mpz class and clear mpz_t
		mpz_class message(message_raw);
		mpz_clear(message_raw);

		// recreate potential 0 at the beginning
		std::string full_message = message.get_str();
		while (full_message.length() % 3 != 0)
			full_message = std::string("0") + full_message;

		// return final message
		return octToText(full_message);
	}

	std::string textToOct(std::string text)
	{
		std::string encoded;

		for_each(text.begin(), text.end(), [&encoded](char& c)
			{
				int code = (int)c;
				std::string partial = std::to_string(code);

				if (code < 10)
				{
					encoded.push_back('0');
					encoded.push_back('0');
					encoded += partial;
				}
				else if (code < 100)
				{
					encoded.push_back('0');
					encoded += partial;
				}
				else
					encoded += partial;
				
			});

		// return encoded text
		return encoded;
	}
	
	std::string octToText(std::string text)
	{
		assert(text.length() % 3 == 0);

		std::string decoded;

		for (int i = 2; i < text.length(); i += 3)
		{
			std::string partial;
			partial.push_back(text[i - 2]);
			partial.push_back(text[i - 1]);
			partial.push_back(text[i]);
			decoded.push_back((char)std::stoi(partial));
		}

		// return decoded text
		return decoded;
	}
}