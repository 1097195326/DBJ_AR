//
//  OpenFileDialogLib.h
//  OpenFileDialogLib
//
//  Created by jo on 2017/9/15.
//  Copyright © 2017年 jo. All rights reserved.
//


//#define PLATFORM_WINDOWS 0

#if PLATFORM_MAC
// Set up compiler pragmas, etc
#include "Mac/MacPlatformCompilerSetup.h"

#define FVector FVectorWorkaround
#ifdef __OBJC__
#import <Cocoa/Cocoa.h>
#endif
// SIMD intrinsics
#include <xmmintrin.h>

@interface OpenFileDialogLib : NSObject

+(bool) OpenFileDialogTool:(NSString*)_dialogTitle DefaultPath:(NSString*) _defaultPath DefaultFile:(NSString*) _defaultFile FileTypes:(NSString*) _fileTypes OutPutPath:(NSString**) _outPutPath;
@end

#endif


bool OpenOnMacFilePath(const char * _dialogTitle,const char * _defaultPath,const char * _defaultFile,const char * _fileTypes,const char ** outPutPath)
{
#if PLATFORM_MAC
    NSString* path;
    bool ret = [OpenFileDialogLib OpenFileDialogTool:[NSString stringWithFormat:@"%s",_dialogTitle] DefaultPath:[NSString stringWithFormat:@"%s",_defaultPath] DefaultFile:[NSString stringWithFormat:@"%s",_defaultFile] FileTypes:[NSString stringWithFormat:@"%s",_fileTypes] OutPutPath:&path];
    
    const char * cPath = [path UTF8String];
    
    *outPutPath = cPath;
    
    return ret;
#endif
}
