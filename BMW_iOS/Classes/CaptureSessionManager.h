//
//  CaptureSessionManager.h
//  BMW_iOS
//
//  Created by Aaron Sarnoff on 2/28/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#if TARGET_OS_IPHONE &&!TARGET_IPHONE_SIMULATOR
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#include <AssetsLibrary/AssetsLibrary.h>
#import <opencv/cv.h>

@class BMW_iOSViewController;

@interface CaptureSessionManager : NSObject <AVCaptureVideoDataOutputSampleBufferDelegate> {
	AVCaptureSession *captureSession;
	AVCaptureVideoPreviewLayer *previewLayer;
	AVAssetWriterInputPixelBufferAdaptor *pixelBufferAdaptor;
	AVAssetWriter *assetWriter;
	AVAssetWriterInput *assetWriterInput;
	NSURL *outputFileURL;
	BMW_iOSViewController *delegate;
}

- (void) addVideoPreviewLayer;
- (void) addVideoInput;
- (void) addVideoOutput;
- (NSURL *) fileURL;
- (void) startWriting;
- (void) finishWriting;
- (CGImageRef) imageFromSampleBuffer:(CMSampleBufferRef) sampleBuffer;
- (CVPixelBufferRef) pixelBufferFromCGImage: (CGImageRef) image;
- (CGImageRef) CGImageFromIplImage:(IplImage *)image;
- (IplImage *) CreateIplImageFromCGImage:(CGImageRef)imageRef;

@property (retain) AVCaptureVideoPreviewLayer *previewLayer;
@property (retain) AVCaptureSession *captureSession;
@property (assign) BMW_iOSViewController *delegate;

@end
#else
#import <Foundation/Foundation.h>
@interface CaptureSessionManager : NSObject
{
}
#endif
