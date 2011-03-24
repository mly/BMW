default precision highp;

uniform sampler2D inputImage;

varying vec2 pos;

uniform vec2 pixelSize;

uniform float elementWidth;
uniform float elementHeight;
uniform float anchorWidth;
uniform float anchorHeight;

uniform int erosion;
void main()
{
	
	for (float i = 1.0 - anchorWidth; i < elementWidth - anchorWidth; i++)  {
		for(float j = 1.0 - anchorHeight; j < elementHeight - anchorHeight; j++) {
			vec4 pixel = texture2D(inputImage, pos + vec2(pixelSize.x * i, pixelSize.y*j));
			if (pixel.r > 0.0 || pixel.g > 0.0) {
				if (erosion < 0) {
					gl_FragColor = pixel;
					return;
				}
			} else {
				if (erosion > 0) {
					gl_FragColor = vec4(0,0,0,1);
					return;
				}
			}
		}
	}
	gl_FragColor = texture2D(inputImage, pos);
}
