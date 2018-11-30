//
//  HMImagePicker.m
//  HMImagePicker
//
//  Created by 门皓 on 2017/11/28.
//  Copyright © 2017年 门皓. All rights reserved.
//

#include "HMImagePickerManager.h"
#if PLATFORM_IOS
#import "HMImagePicker.h"
#import "UIImage+UIImageScale.h"

typedef void(^ImagePickerBlock)(UIImage * image);

@interface HMImagePickerManager()

@property (strong, nonatomic) HMImagePicker *imagePicker;

@property (copy, nonatomic) ImagePickerBlock block;

@end

@implementation HMImagePickerManager

+ (instancetype)defaultManager
{
    static HMImagePickerManager* imagePickerManager = nil;
    
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        imagePickerManager = [HMImagePickerManager new];
    });
    
    return imagePickerManager;
}

- (instancetype)init
{
    self = [super init];
    if (self)
    {
        
    }
    return self;
}


- (void)imagePickerWithController:(id)vc scaledToSizeWithWidth:(CGFloat)width height:(CGFloat)height imagePickerBlock:(void(^)(UIImage *image,UIImage *icon, NSString *imagePath, NSString *iconPath))callBack Error:(void(^)(HMError *error))errorCallBack
{
    self.imagePicker = [HMImagePicker new];
    
    [self.imagePicker  imagepickerWithController:vc];
    
    self.imagePicker.callback = ^(UIImage *image) {
        if (callBack)
        {
            UIImage *icon = [self imageWithImageSimple:image scaledToSizeWithWidth:width height:height];
            
            NSArray *array = [self ssaveImageWtihImage:image andIconImage:icon];
            
            callBack(image,icon,[array firstObject],[array lastObject]);
        }
    };
    
    self.imagePicker.errorCallback = ^{
        
        HMError *error = [HMError new];
        
        error.errorDes = @"取消图片选择";
        
        errorCallBack(error);
        
    };
}


- (UIImage*)imageWithImageSimple:(UIImage*)image scaledToSizeWithWidth:(CGFloat)width height:(CGFloat)height
{
    CGSize newSize = CGSizeMake(width, height);
    
    if (image.size.width >= image.size.height)
    {
        newSize = CGSizeMake((height * image.size.width) / image.size.height, height);
    }
    else
    {
        newSize = CGSizeMake(width, (width * image.size.height) / image.size.width);
    }
    
    //    UIImage *newImage = [self scaleImage:image toScaleSize:newSize];
    
    //    UIImage *newImage = ;
    
    return [UIImage imageFromImage:[self image:image scaleToSize:newSize] inRect:CGRectMake([self image:image scaleToSize:newSize].size.width / 2 - (width / 2), [self image:image scaleToSize:newSize].size.height / 2 - (height / 2), width, height)];
    
}

- (UIImage*)image:(UIImage *)image scaleToSize:(CGSize)size
{
    
    // 得到图片上下文，指定绘制范围
    UIGraphicsBeginImageContext(size);
    
    // 将图片按照指定大小绘制
    [image drawInRect:CGRectMake(0, 0, size.width, size.height)];
    
    // 从当前图片上下文中导出图片
    UIImage* scaledImage = UIGraphicsGetImageFromCurrentImageContext();
    
    // 当前图片上下文出栈
    UIGraphicsEndImageContext();
    
    // 返回新的改变大小后的图片
    return scaledImage;
}


- (NSArray *)ssaveImageWtihImage:(UIImage *)image andIconImage:(UIImage *)icon
{
    NSArray*paths=NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask,YES);
    
    NSString *documentsDirectory=[paths objectAtIndex:0];
    
    NSLog(@"%@",UIImageJPEGRepresentation(image, 1.0));
    
    NSString *savedImagePath=[documentsDirectory stringByAppendingPathComponent:[NSString stringWithFormat:@"saveImage.%@",((UIImageJPEGRepresentation(image, 0.5)==nil) ? @"png" : @"jpg")]];
    
    NSString *savedIconPath=[documentsDirectory stringByAppendingPathComponent:[NSString stringWithFormat:@"saveIcon.%@",((UIImageJPEGRepresentation(icon,0.5)==nil) ? @"png" : @"jpg")]];
    
    NSLog(@"path:%@",savedImagePath);
    
    NSLog(@"iconPath:%@",savedIconPath);
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    
    
    [fileManager removeItemAtPath:savedImagePath error:nil];
    
    [fileManager removeItemAtPath:savedIconPath error:nil];
    
    NSData *imagedata;
    
    NSMutableArray *array = [NSMutableArray array];
    
    [array addObject:image];
    
    [array addObject:icon];
    
    for (NSInteger index = 0; index < array.count; index++)
    {
        UIImage *image = array[index];
        
        if ( UIImageJPEGRepresentation(image, 0.5) != nil)
        {
            imagedata = UIImageJPEGRepresentation(image, 0.5);
            
        }else{
            imagedata=UIImagePNGRepresentation(image);
        }
        if (index)
        {
            if ([imagedata writeToFile:savedIconPath atomically:YES]) {
                [array replaceObjectAtIndex:index withObject:savedIconPath];
            }
        }
        else
        {
            if ([imagedata writeToFile:savedImagePath atomically:YES]) {
                [array replaceObjectAtIndex:index withObject:savedImagePath];
            }
        }
    }
    
    return array;
}

@end

#endif
