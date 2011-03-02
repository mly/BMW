#include <highgui.h>
#include <cv.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>

#define H_MIN1 0
#define H_MAX1 40
#define H_MIN2 350
#define H_MAX2 360
#define S_THRESHOLD .13
#define I_THRESHOLD 100
#define PI 3.14159265
#define BASE_SIZE 500
#define RADIUS_THRESHOLD 10
#define RED_THRESHOLD 200
#define GY_THRESHOLD 50
#define PIXEL_THRESHOLD 50
#define HEIGHT_FRACTION .6

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

typedef struct BlobPoint {
	CvPoint point;
	struct BlobPoint *nextPoint;
} BlobPoint;

typedef struct Blob{
	BlobPoint *points;
	int numPoints;
	struct Blob *nextBlob;
} Blob;

void circleTest(IplImage *src, IplImage *dst, Blob *blobs)
{
	float meanX = 0;
	float meanY = 0;
	
	Blob *blob = blobs;
	Blob *prev = NULL;
	while(blob != NULL) {
		for (int i = 0; i < blob->numPoints; i++) {
			CvPoint *p = blob->points + i;
			meanX += p->x;
			meanY += p->y;
		}
		
		meanX /= blob->numPoints;
		meanY /= blob->numPoints;
		
		float maxR = -1;
		float minR = -1;
		for (int i = 0; i < blob->numPoints; i++) {
			CvPoint *p = blob->points + i;
			float r = pow(p->x - meanX, 2) + pow(p->y, 2);
			if (r > maxR || maxR < 0) maxR = r;
			if (r < minR || minR < 0) minR = r;
		}
		if ((maxR - minR) > RED_THRESHOLD) {
			if (prev == NULL) {
				free(blob->points);
				Blob *temp = blob->nextBlob;
				free(blob);
				blobs = temp;
				blob = temp;
			} else if (blob->nextBlob == NULL) {
				free(blob->points);
				free(blob);
				prev->nextBlob = NULL;
				blob = NULL;
			} else {
				prev->nextBlob = blob->nextBlob;
				free(blob->points);
				free(blob);
				blob = prev->nextBlob;
			}
		} else {
			prev = blob;
			blob = blob->nextBlob;
		}
	}
}

int blobUnion(int labels [], int l1, int l2)
{
	labels[l1] = min(labels[l1], labels[l2]);
	labels[l2] = labels[l1];
	return labels[l1];
}
/*
void LabelRegions(IplImage* src, IplImage* dst, Blob *boundaries)
{
	int labels[BASE_SIZE];
	memset(labels,0,sizeof(labels));
	uchar count = 1;
	for (int i = 1; i < src->height; i++) {
		uchar* sp = (uchar*)(src->imageData + i*src->widthStep);
		uchar* dp = (uchar*)(dst->imageData + i*src->widthStep);
		uchar* dp_a = (uchar*)(dst->imageData + (i-1)*src->widthStep);
		for (int j = 1; j < src->width; j++) {
			unsigned int r = sp[3*j+2];
			if (r > RED_THRESHOLD) {
				uchar left = dp[3*(j-1)+2];
				uchar up = dp_a[3*j+2];
				dp[3*j+2] = left;
				if (up != 0) {
					if (dp[3*j+2] == 0) {
						dp[3*j+2] = up;
					} else {
						dp[3*j+2] = blobUnion(labels, left, up);
					}
				} else {
					if (dp[3*j+2] == 0) {
						blobBoundaries[count] = malloc(sizeof(blob));
						labels[count] = count;
						dp[3*j+2] = count;
						count++;
					}
				}
			} 
		}
	}
	
	for (int i = 1; i < src->height-1; i++) {
		uchar* sp = (uchar*)(src->imageData + i*src->widthStep);
		uchar* dp = (uchar*)(dst->imageData + i*src->widthStep);
		uchar* dp_a = (uchar*)(dst->imageData + (i-1)*src->widthStep);
		uchar* dp_b = (uchar*)(dst->imageData + (i+1)*src->widthStep);
		for (int j = 1; j < src->width-1; j++) {
			unsigned int r = sp[3*j+2];
			uchar left = dp[3*(j-1)+2];
			uchar right = dp[3*(j+1)+2];
			uchar up = dp_a[3*j+2];
			uchar down = dp_b[3*j+2];
			if(!left||!right||!up||!down){
				bp* newpt = malloc(sizeof(bp));
				
				// give destination correct label
				dp[3*j+2] = labels[dp[3*j+2]];
				newpt->x = i;
				newpt->y = j;
				newpt->next = blobBoundaries[dp[3*j+2]]->points;
				
				// add point to correct blob
				blobBoundaries[dp[3*j+2]] = newpt;
				
				// increment number of points in boundary
				blobBoundaries[dp[3*j+2]]++;
			}
		}
	}
}
*/
uchar Intensity(uchar r, uchar g, uchar b)
{
	return r + g + b;
}

unsigned int Hue(int r, int g, int b)
{
	
	int theta = (180/3)*acos((.5*(r - g + r - b))/(pow(pow(r - g, 2) + (r - b)*(g - b), .5)));
	if (b <= g) return theta;
	return 360 - theta;
}

