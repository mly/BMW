//
//  CaptureSessionManager.m
//  BMW_iOS
//
//  Created by Aaron Sarnoff on 2/28/11.
//  Copyright 2011 Stanford University. All rights reserved.
//

#import "CaptureSessionManager.h"


@implementation CaptureSessionManager
@synthesize captureSession;
@synthesize previewLayer;
static int64_t frameNumber = 0;

#pragma mark SampleBufferDelegate

- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection {

	CVImageBufferRef pixelBuffer = CMSampleBufferGetImageBuffer( sampleBuffer );
	
#if VIDEO_SAVE
	//save to video
    if(assetWriterInput.readyForMoreMediaData)
        [pixelBufferAdaptor appendPixelBuffer:pixelBuffer
                         withPresentationTime:CMTimeMake(frameNumber, 25)];
    frameNumber++;
	
#endif
	//Do image processing here
}

#pragma mark Capture Session Configuration

- (void) addVideoPreviewLayer {
	self.previewLayer = [[AVCaptureVideoPreviewLayer alloc] initWithSession:self.captureSession];
	self.previewLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
}


- (void) addVideoInput {
	
	AVCaptureDevice *videoDevice = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];	
	if ( videoDevice ) {
		
		NSError *error;
		AVCaptureDeviceInput *videoIn = [AVCaptureDeviceInput deviceInputWithDevice:videoDevice error:&error];
		if ( !error ) {
			if ([self.captureSession canAddInput:videoIn])
				[self.captureSession addInput:videoIn];
			else
				NSLog(@"Couldn't add video input");		
		}
		else
			NSLog(@"Couldn't create video input");
	}
	else
		NSLog(@"Couldn't create video capture device");
}

- (void) addVideoOutput {
	//video output
	AVCaptureVideoDataOutput *videoOut = [[AVCaptureVideoDataOutput alloc] init];
	[videoOut setAlwaysDiscardsLateVideoFrames:YES];
	[videoOut setVideoSettings:[NSDictionary dictionaryWithObject:[NSNumber numberWithInt:kCVPixelFormatType_32BGRA] forKey:(id)kCVPixelBufferPixelFormatTypeKey]]; // BGRA is necessary for manual preview
	dispatch_queue_t my_queue = dispatch_queue_create("BMW.VideoOutput", NULL);
	[videoOut setSampleBufferDelegate:self queue:my_queue];
	if ([self.captureSession canAddOutput:videoOut])
		[self.captureSession addOutput:videoOut];
	else
		NSLog(@"Couldn't add video output");
	[videoOut release];
#if VIDEO_SAVE
	//Asset writing (saving the video)
	NSDictionary *outputSettings =
    [NSDictionary dictionaryWithObjectsAndKeys:
	 
	 [NSNumber numberWithInt:1280], AVVideoWidthKey,
	 [NSNumber numberWithInt:720], AVVideoHeightKey,
	 AVVideoCodecH264, AVVideoCodecKey,
	 
	 nil];
	assetWriterInput = [AVAssetWriterInput 
											assetWriterInputWithMediaType:AVMediaTypeVideo
											outputSettings:outputSettings];
	pixelBufferAdaptor =
	[[AVAssetWriterInputPixelBufferAdaptor alloc] 
	 initWithAssetWriterInput:assetWriterInput 
	 sourcePixelBufferAttributes:
	 [NSDictionary dictionaryWithObjectsAndKeys:
	  [NSNumber numberWithInt:kCVPixelFormatType_32BGRA], 
	  kCVPixelBufferPixelFormatTypeKey,
	  nil]];
	outputFileURL = [self tempFileURL];
	assetWriter = [[AVAssetWriter alloc]
								  initWithURL:outputFileURL
								  fileType:AVFileTypeMPEG4
								  error:nil];
	[assetWriter addInput:assetWriterInput];
	assetWriterInput.expectsMediaDataInRealTime = YES;
#endif
}

- (void) startCapturing
{
#if VIDEO_SAVE
	[assetWriter startWriting];
	[assetWriter startSessionAtSourceTime:kCMTimeZero];
	//[self performSelector:@selector(stopCapturing)];
	//[self performSelector:@selector(stopCapturing) withObject:nil afterDelay:5];
#endif
	[captureSession startRunning];
}

- (void) stopCapturing
{
	[captureSession stopRunning];
#if VIDEO_SAVE
	[assetWriter finishWriting];
	ALAssetsLibrary *library = [[ALAssetsLibrary alloc] init];
    if ([library videoAtPathIsCompatibleWithSavedPhotosAlbum:outputFileURL]) {
        [library writeVideoAtPathToSavedPhotosAlbum:outputFileURL
                                    completionBlock:nil];
	}
#endif
}

- (NSURL *) tempFileURL
{
	NSString *outputPath = [[NSString alloc] initWithFormat:@"%@%@", NSTemporaryDirectory(), @"camera.mov"];
	NSURL *outputURL = [[NSURL alloc] initFileURLWithPath:outputPath];
	NSFileManager *fileManager = [NSFileManager defaultManager];
	if ([fileManager fileExistsAtPath:outputPath]) {
		[[NSFileManager defaultManager] removeItemAtPath:outputPath error:nil];
		[outputPath release];
	}
	return [outputURL autorelease];
}
	
	
#pragma mark init/dealloc

- (id) init {
	
	if (self = [super init]) {
		self.captureSession = [[AVCaptureSession alloc] init];
		self.captureSession.sessionPreset = AVCaptureSessionPresetHigh;
		
	}
	
	return self;
}


- (void)dealloc {
	[self stopCapturing];
	
	 [self.previewLayer release];
	[self.captureSession release];
	
	[super dealloc];
}

@end
