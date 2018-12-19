#pragma once

#include "IOpenFileOperator.h"
class FWindowsOpenFileOperator : public IOpenFileOperator
{
public:
	static FWindowsOpenFileOperator *Get()
	{
		static FWindowsOpenFileOperator *thisInst = new FWindowsOpenFileOperator;
		return thisInst;
	}
private:
	FWindowsOpenFileOperator();
	virtual ~FWindowsOpenFileOperator();
public://interface
	virtual void OpenFile() override;
	virtual bool IsFinish() override;
	virtual void GetOpenResultAndClean(FOpenResult&outResult) override;
private:
	bool isReturn;
	FOpenResult OpenResult;
};