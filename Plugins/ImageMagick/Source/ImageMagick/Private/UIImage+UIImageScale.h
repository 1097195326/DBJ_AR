//
//  UIImage+UIImageScale.h
//  HMImagePickerManager
//
//  Created by 门皓 on 2018/1/4.
//  Copyright © 2018年 门皓. All rights reserved.
//
#pragma once
#if PLATFORM_IOS
#import <UIKit/UIKit.h>

@interface UIImage (UIImageScale)

+(UIImage*)image:(UIImage *)image scaleToSize:(CGSize)size;

+(UIImage *)imageFromImage:(UIImage *)image inRect:(CGRect)rect;
@end

#endif
