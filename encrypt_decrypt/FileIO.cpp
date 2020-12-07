#include "FileIO.h"

string FileIO::readFile(string fileName)
{
	ifstream inFile(fileName);

	string contents((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());

	return contents;
}

void FileIO::writeFile(string fileName, string contentsOut)
{
	ofstream outFile(fileName);

	outFile << contentsOut;

	outFile.close();
}
