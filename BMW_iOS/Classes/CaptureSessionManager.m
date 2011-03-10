//
//  CaptureSessionManager.m
//  BMW_iOS
//
//  Created by Aaron Sarnoff on 2/28/11.
//  Copyright 2011 Stanford University. All rights reserved.
//
#if TARGET_OS_IPHONE &&!TARGET_IPHONE_SIMULATOR
#import "CaptureSessionManager.h"

@implementation CaptureSessionManager
@synthesize captureSession;
@synthesize previewLayer;
@synthesize delegate;
static int64_t frameNumber = 0;

#pragma mark SampleBufferDelegate

- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection {

	CVImageBufferRef pixelBuffer = CMSampleBufferGetImageBuffer( sampleBuffer );
	CGImageRef imageRef = [self imageFromSampleBuffer:sampleBuffer];
#if VIDEO_SAVE
	//save to video
    if(assetWriterInput.readyForMoreMediaData)
        [pixelBufferAdaptor appendPixelBuffer:pixelBuffer
                         withPresentationTime:CMTimeMake(frameNumber, 25)];
    frameNumber++;
	
#endif
#ifdef SCREEN_CAPTURE
	//screen capture
	//UIGetScreenImage()
    if(assetWriterInput.readyForMoreMediaData)
	{
		CVPixelBufferRef pixelBuffer2 = [self pixelBufferFromCGImage:UIGetScreenImage()];
		[pixelBufferAdaptor appendPixelBuffer:pixelBuffer2
							 withPresentationTime:CMTimeMake(frameNumber, 25)];
		CVPixelBufferRelease(pixelBuffer2);

	}
    frameNumber++;
	
#endif
	//Do image processing here
#ifdef OPEN_CV
#if EDGE_DETECTION
	cvSetErrMode(CV_ErrModeParent);
	
	// Create grayscale IplImage from UIImage
	IplImage *img_color = [self CreateIplImageFromCGImage:imageRef];
	IplImage *img = cvCreateImage(cvGetSize(img_color), IPL_DEPTH_8U, 1);
	cvCvtColor(img_color, img, CV_BGR2GRAY);
	cvReleaseImage(&img_color);
	
	// Detect edge
	IplImage *img2 = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	cvCanny(img, img2, 64, 128, 3);
	cvReleaseImage(&img);
	
	// Convert black and whilte to 24bit image then convert to UIImage to show
	IplImage *image = cvCreateImage(cvGetSize(img2), IPL_DEPTH_8U, 3);
	for(int y=0; y<img2->height; y++) {
		for(int x=0; x<img2->width; x++) {
			char *p = image->imageData + y * image->widthStep + x * 3;
			*p = *(p+1) = *(p+2) = img2->imageData[y * img2->widthStep + x];
		}
	}
	cvReleaseImage(&img2);
	
	CGImageRef output = [self CGImageFromIplImage:image];
	cvReleaseImage(&image);
	CVPixelBufferRef pixelBuffer2 = [self pixelBufferFromCGImage:output];
	if(assetWriterInput.readyForMoreMediaData)
	{
		[pixelBufferAdaptor appendPixelBuffer:pixelBuffer2
						 withPresentationTime:CMTimeMake(frameNumber, 25)];
	}
    frameNumber++;
	CVPixelBufferRelease(pixelBuffer2);
#endif
#if FACE_DETECTION
	cvSetErrMode(CV_ErrModeParent);
	
	IplImage *image = [self CreateIplImageFromCGImage:imageRef];
	
	// Scaling down
	IplImage *small_image = cvCreateImage(cvSize(CGImageGetWidth(imageRef)/2,CGImageGetHeight(imageRef)/2), IPL_DEPTH_8U, 3);
	cvPyrDown(image, small_image, CV_GAUSSIAN_5x5);
	int scale = 2;
	
	// Load XML
	NSString *path = [[NSBundle mainBundle] pathForResource:@"haarcascade_frontalface_default" ofType:@"xml"];
	CvHaarClassifierCascade* cascade = (CvHaarClassifierCascade*)cvLoad([path cStringUsingEncoding:NSASCIIStringEncoding], NULL, NULL, NULL);
	CvMemStorage* storage = cvCreateMemStorage(0);
	
	// Detect faces and draw rectangle on them
	CvSeq* faces = cvHaarDetectObjects(small_image, cascade, storage, 1.2f, 2, CV_HAAR_DO_CANNY_PRUNING, cvSize(20, 20));
	cvReleaseImage(&small_image);
	
	// Create canvas to show the results
	CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
	CGContextRef contextRef = CGBitmapContextCreate(NULL, CGImageGetWidth(imageRef), CGImageGetHeight(imageRef),
													8, CGImageGetWidth(imageRef) * 4,
													colorSpace, kCGImageAlphaPremultipliedLast|kCGBitmapByteOrderDefault);
	CGContextDrawImage(contextRef, CGRectMake(0, 0, CGImageGetWidth(imageRef), CGImageGetHeight(imageRef)), imageRef);
	
	CGContextSetLineWidth(contextRef, 4);
	CGContextSetRGBStrokeColor(contextRef, 0.0, 0.0, 1.0, 0.5);
	
	// Draw results on the iamge
	for(int i = 0; i < faces->total; i++) {
		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
		
		// Calc the rect of faces
		CvRect cvrect = *(CvRect*)cvGetSeqElem(faces, i);
		CGRect face_rect = CGContextConvertRectToDeviceSpace(contextRef, CGRectMake(cvrect.x * scale, cvrect.y * scale, cvrect.width * scale, cvrect.height * scale));
		
		CGContextStrokeRect(contextRef, face_rect);
		
		[pool release];
	}
	
	CGImageRef output = CGBitmapContextCreateImage(contextRef);
	CGContextRelease(contextRef);
	CGColorSpaceRelease(colorSpace);
	
	cvReleaseMemStorage(&storage);
	cvReleaseHaarClassifierCascade(&cascade);
	
	CVPixelBufferRef pixelBuffer2 = [self pixelBufferFromCGImage:output];
	if(assetWriterInput.readyForMoreMediaData)
	{
		[pixelBufferAdaptor appendPixelBuffer:pixelBuffer2
						 withPresentationTime:CMTimeMake(frameNumber, 25)];
	}
    frameNumber++;
	CVPixelBufferRelease(pixelBuffer2);
#endif
#if RENDER_PROCESSING
	[delegate setProcessedImage:output];
#endif
	CGImageRelease(output);
#endif
	CGImageRelease(imageRef);
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
}

