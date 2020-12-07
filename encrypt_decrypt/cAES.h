#pragma once

#include <windows.h>
#include <string>
#include <cstdlib>
#include <vector>
#include "cryptopp820/pch.h"
#include "cryptopp820/aes.h"
#include "cryptopp820/osrng.h"
#include "cryptopp820/cryptlib.h"
#include "cryptopp820/hex.h"
#include "cryptopp820/filters.h"
#include "cryptopp820/ccm.h"

using namespace std;
using namespace CryptoPP;

class cAES
{
public:
	static vector<string> encryptAES(string plain);
	static string decryptAES(string encoded, const byte* key, const byte* IV);
};

