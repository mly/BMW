//
//  ColorTrackingViewController.h
//  ColorTracking
//

#import <UIKit/UIKit.h>
#import "CaptureSessionManager.h"
#import "ColorTrackingGLView.h"


@interface ColorTrackingViewController : UIViewController <ColorTrackingCameraDelegate>
{
	CaptureSessionManager *camera;
	ColorTrackingGLView *glView;
	
	GLuint directDisplayProgram;
	GLuint videoFrameTexture;
}

@property(readonly) ColorTrackingGLView *glView;

// OpenGL ES 2.0 setup methods
- (BOOL)loadVertexShader:(NSString *)vertexShaderName fragmentShader:(NSString *)fragmentShaderName forProgram:(GLuint *)programPointer;
- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file;
- (BOOL)linkProgram:(GLuint)prog;
- (BOOL)validateProgram:(GLuint)prog;

@end

