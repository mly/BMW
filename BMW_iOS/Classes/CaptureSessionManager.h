//
//  CaptureSessionManager.h
//  BMW_iOS
//
//  Created by Aaron Sarnoff on 2/28/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#if TARGET_OS_IPHONE
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#include <AssetsLibrary/AssetsLibrary.h>
#import <opencv/cv.h>

@interface CaptureSessionManager : NSObject <AVCaptureVideoDataOutputSampleBufferDelegate> {
	AVCaptureSession *captureSession;
	AVCaptureVideoPreviewLayer *previewLayer;
	AVAssetWriterInputPixelBufferAdaptor *pixelBufferAdaptor;
	AVAssetWriter *assetWriter;
	AVAssetWriterInput *assetWriterInput;
	NSURL *outputFileURL;
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

@end
#else
#import <Foundation/Foundation.h>
@interface CaptureSessionManager : NSObject
{
}
#endif
