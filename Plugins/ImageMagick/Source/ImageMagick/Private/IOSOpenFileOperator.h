#pragma once
#include "IOpenFileOperator.h"
class FIOSOpenFileOperator : public IOpenFileOperator
{
public:
	static FIOSOpenFileOperator *Get()
	{
		static FIOSOpenFileOperator *thisInst = new FIOSOpenFileOperator;
		return thisInst;
	}
private:
	FIOSOpenFileOperator();
	virtual ~FIOSOpenFileOperator();
public://interface
	virtual void OpenFile() override;
	virtual bool IsFinish();
	virtual void GetOpenResultAndClean(FOpenResult&outResult);
public:
	void SetFileName(const FString &inFileName);
	void SetDPI(const FVector2D &inDPI);
	void SetRes(const FVector2D &inRes);
	void SetResultCode(EOpenReturnCode inCode);
	void SetReturn() { IsReturn = true; }
    void SetPatternFileName(const FString &inFileName);
    void SetIconFileName(const FString &inFileName);
private:
	bool IsReturn;
	FOpenResult OpenResult;
};
