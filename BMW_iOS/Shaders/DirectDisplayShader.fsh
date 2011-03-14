varying lowp vec2 textureCoordinate;

uniform sampler2D videoFrame;

void main()
{
	mediump vec4 c = texture2D(videoFrame, textureCoordinate);
if (c.r > (95.0/255.0) && c.g > (40.0/255.0) && c.b > (20.0/255.0) && max(c.r,max(c.g,c.b)) - min(c.r,min(c.b,c.g)) > (15.0/255.0) && abs(c.r-c.g)>(15.0/255.0) && c.r>c.g && c.r>c.b) {
		//detects skin color at a 1-pixel level
		gl_FragColor = vec4(c.r-(25.0/255.0),c.g-(25.0/255.0),c.b+(100.0/255.0),1.0);
	} else {
		gl_FragColor = c;
	}
	
}
