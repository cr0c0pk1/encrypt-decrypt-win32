#pragma once

#include <string>

using namespace std;

class CaesarCipher
{
private: 
	string fileContents;
	int shift;
public:
	CaesarCipher(string fileContents, int shift);
	string encrypt();
	string decrypt();
};

