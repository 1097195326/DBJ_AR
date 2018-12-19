// Fill out your copyright notice in the Description page of Project Settings.

#include "MacOpenFileOperator.h"
#if PLATFORM_MAC
#include <Magick++.h>
#include "Runtime/Core/Public/Misc/Paths.h"
//#include "OpenFileDialogLib.h"
#include "CocoaThread.h"
#endif

FMacOpenFileOperator::FMacOpenFileOperator() :
IsReturn(false)
{
    
}

void FMacOpenFileOperator::OpenFile()
{
#if PLATFORM_MAC
    
    bool ret = false;
    
    const char* DialogTitle = "选择花型";
    const char* DefaultPath = TCHAR_TO_UTF8(*FPaths::GameDir());
    const char* FileTypes = "JPG\0*.JPG\0PNG\0*.PNG\0";//由于\0是字符串结尾标识，所以不能当作参数传入，WTF.
    std::string TargetFile;

    __block const char * _path;
    
    //通知主线程刷新.
//    ret = MainThreadReturn({
//
////        bool bresult = OpenOnMacFilePath(DialogTitle,DefaultPath,DefaultPath,FileTypes,&_path);
//
//        return true;//bresult;
//    });
    
    if (!ret)
    {
        FMacOpenFileOperator::Get()->SetResultCode(E_CANCEL);
        return;
    }
    
//    TargetFile = _path;
//
//    FMacOpenFileOperator::Get()->SetResultCode(E_OK);
//
//    // 查询dpi.
//    Magick::Image inputImage( TargetFile);
//
//    float _X = inputImage.density().x();
//    float _Y = inputImage.density().y();
//    float nowWidth = inputImage.size().width();
//    float nowHeight = inputImage.size().height();
//
//    FMacOpenFileOperator::Get()->SetRes(FVector2D(_X, _Y));// TODO
//
//    FMacOpenFileOperator::Get()->SetDPI(FVector2D(nowWidth, nowHeight));
//
//    FMacOpenFileOperator::Get()->SetFileName(UTF8_TO_TCHAR(_path));
//
//    FMacOpenFileOperator::Get()->SetReturn();
    
#endif
    
}

bool FMacOpenFileOperator::IsFinish()
{
    return IsReturn;
}

void FMacOpenFileOperator::GetOpenResultAndClean(FOpenResult&outResult)
{
    outResult = OpenResult;
    OpenResult.Reset();
}

void FMacOpenFileOperator::SetFileName(const FString &inFileName)
{
    OpenResult.PatternFilePath = inFileName;
}

void FMacOpenFileOperator::SetDPI(const FVector2D &inDPI)
{
    OpenResult.DPI = inDPI;
}

void FMacOpenFileOperator::SetRes(const FVector2D &inRes)
{
    OpenResult.RES = inRes;
}

void FMacOpenFileOperator::SetResultCode(EOpenReturnCode inCode)
{
    OpenResult.ResultCode = inCode;
}

FMacOpenFileOperator::~FMacOpenFileOperator()
{
}


