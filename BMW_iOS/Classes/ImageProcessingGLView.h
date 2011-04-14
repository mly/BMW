//
//  ImageProcessingGLView.h
//  ImageProcessing
//

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#define FBO_HEIGHT 1280/2
#define FBO_WIDTH 720/2

@interface ImageProcessingGLView : UIView 
{
	/* The pixel dimensions of the backbuffer */
	GLint backingWidth, backingHeight;
	
	EAGLContext *context;
	
	/* OpenGL names for the renderbuffer and framebuffers used to render to this view */
	GLuint viewRenderbuffer, viewFramebuffer;
	
	GLuint positionRenderTexture;
	GLuint positionRenderbuffer, positionFramebuffer;
}

@property(readonly) GLuint positionRenderTexture;

// OpenGL drawing
- (BOOL)createFramebuffers;
- (void)destroyFramebuffer;
- (void)setDisplayFramebuffer;
- (void)setPositionThresholdFramebuffer;
- (BOOL)presentFramebuffer;

@end
