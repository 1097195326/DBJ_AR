#pragma once
#include "Engine.h"
#include "Misc/SecureHash.h"
#include "CoreMinimal.h"


#include <iostream>
#include <ctime>

using namespace std;


#define C1 52845  
#define C2 22719  
#define COMPLEXITY_NUM 1024 
#if !PLATFORM_WINDOWS

typedef unsigned char       BYTE;
typedef unsigned short      WORD;

#endif

#define EncryptKey 4890

class ENCRYPTANDDECRYPT_API EncryptAndDecryptTool
{
public:
	static FString Encrypt(FString Src, WORD Key);

	static FString Decrypt(FString Des, WORD Key);

};
