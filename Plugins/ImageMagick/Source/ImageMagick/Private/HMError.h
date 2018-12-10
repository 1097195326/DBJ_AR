//
//  HMError.h
//  HMImagePickerManager
//
//  Created by 门皓 on 2018/1/4.
//  Copyright © 2018年 门皓. All rights reserved.
//
#pragma once
#if PLATFORM_IOS
#import <Foundation/Foundation.h>

@interface HMError : NSObject

@property (copy, nonatomic) NSString *errorDes;

@end
#endif
