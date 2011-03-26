uniform sampler2D inputImage;

varying highp vec2 pos;

uniform highp vec2 pixelSize;

uniform highp float elementWidth;
uniform highp float elementHeight;
uniform highp float anchorWidth;
uniform highp float anchorHeight;

uniform lowp int erosion;
void main()
{
lowp float flag = 0.0;
for (highp float i = 1.0 - anchorWidth; flag==0.0&&i < elementWidth - anchorWidth; i++)  {
	for(highp float j = 1.0 - anchorHeight; flag==0.0&&j < elementHeight - anchorHeight; j++) {
		highp vec4 pixel = texture2D(inputImage, pos + vec2(i*pixelSize.x,j*pixelSize.y));
		if(pixel.r > 0.0)
		{
			flag = 1.0;
		}
	}
}
gl_FragColor = texture2D(inputImage, pos)*flag;

//	for (highp float i = 1.0 - anchorWidth; i < elementWidth - anchorWidth; i++)  {
//		for(highp float j = 1.0 - anchorHeight; j < elementHeight - anchorHeight; j++) {
//			highp vec4 pixel = texture2D(inputImage, pos + vec2(pixelSize.x * i, pixelSize.y*j));
//			if (pixel.r > 0.0 || pixel.g > 0.0) {
//				if (erosion < 0) {
//					gl_FragColor = pixel;
//					return;
//				}
//			} else {
//				if (erosion > 0) {
//					gl_FragColor = vec4(0.0,0.0,0.0,1.0);
//					return;
//				}
//			}
//		}
//	}
//	gl_FragColor = texture2D(inputImage, pos);
}
