// Fill out your copyright notice in the Description page of Project Settings.

#include "IOSOpenFileOperator.h"
#if PLATFORM_IOS
#include <Magick++.h>
#include "HMImagePickerManager.h"
#endif
#include "ImageMagick.h"
#include "Engine/Engine.h"
#include "ImageMagickBPLibrary.h"

FIOSOpenFileOperator::FIOSOpenFileOperator() :
IsReturn(false)
{
    
}

void FIOSOpenFileOperator::SetPatternFileName(const FString &inFileName)
{
    OpenResult.PatternFilePath = inFileName;
}
void FIOSOpenFileOperator::SetIconFileName(const FString &inFileName)
{
    OpenResult.IconFilePath = inFileName;
}

void FIOSOpenFileOperator::OpenFile()
{
    IsReturn = false;
#if PLATFORM_IOS
    dispatch_async(dispatch_get_main_queue(),^ {
        UIViewController *rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
        
        //调用静态库方法  其中返回选中的图片  并返回其本地路径.
        [[HMImagePickerManager defaultManager] imagePickerWithController:rootViewController scaledToSizeWithWidth:212 height:212 imagePickerBlock:^(UIImage *image, UIImage *icon, NSString *imagePath, NSString *iconPath)
         {
             std::string mPath = [imagePath UTF8String];
             
             UE_LOG(ImageMagick, Error, TEXT("选取照片: %s"), UTF8_TO_TCHAR([imagePath UTF8String]));
             
             NSFileManager *fm=[NSFileManager defaultManager];
             
             BOOL isExist = [fm fileExistsAtPath : imagePath];
             if(isExist)
             {
                 UE_LOG(ImageMagick, Error, TEXT("选择照片存在路径 %s"), UTF8_TO_TCHAR([imagePath UTF8String]));
             }
             else
             {
                 UE_LOG(ImageMagick, Error, TEXT("选择照片路径不存在 %s"), UTF8_TO_TCHAR([imagePath UTF8String]));
                 return;
             }
             
             
             // 查询dpi.
             Magick::Image inputImage( mPath);
             
             float _X = inputImage.density().x();
             float _Y = inputImage.density().y();
             float nowWidth = inputImage.size().width();
             float nowHeight = inputImage.size().height();
             
             UE_LOG(ImageMagick, Error, TEXT("选择照片路径dpi %f,%f"), _X,_Y);
             
             FIOSOpenFileOperator::Get()->SetDPI(FVector2D(_X, _Y));// TODO
             
             FIOSOpenFileOperator::Get()->SetRes(FVector2D(nowWidth, nowHeight));
             
             FIOSOpenFileOperator::Get()->SetPatternFileName(UTF8_TO_TCHAR([imagePath UTF8String]));
             
             FIOSOpenFileOperator::Get()->SetIconFileName(UTF8_TO_TCHAR([iconPath UTF8String]));
             
             FIOSOpenFileOperator::Get()->SetResultCode(E_OK);
             
             FIOSOpenFileOperator::Get()->SetReturn();
             
             UE_LOG(ImageMagick, Error, TEXT("生成icon"));
         }
         Error:^(HMError *error)
        {
             FString mPatternFile = TEXT("");
             
             FString mIconFile = TEXT("");
             
             FIOSOpenFileOperator::Get()->SetDPI(FVector2D(0.0f, 0.0f));// TODO
             
             FIOSOpenFileOperator::Get()->SetRes(FVector2D(0.0f, 0.0f));
             
             FIOSOpenFileOperator::Get()->SetPatternFileName(mPatternFile);
             
             FIOSOpenFileOperator::Get()->SetIconFileName(mIconFile);
             
             FIOSOpenFileOperator::Get()->SetResultCode(E_CANCEL);
             
             FIOSOpenFileOperator::Get()->SetReturn();
         }];
        
    } );
#endif
    
}

bool FIOSOpenFileOperator::IsFinish()
{
    return IsReturn;
}

void FIOSOpenFileOperator::GetOpenResultAndClean(FOpenResult&outResult)
{
    outResult = OpenResult;
    OpenResult.Reset();
    IsReturn  = false;
}

void FIOSOpenFileOperator::SetFileName(const FString &inFileName)
{
    OpenResult.PatternFilePath = inFileName;
}

void FIOSOpenFileOperator::SetDPI(const FVector2D &inDPI)
{
    OpenResult.DPI = inDPI;
}

void FIOSOpenFileOperator::SetRes(const FVector2D &inRes)
{
    OpenResult.RES = inRes;
}

void FIOSOpenFileOperator::SetResultCode(EOpenReturnCode inCode)
{
    OpenResult.ResultCode = inCode;
}

FIOSOpenFileOperator::~FIOSOpenFileOperator()
{
}

