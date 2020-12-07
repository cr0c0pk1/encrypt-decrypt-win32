#pragma once

#include <string>
#include <fstream>

using namespace std;

class FileIO
{
public:
	static string readFile(string fileName);
	static void writeFile(string fileName, string contentsOut);
};

