//
//  ImageProcessingViewController.h
//  ImageProcessing
//

#import <UIKit/UIKit.h>
#import "CaptureSessionManager.h"
#import "ImageProcessingGLView.h"

@interface ImageProcessingViewController : UIViewController <ImageProcessingCameraDelegate>
{
	CaptureSessionManager *camera;
	ImageProcessingGLView *glView;
	
	GLuint directDisplayProgram;
	GLuint videoFrameTexture;
	GLubyte *rawPositionPixels;
}

@property(readonly) ImageProcessingGLView *glView;

- (void) assetWriterStart;
- (NSURL *) fileURL;

// OpenGL ES 2.0 setup methods
- (BOOL)loadVertexShader:(NSString *)vertexShaderName fragmentShader:(NSString *)fragmentShaderName forProgram:(GLuint *)programPointer;
- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file;
- (BOOL)linkProgram:(GLuint)prog;
- (BOOL)validateProgram:(GLuint)prog;

@end