- (void) assetWriterStart
{
	//Asset writing (saving the video)
	NSDictionary *outputSettings =
    [NSDictionary dictionaryWithObjectsAndKeys:
	 [NSNumber numberWithInt:640], AVVideoWidthKey,
	 [NSNumber numberWithInt:480], AVVideoHeightKey,
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
	outputFileURL = [self fileURL];
	assetWriter = [[AVAssetWriter alloc]
				   initWithURL:outputFileURL
				   fileType:AVFileTypeMPEG4
				   error:nil];
	[assetWriter addInput:assetWriterInput];
	assetWriterInput.expectsMediaDataInRealTime = YES;
	
	[assetWriter startWriting];
	[assetWriter startSessionAtSourceTime:kCMTimeZero];
}

- (void) startWriting
{
#ifdef SCREEN_CAPTURE
	[self assetWriterStart];
#endif
#ifdef OPEN_CV
	[self assetWriterStart];
#endif
#if VIDEO_SAVE
	[self assetWriterStart];
#endif
}

- (void) finishWriting
{
#ifdef SCREEN_CAPTURE
	[assetWriter finishWriting];
#endif
#ifdef OPEN_CV
	[assetWriter finishWriting];
#endif
#if VIDEO_SAVE
	[assetWriter finishWriting];
#endif
}

- (NSURL *) fileURL
{
	NSString *outputPath = [[NSString alloc] initWithFormat:@"%@%@%f%@", NSHomeDirectory(), @"/Documents/Drive",[[NSDate date] timeIntervalSince1970],@".mov"];
#ifdef SCREEN_CAPTURE
	outputPath = [[NSString alloc] initWithFormat:@"%@%@%f%@", NSHomeDirectory(), @"/Documents/Drive",[[NSDate date] timeIntervalSince1970],@"_OVERLAY.mov"];

#endif
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
		self.captureSession.sessionPreset = AVCaptureSessionPreset640x480;
		
	}
	
	return self;
}


- (void)dealloc {
	[self.previewLayer release];
	[self.captureSession release];
	
	[super dealloc];
}
#endif
@end
