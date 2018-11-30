#pragma once
#include "IOpenFileOperator.h"
class FAndroidOpenFileOperator : public IOpenFileOperator
{
public:
	static FAndroidOpenFileOperator *Get() 
	{
		static FAndroidOpenFileOperator *thisInst = new FAndroidOpenFileOperator;
		return thisInst;
	}
private:
	FAndroidOpenFileOperator();
	virtual ~FAndroidOpenFileOperator();
public://interface
	virtual void OpenFile() override;
	virtual void OpenCamera() override;
	virtual bool IsFinish();
	virtual void GetOpenResultAndClean(FOpenResult&outResult);
public:
	void SetPatternFileName(const FString &inFileName);
	void SetIconFileName(const FString &inFileName);
	void SetDPI(const FVector2D &inDPI);
	void SetRes(const FVector2D &inRes);
	void SetResultCode(EOpenReturnCode inCode);
	void SetReturn() { IsReturn = true; }
private:
	bool IsReturn;
	FOpenResult OpenResult;
};
