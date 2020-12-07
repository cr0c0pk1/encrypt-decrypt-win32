// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <commdlg.h> //using for openfilename
#include <fstream>	//using for files
#include <vector>	//using for deleteFilePath function
#include "CaesarCipher.h"	//private class
/*#include "cryptopp820/pch.h"
#include "cryptopp820/aes.h"
#include "cryptopp820/osrng.h"
#include "cryptopp820/cryptlib.h"
#include "cryptopp820/hex.h"
#include "cryptopp820/filters.h"
#include "cryptopp820/ccm.h"*/
#include "cAES.h"	//private class
