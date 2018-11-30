#pragma once
#include "CoreMinimal.h"
#include "Engine.h"
#include "Runtime/Core/Public/Misc/Paths.h"
enum EOpenReturnCode
{
	E_OK=0,
	E_CANCEL=1,
	E_ERROR=2
};

struct FOpenResult
{
	EOpenReturnCode ResultCode; //
	FVector2D DPI;				//dpi
	FVector2D RES;				//分辨率
	FString PatternFilePath;	//花型
	FString IconFilePath;		//花型
	void Reset()
	{
		ResultCode = E_ERROR;
		DPI = FVector2D::ZeroVector;
		RES = FVector2D::ZeroVector;
		PatternFilePath.Empty();
		IconFilePath.Empty();
	}
};

class IOpenFileOperator
{
public:
	virtual void OpenFile() = 0;//打开文件浏览
	virtual void OpenCamera();//打开文件浏览
	virtual bool IsFinish() = 0;//是否完成了本次操作
	virtual void GetOpenResultAndClean(FOpenResult&outResult) = 0;//获取操作结果,并清空结果

protected:
	bool CreateDir(const FString &inDirPath);
	FString ExtractFileFolder(const FString &inFilePath);
	bool DirIsExist(const FString &inDirPath);
};

