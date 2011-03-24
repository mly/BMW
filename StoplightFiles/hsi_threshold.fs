float RH_MIN1 = 0.0;
float RH_MAX1 = 40.0;
float RH_MIN2 = 350.0;
float RH_MAX2 = 360.0;
float RS_THRESHOLD = .13;

float GH_MIN = 150.0;
float GH_MAX = 180.0;
float GS_THRESHOLD = .6;

float I_THRESHOLD = 100.0;

float RED_THRESHOLD = 200.0;
float GY_THRESHOLD = 50.0;
float PIXEL_THRESHOLD  = 50.0;
float HEIGHT_FRACTION = .6;

uniform sampler2D inputImage;
varying vec2 pos;
float Intensity(float r, float g, float b)
{
	return (r + g + b)/3.0;
}

float Hue(float r, float g, float b)
{
	float theta = (180.0/3.0)*acos(((r - g + r - b)*.5)/(pow(pow(r - g, 2.0) + (r - b)*(g - b), .5)));
	if (b <= g) return theta;
	return 360.0 - theta;
	
}

float colorMin(float r, float g, float b)
{
	float m = r;
	if (g < m) m = g;
	if (b < m) m = b;
	return m;
}

float Saturation(float r, float g, float b)
{
	return (1.0 - (3.0/(r + g + b))*colorMin(r, g, b));
}

void main()
{
	vec4 pixel = texture2D(inputImage, pos);
	float ins = Intensity(pixel.r, pixel.g, pixel.b);
	float sat = Saturation(pixel.r, pixel.g, pixel.b);
	float hue = Hue(pixel.r, pixel.g, pixel.b);
	
	//Check for red traffic lights
	if (((hue >= RH_MIN1 && hue <= RH_MAX1) || (hue >= RH_MIN2 && hue <= RH_MAX2)) && sat >= RS_THRESHOLD && ins >= I_THRESHOLD){
	
		if (pixel.r > RED_THRESHOLD && pixel.g < GY_THRESHOLD && pixel.b < GY_THRESHOLD) {
			gl_FragColor = vec4(pixel.r, 0, 0, 1);
		} else gl_FragColor = vec4(0,0,0,1);

	//Check for green traffic lights
	} else if (hue >= GH_MIN && hue <= GH_MAX && sat >= GS_THRESHOLD && ins >= I_THRESHOLD){

		if (pixel.g > RED_THRESHOLD && pixel.r < GY_THRESHOLD && pixel.b < GY_THRESHOLD) {
			gl_FragColor = vec4(0, pixel.g, 0, 1);
		} else gl_FragColor = vec4(0,0,0,1);	

	}
	
}
