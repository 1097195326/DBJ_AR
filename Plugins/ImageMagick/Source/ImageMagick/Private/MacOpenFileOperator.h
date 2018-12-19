#pragma once
#include "IOpenFileOperator.h"
class FMacOpenFileOperator : public IOpenFileOperator
{
public:
    static FMacOpenFileOperator *Get()
    {
        static FMacOpenFileOperator *thisInst = new FMacOpenFileOperator;
        return thisInst;
    }
private:
    FMacOpenFileOperator();
    virtual ~FMacOpenFileOperator();
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
private:
    bool IsReturn;
    FOpenResult OpenResult;
};

