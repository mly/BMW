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
@synthesize delegate;

#pragma mark SampleBufferDelegate

- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection {

	CVImageBufferRef pixelBuffer = CMSampleBufferGetImageBuffer( sampleBuffer );
	
	[delegate processNewCameraFrame:pixelBuffer];
}

- (IplImage *)CreateIplImageFromCGImage:(CGImageRef)imageRef {
	CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
	IplImage *iplimage = cvCreateImage(cvSize(CGImageGetWidth(imageRef), CGImageGetHeight(imageRef)), IPL_DEPTH_8U, 4);
	CGContextRef contextRef = CGBitmapContextCreate(iplimage->imageData, iplimage->width, iplimage->height,
													iplimage->depth, iplimage->widthStep,
													colorSpace, kCGImageAlphaPremultipliedLast|kCGBitmapByteOrderDefault);
	CGContextDrawImage(contextRef, CGRectMake(0, 0, CGImageGetWidth(imageRef), CGImageGetHeight(imageRef)), imageRef);
	CGContextRelease(contextRef);
	CGColorSpaceRelease(colorSpace);
	
	IplImage *ret = cvCreateImage(cvGetSize(iplimage), IPL_DEPTH_8U, 3);
	cvCvtColor(iplimage, ret, CV_RGBA2BGR);
	cvReleaseImage(&iplimage);
	
	return ret;
}

// NOTE You should convert color mode as RGB before passing to this function
- (CGImageRef)CGImageFromIplImage:(IplImage *)image {
	NSLog(@"IplImage (%d, %d) %d bits by %d channels, %d bytes/row %s", image->width, image->height, image->depth, image->nChannels, image->widthStep, image->channelSeq);
	
	CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
	NSData *data = [NSData dataWithBytes:image->imageData length:image->imageSize];
	CGDataProviderRef provider = CGDataProviderCreateWithCFData((CFDataRef)data);
	CGImageRef imageRef = CGImageCreate(image->width, image->height,
										image->depth, image->depth * image->nChannels, image->widthStep,
										colorSpace, kCGImageAlphaNone|kCGBitmapByteOrderDefault,
										provider, NULL, false, kCGRenderingIntentDefault);
	CGDataProviderRelease(provider);
	CGColorSpaceRelease(colorSpace);
	return imageRef;
}

- (CGImageRef) imageFromSampleBuffer:(CMSampleBufferRef) sampleBuffer // Create a CGImageRef from sample buffer data
{
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer); 
    CVPixelBufferLockBaseAddress(imageBuffer,0);        // Lock the image buffer 
	
    uint8_t *baseAddress = (uint8_t *)CVPixelBufferGetBaseAddressOfPlane(imageBuffer, 0);   // Get information of the image 
    size_t bytesPerRow = CVPixelBufferGetBytesPerRow(imageBuffer); 
    size_t width = CVPixelBufferGetWidth(imageBuffer); 
    size_t height = CVPixelBufferGetHeight(imageBuffer); 
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB(); 
	
    CGContextRef newContext = CGBitmapContextCreate(baseAddress, width, height, 8, bytesPerRow, colorSpace, kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedFirst); 
    CGImageRef newImage = CGBitmapContextCreateImage(newContext); 
    CGContextRelease(newContext); 
	
    CGColorSpaceRelease(colorSpace); 
    CVPixelBufferUnlockBaseAddress(imageBuffer,0); 
    /* CVBufferRelease(imageBuffer); */  // do not call this!
	
    return newImage;
}

