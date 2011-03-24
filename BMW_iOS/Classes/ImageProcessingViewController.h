//
//  ImageProcessingViewController.h
//  ImageProcessing
//

#import <UIKit/UIKit.h>
#import "CaptureSessionManager.h"
#import "ImageProcessingGLView.h"
#import "ShaderProgram.h"

@interface ImageProcessingViewController : UIViewController <ImageProcessingCameraDelegate>
{
	CaptureSessionManager *camera;
	ImageProcessingGLView *glView;
	
	GLuint directDisplayProgram;
	GLuint redProgram;
	GLuint blueProgram;
	
	NSMutableArray *shaders;
	ShaderProgram *shader;
	
	GLuint videoFrameTexture;
	GLubyte *rawPositionPixels;
}

@property(readonly) ImageProcessingGLView *glView;

- (void) assetWriterStart;
- (NSURL *) fileURL;

@end

