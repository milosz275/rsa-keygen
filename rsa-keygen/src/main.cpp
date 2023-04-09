#include <iostream>
#include "include/keygen.h"

int main(int argc, char* argv[])
{
	try
	{
		// create key generator and key pair
		RSA::Keygen* K = new RSA::Keygen(4096);
		K->generateKeyPair();
		std::cout << "private key: " << K->getPrivateKey() << std::endl << std::endl;
		std::cout << "public key: " << K->getPublicKey() << std::endl << std::endl;

		// encrypt and decrypt some data
		std::string message("This message is safely encrypted:)");
		std::cout << "message to encrypt: " << message << std::endl << std::endl;
		
		std::string encrypted_message = K->encrypt(message);
		std::cout << "encrypted message: " << encrypted_message << std::endl << std::endl;
		
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