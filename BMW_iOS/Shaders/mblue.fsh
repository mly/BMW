default precision highp;
varying vec2 textureCoordinate;

uniform sampler2D videoFrame;

void main()
{
	vec4 c = texture2D(videoFrame, textureCoordinate);
	c.b = 0.0;
	gl_FragColor = c;
	
}
