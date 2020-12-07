#include "cAES.h"

vector<string> cAES::encryptAES(string plain)
{
	vector<string> elementsAES;

	AutoSeededRandomPool prng;

	byte key[AES::DEFAULT_KEYLENGTH];
	prng.GenerateBlock(key, sizeof(key));

	byte iv[AES::BLOCKSIZE];
	prng.GenerateBlock(iv, sizeof(iv));

	string cipher, encodedCipher, encodedKey, encodedIV;
	
	StringSource(key, sizeof(key), true, new HexEncoder( new StringSink(encodedKey))  ); //hex // StringSource
	elementsAES.push_back(encodedKey);

	StringSource(iv, sizeof(iv), true,
		new HexEncoder(
			new StringSink(encodedIV)
		) // HexEncoder
	); // StringSource
	elementsAES.push_back(encodedIV);

	try
	{
		CBC_Mode< AES >::Encryption e;
		e.SetKeyWithIV(key, sizeof(key), iv);

		// The StreamTransformationFilter removes
		//  padding as required.
		StringSource s(plain, true,
			new StreamTransformationFilter(e,
				new StringSink(cipher)
			) // StreamTransformationFilter
		); // StringSource
#if 0
		StreamTransformationFilter filter(e);
		filter.Put((const byte*)plain.data(), plain.size());
		filter.MessageEnd();

		const size_t ret = filter.MaxRetrievable();
		cipher.resize(ret);
		filter.Get((byte*)cipher.data(), cipher.size());
#endif
	}
	catch (const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}

	StringSource(cipher, true,
		new HexEncoder(
			new StringSink(encodedCipher)
		) // HexEncoder
	); // StringSource
	elementsAES.push_back(encodedCipher);

	return elementsAES;
}

string cAES::decryptAES(string cipher, const byte* key, const byte* iv)
{
	string recovered;

	try
	{
		CBC_Mode< AES >::Decryption d;
		d.SetKeyWithIV(key, 16, iv);

		// The StreamTransformationFilter removes
		//  padding as required.
		StringSource s(cipher, true, new HexDecoder
		(new StreamTransformationFilter(d,
			new StringSink(recovered))));
#if 0
		StreamTransformationFilter filter(d);
		filter.Put((const byte*)cipher.data(), cipher.size());
		filter.MessageEnd();

		const size_t ret = filter.MaxRetrievable();
		recovered.resize(ret);
		filter.Get((byte*)recovered.data(), recovered.size());
#endif
	}
	catch (const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}

	return recovered;
}


