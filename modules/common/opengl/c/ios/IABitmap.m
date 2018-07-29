//
//  IABitmap.m
//  OpenGL
//
//  Created by Konstantin Merker on 05.06.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#import <UIKit/UIKit.h>
#include "IALibrary.h"
#include "IAOpenGLHeaders.h"
#include "IABitmap+Native.h"

#include "IAMath.h"

#include "IALogger.h"
#include "IAOpenGLAssert.h"

#define CLASSNAME "IABitmap - NativeIOS"


void * IABitmap_nativeCreateRefFromAsset(const char * assetName){
    NSString * imageName =[NSString stringWithUTF8String:assetName];
    NSString * file = [[NSBundle mainBundle] pathForResource:imageName ofType:nil];
    UIImage * image = [[UIImage alloc] initWithContentsOfFile:file];
    return image;
}

static void IABitmap_releaseDataCallback(void *info, const void *data, size_t size){
    IA_free((void *) data);
}

void * IABitmap_nativeCreateRefFromScreen(int x, int y, int width, int height){
    NSInteger myDataLength = width * height * 4;
    GLubyte * buffer = (GLubyte *) IA_malloc(myDataLength);
    
    glAssert();
    glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glAssert();
    
    GLubyte * buffer2 = (GLubyte *) IA_malloc(myDataLength);
    
    for(int i_y = 0; i_y < height; i_y++){
        for(int i_x = 0; i_x < width * 4; i_x++){
            buffer2[(height - 1 - i_y) * width * 4 + i_x] = buffer[i_y * 4 * width + i_x];
        }
    }
    
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, buffer2, myDataLength, IABitmap_releaseDataCallback);
    
    int bitsPerComponent = 8;
    int bitsPerPixel = 32;
    int bytesPerRow = 4 * width;
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
    
    CGImageRef imageRef = CGImageCreate(width, height, bitsPerComponent, bitsPerPixel, bytesPerRow, colorSpaceRef, bitmapInfo, provider, NULL, NO, renderingIntent);
    
    UIImage * myImage = [[UIImage alloc] initWithCGImage:imageRef];
    
    CGImageRelease(imageRef);
    CGColorSpaceRelease(colorSpaceRef);
    CGDataProviderRelease(provider);
    
    IA_free(buffer);
    
    return myImage;
}

IASize IABitmap_nativeGetSourceSize(void * bitmapRef){
    UIImage * image = (UIImage *) bitmapRef;
    CGImageRef spriteImage = image.CGImage;
    IASize result;
    result.width = CGImageGetWidth(spriteImage);
    result.height = CGImageGetHeight(spriteImage);
    return result;
}

void IABitmap_nativeBind(void * bitmapRef){
    UIImage * image = (UIImage *) bitmapRef;
    
    CGImageRef spriteImage = image.CGImage;
    
    int width = (int) CGImageGetWidth(spriteImage);
    int height = (int) CGImageGetHeight(spriteImage);
    
    int bytesPerPixel = 4;
    int bytesPerRow = bytesPerPixel * width;
    int bitsPerComponent = 8;
    int spriteDataLength = bytesPerRow * height;
    
    GLubyte * spriteData = IA_calloc(spriteDataLength, sizeof(GLubyte));
    
    CGColorSpaceRef colorSpace = CGImageGetColorSpace(spriteImage);
    
    CGContextRef spriteContext = CGBitmapContextCreate(spriteData, width, height, bitsPerComponent, bytesPerRow, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    
    CGContextDrawImage(spriteContext, CGRectMake(0, 0, width, height), spriteImage);
    
    CGContextRelease(spriteContext);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    if (IAMath_isPow2(width) == false || IAMath_isPow2(height) == false) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, spriteData);
    
    IA_free(spriteData);
    
    glAssert();
}

void IABitmap_nativeDestroyBitmapRef(void * bitmapRef){
    UIImage * image = (UIImage *) bitmapRef;
    [image release];
}

