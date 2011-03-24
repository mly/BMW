varying highp vec2 pos;

uniform sampler2D videoFrame;

void main()
{
	highp vec4 c = texture2D(videoFrame, pos);
	c.b = 0.0;
	gl_FragColor = c;
	
}
