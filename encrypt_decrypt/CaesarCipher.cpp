#include "CaesarCipher.h"

CaesarCipher::CaesarCipher(string fileContents, int shift)
	: fileContents(fileContents), shift(shift) {};

string CaesarCipher::encrypt()
{
    string result = "";

    for (int i = 0; i < fileContents.length(); i++)
    {
        if (islower(fileContents[i]))
        {
            result += char(int(fileContents[i] + shift - 97) % 26 + 97);
        }
        else if (isupper(fileContents[i]))
        {
            result += char(int(fileContents[i] + shift - 65) % 26 + 65);
        }
        else
        {
            result += fileContents[i];
        }
    }

    return result;
}

string CaesarCipher::decrypt()
{
    string result = "";
    int decryptShift = 26 - shift;

    for (int i = 0; i < fileContents.length(); i++)
    {
        if (islower(fileContents[i]))
        {
            result += char(int(fileContents[i] + decryptShift - 97) % 26 + 97);
        }
        else if (isupper(fileContents[i]))
        {
            result += char(int(fileContents[i] + decryptShift - 65) % 26 + 65);
        }
        else
        {
            result += fileContents[i];
        }
    }

    return result;
}