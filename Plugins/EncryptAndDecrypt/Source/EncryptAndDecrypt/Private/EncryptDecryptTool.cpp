#include "EncryptDecryptTool.h"


FString EncryptAndDecryptTool::Encrypt(FString Src, WORD Key)
{
	FString Result, str;
	int32 i, j;
	Result = Src;

	for (i = 0; i < Src.Len(); i++)
	{
		Result[i] = Src[i] ^ (Key >> 8);
		Key = ((BYTE)Result[i] + Key)*C1 + C2;
	}
	Src = Result;
	Result.Empty();

	for (i = 0; i < Src.Len(); i++)
	{
		j = (BYTE)Src[i];
		str = "12";
		str[0] = COMPLEXITY_NUM + j / 26;
		str[1] = COMPLEXITY_NUM + j % 26;
		Result += str;
	}

	return Result;
}

FString EncryptAndDecryptTool::Decrypt(FString Des, WORD Key)
{
	FString Result, str;
	int32 i, j;
	Result.Empty();
	for (i = 0; i < Des.Len() / 2; i++)
	{
		j = ((BYTE)Des[2 * i] - COMPLEXITY_NUM) * 26;
		j += (BYTE)Des[2 * i + 1] - COMPLEXITY_NUM;
		str = "1";
		str[0] = j;
		Result += str;
	}
	Des = Result;
	for (i = 0; i < Des.Len(); i++)
	{
		Result[i] = (BYTE)Des[i] ^ (Key >> 8);
		Key = ((BYTE)Des[i] + Key)*C1 + C2;
	}
	return Result;
}
