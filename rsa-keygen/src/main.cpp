#include <iostream>
#include "include/keygen.h"

int main(int argc, char* argv[])
{
	try
	{
		RSA::Keygen* K = new RSA::Keygen();
		K->generateKeyPair(1024);
		std::cout << "private key: " << K->getPrivateKey() << std::endl;
		std::cout << "public key: " << K->getPublicKey() << std::endl;
		std::string message("12345");
		std::cout << "message to encrypt: " << message << std::endl;
		std::string encrypted_message = K->encrypt(message);
		std::string decrypted_message = K->decrypt(encrypted_message, K->getPrivateKey(), K->getPublicKey());
		std::cout << "decrypted message: " << decrypted_message << std::endl;
		delete K;
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}