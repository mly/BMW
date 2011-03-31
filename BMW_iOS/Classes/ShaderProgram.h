//
//  ShaderProgram.h
//

#import <Foundation/Foundation.h>
#import <OpenGLES/ES2/gl.h>

@interface ShaderProgram : NSObject {
@protected
    GLuint m_programID;
    GLuint m_vertShaderID;
    GLuint m_fragShaderID;
    NSMutableDictionary* m_attributeMap;
	NSMutableDictionary* m_uniformMap;
}

@property GLuint programID;

+ (void)enableDebugging:(BOOL)a_shouldDebug;
+ (ShaderProgram*)programWithVertexShader:(NSString*)a_vertShader andFragmentShader:(NSString*)a_fragmentShader;
+ (void)deleteAllPrograms;

- (void)setAsActive;
- (GLint)indexForAttribute:(NSString*)a_attributeName;
- (GLint)indexForUniform:(NSString*)a_uniformName;

@end
