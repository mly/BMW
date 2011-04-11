//
//  ImageProcessingViewController.h
//  ImageProcessing
//

#import <UIKit/UIKit.h>
#import "CaptureSessionManager.h"
#import "ImageProcessingGLView.h"
#import "ShaderProgram.h"

#ifdef OPEN_CV

@interface ImageProcessingViewController : UIViewController <ImageProcessingCameraDelegate>
{
	CaptureSessionManager *camera;
	ImageProcessingGLView *glView;
	
	NSMutableArray *shaders;
	
	GLuint videoFrameTexture;
	GLubyte *rawPositionPixels;
}

@property(readonly) ImageProcessingGLView *glView;

- (void) assetWriterStart;
- (NSURL *) fileURL;

@end

#endif