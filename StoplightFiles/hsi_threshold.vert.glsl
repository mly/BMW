// default.vert

/*
  This is a simple GLSL vertex shader appropriate for
  image processing. It transforms the vertex positions
  using the default OpenGL transformation, and passes
  through the texture coordinate as the position
  to be used in the image-processing kernel.
*/

// This 'varying' vertex output can be read as an input
// by a fragment shader that makes the same declaration.
varying vec2 pos;

void main()
{
    // Copy the stanard OpenGL texture coordiante to the output.
    pos = gl_MultiTexCoord0.xy;

    // Render the shape using stanard OpenGL position transforms.
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
}
