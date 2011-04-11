precision highp float;
uniform sampler2D inputImage;

varying vec2 pos;

uniform vec2 pixelSize;

uniform float elementWidth;
uniform float elementHeight;
uniform float anchorWidth;
uniform float anchorHeight;

void main()
{
	int found = -1;
	float leftW = -(anchorWidth - 1.0);
	float rightW = elementWidth - anchorWidth;
	float leftH = -(anchorHeight - 1.0);
	float rightH = elementHeight - anchorHeight;
	
	for (float i = leftW; i < rightW; i++)  {
		for(float j = leftH; j < rightH; j++) {
			vec4 pixel = texture2D(inputImage, pos + vec2(pixelSize.x*i, pixelSize.y*j));
			if (pixel.r < .1 && pixel.g < .1 && pixel.b < .1) {
				gl_FragColor = vec4(0,0,0,1);
				found = 1;
				break;
			}
		}
		if (found > 0) break;
	}
	if (found < 0) gl_FragColor = texture2D(inputImage, pos);

}