unsigned int colorMin(uchar r, uchar g, uchar b)
{
	uchar min = r;
	if (g < min) min = g;
	if (b < min) min = b;
	return min;
}

float Saturation(int r, int g, int b)
{
	return (1.0 - (float)(3.0/(float)(r + g + b))*(float)colorMin(r, g, b));
}

void ColorScreening(IplImage *src, IplImage *dst)
{
	for (int i = 0; i < src->height*HEIGHT_FRACTION; i++) {
		uchar* srcp = (uchar*)(src->imageData + i*src->widthStep);
		uchar* dstp = (uchar*)(dst->imageData + i*src->widthStep);
		for (int j = 0; j < src->width; j++) {
			unsigned int b = srcp[3*j];
			unsigned int g = srcp[3*j+1];
			unsigned int r = srcp[3*j+2];
			
			unsigned int hue = Hue(r, g, b);
			float sat = Saturation(r, g, b);
			unsigned int ins = Intensity(r, g, b);
			if (((hue >= H_MIN1 && hue <= H_MAX1) || (hue >= H_MIN2 && hue <= H_MAX2)) && sat >= S_THRESHOLD && ins >= I_THRESHOLD){
				if (r > RED_THRESHOLD && g < GY_THRESHOLD && b < GY_THRESHOLD) {
					dstp[3*j+2] = r;
				} else dstp[3*j+2] = 0;
			} else {
				dstp[3*j+2] = 0;
			}
		}
	}
}
/*
void LabelRegions(IplImage* src, IplImage* dst)
{
	int *labels = malloc(sizeof(int *)*BASE_SIZE);
	uchar count = 1;
	for (int i = 1; i < src->height; i++) {
		uchar* sp = (uchar*)(src->imageData + i*src->widthStep);
		uchar* dp = (uchar*)(dst->imageData + i*src->widthStep);
		uchar* dp_a = (uchar*)(dst->imageData + (i-1)*src->widthStep);
		for (int j = 1; j < src->width; j++) {
			unsigned int r = sp[3*j+2];
			if (r > 0) {
				dp[3*j+2] = dp[3*(j-1)+2];
				if (dp_a[3*j+2] != 0) {
					if (dp[3*j+2] == 0) {
						dp[3*j+2] = dp[3*(j-1)+2];
					} else {
						//UNION
					}
				} else {
					if (dp[3*j+2] == 0) {
						dp[3*j+2] = count;
						count++;
					}
				}
				
			} else {
				//dp[3*j] = 0;
				//dp[3*j+1] = 0;
				//dp[3*j+2] = 0;
			}
		}
	}
}
*/
int main (int argc, const char * argv[]) {
	CvCapture* capture = cvCreateFileCapture(argv[1]);
	IplImage* frame = cvQueryFrame(capture);
	CvSize sz = cvGetSize(frame);
	IplImage* redScreened = cvCreateImage(sz, frame->depth, frame->nChannels);
	IplImage* redErode = cvCreateImage(sz, frame->depth, frame->nChannels);
	IplImage* redDilate = cvCreateImage(sz, frame->depth, frame->nChannels);
	
	double fps = cvGetCaptureProperty (capture, CV_CAP_PROP_FPS);
	CvSize size = cvSize((int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH), (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT)); 
	CvVideoWriter *writer = cvCreateVideoWriter(argv[2], CV_FOURCC('M','P','4','2'), fps, sz, 1);
	
	while (1) {
		if (!frame) break;
		
		ColorScreening(frame, redScreened);
		cvDilate(redScreened, redDilate, cvCreateStructuringElementEx(17, 17, 9, 9, CV_SHAPE_RECT, NULL), 1);
		cvErode(redDilate, redErode, cvCreateStructuringElementEx(19, 19, 10, 10, CV_SHAPE_RECT, NULL), 1);
		
		/*
		cvNamedWindow("Light Detector",CV_WINDOW_AUTOSIZE); 
		cvShowImage("Light Detector", frame);
		cvWaitKey(0);
		
		cvShowImage("Light Detector",redScreened); 
		cvWaitKey(0); 
		cvShowImage("Light Detector", redDilate);
		cvWaitKey(0);
		
		cvShowImage("Light Detector", redErode);
		cvWaitKey(0);
		*/
		cvWriteFrame(writer, redErode);
		frame = cvQueryFrame(capture);
	}
	/*
	ColorScreening(greenLight, redScreened);
	cvDilate(redScreened, redDilate, cvCreateStructuringElementEx(13, 13, 6, 6, CV_SHAPE_RECT, NULL), 1);
	cvErode(redDilate, redErode, cvCreateStructuringElementEx(17, 17, 8, 8, CV_SHAPE_RECT, NULL), 1);
	cvShowImage("Light Detector", redErode);

	cvWaitKey(0);
	*/
	cvReleaseImage(&frame);
	cvReleaseImage(&redScreened);
	cvReleaseImage(&redErode);
	cvReleaseImage(&redDilate);
	cvReleaseVideoWriter(&writer);
	cvDestroyWindow("Light Detector");
}
