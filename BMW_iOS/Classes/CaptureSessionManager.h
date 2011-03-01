//
//  CaptureSessionManager.h
//  BMW_iOS
//
//  Created by Aaron Sarnoff on 2/28/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#include <AssetsLibrary/AssetsLibrary.h>

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
- (NSURL *) tempFileURL;
- (void) startCapturing;
- (void) stopCapturing;

@property (retain) AVCaptureVideoPreviewLayer *previewLayer;
@property (retain) AVCaptureSession *captureSession;

@end
