varying highp vec2 pos;

uniform sampler2D image;
uniform highp float phase;

void main()
{
//avatar mode
//	mediump vec4 c = texture2D(videoFrame, textureCoordinate);
//if (c.r > (95.0/255.0) && c.g > (40.0/255.0) && c.b > (20.0/255.0) && max(c.r,max(c.g,c.b)) - min(c.r,min(c.b,c.g)) > (15.0/255.0) && abs(c.r-c.g)>(15.0/255.0) && c.r>c.g && c.r>c.b) {
//		//detects skin color at a 1-pixel level
//		gl_FragColor = vec4(c.r-(25.0/255.0),c.g-(25.0/255.0),c.b+(100.0/255.0),1.0);
//	} else {
//		gl_FragColor = c;
//	}
//
//ripple
	highp vec2 r = vec2(0.5,0.5);
	highp float dist = length((pos-vec2(.5,.5))/r);
	highp float amplitude = 0.03;
	highp float period = 0.3;
	highp float delta = amplitude*sin(2.0*3.14159*dist/period-phase);
	gl_FragColor = texture2D(image, pos+vec2(delta,delta));
}
