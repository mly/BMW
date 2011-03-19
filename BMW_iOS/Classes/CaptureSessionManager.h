//
//  CaptureSessionManager.h
//  BMW_iOS
//
//  Created by Aaron Sarnoff on 2/28/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <opencv/cv.h>

@protocol ImageProcessingCameraDelegate;

@interface CaptureSessionManager : NSObject <AVCaptureVideoDataOutputSampleBufferDelegate> {
	AVCaptureSession *captureSession;
	
	AVAssetWriterInputPixelBufferAdaptor *pixelBufferAdaptor;
	AVAssetWriter *assetWriter;
	AVAssetWriterInput *assetWriterInput;
	
	NSURL *outputFileURL;
}

- (NSURL *) fileURL;
- (void) startWriting;
- (void) finishWriting;
- (CGImageRef) imageFromSampleBuffer:(CMSampleBufferRef) sampleBuffer;
- (CVPixelBufferRef) pixelBufferFromCGImage: (CGImageRef) image;
- (CGImageRef) CGImageFromIplImage:(IplImage *)image;
- (IplImage *) CreateIplImageFromCGImage:(CGImageRef)imageRef;

@property (retain) AVCaptureSession *captureSession;
@property(nonatomic, assign) id<ImageProcessingCameraDelegate> delegate;
@end

@protocol ImageProcessingCameraDelegate
- (void)cameraHasConnected;
- (void)processNewCameraFrame:(CVImageBufferRef)cameraFrame;
@end