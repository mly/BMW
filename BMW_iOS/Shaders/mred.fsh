varying highp vec2 textureCoordinate;

uniform sampler2D videoFrame;

void main()
{
	highp vec4 c = texture2D(videoFrame, textureCoordinate);
	c.r = 0.0;
	gl_FragColor = c;
}
