//
//  ImageProcessingViewController.m
//  ImageProcessing
//

#import "ImageProcessingViewController.h"

// Uniform index.
enum {
	UNIFORM_TRANSLATE,
    UNIFORM_VIDEOFRAME,
	UNIFORM_PHASE,
    NUM_UNIFORMS
};
GLint uniforms[NUM_UNIFORMS];

// Attribute index.
enum {
    ATTRIB_VERTEX,
    ATTRIB_TEXTUREPOSITON,
    NUM_ATTRIBUTES
};

@implementation ImageProcessingViewController

#define DEBUG

#pragma mark -
#pragma mark Initialization and teardown

- (void)loadView 
{
	CGRect mainScreenFrame = [[UIScreen mainScreen] applicationFrame];	
	UIView *primaryView = [[UIView alloc] initWithFrame:mainScreenFrame];
	self.view = primaryView;
	[primaryView release];

	glView = [[ImageProcessingGLView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, mainScreenFrame.size.width, mainScreenFrame.size.height)];	
	[self.view addSubview:glView];
	[glView release];
	
	//shaders = [[NSMutableArray alloc] init];
	
	//ShaderProgram *
	[ShaderProgram enableDebugging:YES];
//	[ShaderProgram programWithVertexShader:@"default.vsh" andFragmentShader:@"DirectDisplayShader.fsh"];
//	[ShaderProgram programWithVertexShader:@"default.vsh" andFragmentShader:@"mred.fsh"];
	//[shaders addObject:shader];
	//[shader release];
	
	camera = [[CaptureSessionManager alloc] init];
	camera.delegate = self;
}

-(void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)didReceiveMemoryWarning 
{
    [super didReceiveMemoryWarning];
}

- (void)dealloc 
{
	free(rawPositionPixels);
	[camera release];
	[shaders release];
    [super dealloc];
}

#pragma mark -
#pragma mark OpenGL ES 2.0 rendering methods
- (void)drawFrame
{    
    // Replace the implementation of this method to do your own custom drawing.
    static const GLfloat squareVertices[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f,  1.0f,
        1.0f,  1.0f,
    };

	static const GLfloat textureVertices[] = {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f,  1.0f,
        0.0f,  0.0f,
    };
	
	static const GLfloat passthroughTextureVertices[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f,  1.0f,
        1.0f,  1.0f,
    };
	
	static float transY = 0.0f;
	ShaderProgram *shader;
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
	// Use shader program.
	[glView setDisplayFramebuffer];	
	shader = [ShaderProgram programWithVertexShader:@"default.vsh" andFragmentShader:@"DirectDisplayShader.fsh"];
	[shader setAsActive];
	 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, videoFrameTexture);
	
	// Update uniform values
	glUniform1i([shader indexForUniform:@"image"], 0);
	glUniform4f([shader indexForUniform:@"colorFilter"], 1.0,1.0,1.0,1.0);
	glUniform1f([shader indexForUniform:@"phase"], transY);
	NSLog(@"%d",[shader indexForUniform:@"phase"]);
	transY += 0.1f;
	
	// Update attribute values.
	glVertexAttribPointer([shader indexForAttribute:@"position"], 2, GL_FLOAT, 0, 0, squareVertices);
	glEnableVertexAttribArray([shader indexForAttribute:@"position"]);
	glVertexAttribPointer([shader indexForAttribute:@"inputTextureCoordinate"], 2, GL_FLOAT, 0, 0, textureVertices);
	glEnableVertexAttribArray([shader indexForAttribute:@"inputTextureCoordinate"]);
	
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
//	shader = [ShaderProgram programWithVertexShader:@"default.vsh" andFragmentShader:@"mblue.fsh"];
//multiple passes	
//	[glView setPositionThresholdFramebuffer];
//	[shader setAsActive];
//	
//	glUniform1i([shader indexForUniform:@"videoFrame"], 0);
//	glUniform1f([shader indexForUniform:@"phase"], transY);
//	
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, glView.positionRenderTexture);
//	glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT, 0, 0, squareVertices);
//	glEnableVertexAttribArray(ATTRIB_VERTEX);
//	glVertexAttribPointer(ATTRIB_TEXTUREPOSITON, 2, GL_FLOAT, 0, 0, passthroughTextureVertices);
//	glEnableVertexAttribArray(ATTRIB_TEXTUREPOSITON);
//	
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//	
//	[glView setDisplayFramebuffer];
//	glUseProgram(blueProgram);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, glView.positionRenderTexture);
//	glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT, 0, 0, squareVertices);
//	glEnableVertexAttribArray(ATTRIB_VERTEX);
//	glVertexAttribPointer(ATTRIB_TEXTUREPOSITON, 2, GL_FLOAT, 0, 0, passthroughTextureVertices);
//	glEnableVertexAttribArray(ATTRIB_TEXTUREPOSITON);
//	
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
    [glView presentFramebuffer];
}

#pragma mark -
#pragma mark ImageProcessingCameraDelegate methods

- (void)cameraHasConnected;
{
//	NSLog(@"Connected to camera");
/*	camera.videoPreviewLayer.frame = self.view.bounds;
	[self.view.layer addSublayer:camera.videoPreviewLayer];*/
}

- (void)processNewCameraFrame:(CVImageBufferRef)cameraFrame;
{
	CVPixelBufferLockBaseAddress(cameraFrame, 0);
	int bufferHeight = CVPixelBufferGetHeight(cameraFrame);
	int bufferWidth = CVPixelBufferGetWidth(cameraFrame);
	
	// Create a new texture from the camera frame data, display that using the shaders
	glGenTextures(1, &videoFrameTexture);
	glBindTexture(GL_TEXTURE_2D, videoFrameTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// This is necessary for non-power-of-two textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	// Using BGRA extension to pull in video frame data directly
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bufferWidth, bufferHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, CVPixelBufferGetBaseAddress(cameraFrame));

	[self drawFrame];
	
	glDeleteTextures(1, &videoFrameTexture);

	CVPixelBufferUnlockBaseAddress(cameraFrame, 0);
}

#pragma mark -
#pragma mark Accessors

@synthesize glView;

@end
