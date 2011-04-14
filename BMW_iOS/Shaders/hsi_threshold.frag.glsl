precision highp float;
float RH_MIN1 = 0.0;
float RH_MAX1 = 40.0;
float RH_MIN2 = 350.0;
float RH_MAX2 = 360.0;
float RS_THRESHOLD = .13;

float GH_MIN = 150.0;
float GH_MAX = 180.0;
float GS_THRESHOLD = .6;

float YH_MIN = 20.0;
float YH_MAX = 60.0;
float YS_THRESHOLD = .5;

float I_THRESHOLD = 100.0;

float R_THRESHOLD = 200.0;
float G_THRESHOLD = 150.0;
float Y_THRESHOLD = 150.0;

float GB_THRESHOLD = 100.0;
float RB_THRESHOLD = 100.0;
float RY_THRESHOLD = 100.0;

uniform sampler2D inputImage;
varying vec2 pos;

float Intensity(float r, float g, float b)
{
	return (r + g + b)/3.0;
}

float Hue(float r, float g, float b)
{
	float theta = (180.0/3.0)*acos(((r+r-b-g)*.5)/(pow(pow(r - g, 2.0) + (r - b)*(g - b), .5)));
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
	return 1.0 - 3.0*colorMin(r, g, b)/(r + g + b);
}

void main()
{
	vec4 pixel = texture2D(inputImage, pos);
	pixel *= 255.0;
	float ins = Intensity(pixel.r, pixel.g, pixel.b);
	float sat = Saturation(pixel.r, pixel.g, pixel.b);
	float hue = Hue(pixel.r, pixel.g, pixel.b);
	
	//Check for red traffic lights
	if (((hue >= RH_MIN1 && hue <= RH_MAX1) || (hue >= RH_MIN2 && hue <= RH_MAX2)) && sat >= RS_THRESHOLD && ins >= I_THRESHOLD){
		
		if (pixel.r > R_THRESHOLD && pixel.g < GB_THRESHOLD && pixel.b < GB_THRESHOLD) {
			gl_FragColor = vec4(1, 0, 0, 1);
		} else gl_FragColor = vec4(0,0,0,1);
		
	}else gl_FragColor = vec4(0,0,0,1);	
}
