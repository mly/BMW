attribute vec4 position;
attribute vec4 inputTextureCoordinate;

varying vec2 pos;

uniform float translate;

void main()
{
	gl_Position = position;
	//gl_Position.y += sin(translate) / 3.0;
	pos = inputTextureCoordinate.xy;
}