- (CVPixelBufferRef) pixelBufferFromCGImage: (CGImageRef) image
{
	CGSize frameSize = CGSizeMake(CGImageGetWidth(image), CGImageGetHeight(image));
    NSDictionary *options = [NSDictionary dictionaryWithObjectsAndKeys:
							 [NSNumber numberWithBool:YES], kCVPixelBufferCGImageCompatibilityKey,
							 [NSNumber numberWithBool:YES], kCVPixelBufferCGBitmapContextCompatibilityKey,
							 nil];
    CVPixelBufferRef pxbuffer = NULL;
    CVReturn status = CVPixelBufferCreate(kCFAllocatorDefault, frameSize.width,
										  frameSize.height, kCVPixelFormatType_32ARGB, (CFDictionaryRef) options, 
										  &pxbuffer);
    NSParameterAssert(status == kCVReturnSuccess && pxbuffer != NULL);
	
    CVPixelBufferLockBaseAddress(pxbuffer, 0);
    void *pxdata = CVPixelBufferGetBaseAddress(pxbuffer);
    NSParameterAssert(pxdata != NULL);
	
    CGColorSpaceRef rgbColorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate(pxdata, frameSize.width,
												 frameSize.height, 8, 4*frameSize.width, rgbColorSpace, 
												 kCGImageAlphaNoneSkipFirst);
    NSParameterAssert(context);
#ifdef SCREEN_CAPTURE
	CGContextTranslateCTM(context,
						  +(frameSize.width/2),
						  +(frameSize.height/2));	
	CGContextRotateCTM(context, M_PI/2.0);
	CGContextTranslateCTM(context,
						  -(frameSize.height/2),
						  -(frameSize.width/2));
	CGContextDrawImage(context, CGRectMake(0, 0, CGImageGetHeight(image), CGImageGetWidth(image)), image);
#else	
	CGContextDrawImage(context, CGRectMake(0, 0, CGImageGetWidth(image), CGImageGetHeight(image)), image);
#endif
    CGColorSpaceRelease(rgbColorSpace);
    CGContextRelease(context);
	
    CVPixelBufferUnlockBaseAddress(pxbuffer, 0);
    return pxbuffer;
}
	
	
#pragma mark init/dealloc

- (id) init {
	
	if (!(self = [super init]))
		return nil;
	
	// Grab the back-facing camera
	AVCaptureDevice *camera = nil;
	NSArray *devices = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
	for (AVCaptureDevice *device in devices) 
	{
#ifdef USE_FRONT_CAMERA
		if ([device position] == AVCaptureDevicePositionFront) 
		{
			camera = device;
		} 
#else
		if ([device position] == AVCaptureDevicePositionBack) {
			camera = device;
		}
#endif
		
	}
	
	// Create the capture session
	self.captureSession = [[AVCaptureSession alloc] init];
	
	// Add the video input	
	NSError *error = nil;
	AVCaptureDeviceInput *videoInput = [[AVCaptureDeviceInput alloc] initWithDevice:camera error:&error];
	if ([captureSession canAddInput:videoInput]) 
		[captureSession addInput:videoInput];
	[videoInput release];
	
	// Add the video frame output	
	AVCaptureVideoDataOutput *videoOutput = [[AVCaptureVideoDataOutput alloc] init];
	[videoOutput setAlwaysDiscardsLateVideoFrames:YES];
	// Use RGB frames instead of YUV to ease color processing
	[videoOutput setVideoSettings:[NSDictionary dictionaryWithObject:[NSNumber numberWithInt:kCVPixelFormatType_32BGRA] forKey:(id)kCVPixelBufferPixelFormatTypeKey]];
	
	[videoOutput setSampleBufferDelegate:self queue:dispatch_get_main_queue()];
	
	if ([captureSession canAddOutput:videoOutput])
		[captureSession addOutput:videoOutput];
	else
		NSLog(@"Couldn't add video output");
	[videoOutput release];
	
	// Start capturing
	//[captureSession setSessionPreset:AVCaptureSessionPresetHigh];
	[captureSession setSessionPreset:AVCaptureSessionPreset640x480];
	if (![captureSession isRunning])
	{
		[captureSession startRunning];
	};
	
	return self;
}


- (void)dealloc {
	[self.captureSession release];
	
	[super dealloc];
}
@end
