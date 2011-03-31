attribute vec4 position;
attribute vec4 inputTextureCoordinate;

varying vec2 pos;

void main()
{
	gl_Position = position;
	pos = inputTextureCoordinate.xy;
}