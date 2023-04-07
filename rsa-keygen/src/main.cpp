#include <iostream>
#include "include/keygen.h"

int main(int argc, char* argv[])
{
	try
	{
		RSA::Keygen* K = new RSA::Keygen();
		//K
		delete K;
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}



	return 0;
}