#include "include/keygen.h"

namespace RSA
{
	Keygen::Keygen() {}

	Keygen::~Keygen() {}

	void Keygen::generateKeyPair(void) {}

	mpz_t* Keygen::getPublicKey(void) {}

	mpz_t* Keygen::getPrivateKey(void) {}

	void Keygen::encrypt(std::string text) {}

	void Keygen::decrypt(std::string text) {}
}