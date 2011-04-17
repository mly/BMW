#include "Framework.h"
#include "Shader.h"
#include "DepthRenderTarget.h"
#include <math.h>

#define RED_THRESHOLD 200
#define BASE_SIZE 500
#define GL_CHECK(x) { (x); GLenum error = glGetError(); if (GL_NO_ERROR != error) {printf("GL_ERROR: %s\n", gluErrorString(error));}}

typedef struct BlobPoint {
	int x;
	int y;
	struct BlobPoint* nextPoint;
} BlobPoint;

typedef struct Blob{
	BlobPoint *points;
	int numPoints;
} Blob;

sf::WindowSettings settings(24, 8, 2);
sf::RenderWindow window(sf::VideoMode(640, 360), "CS210 Rules!", sf::Style::Close, settings); 

// Vertex shader
std::auto_ptr<Shader> hsi;
std::auto_ptr<Shader> erosion;
std::auto_ptr<Shader> dilation;
std::auto_ptr<Shader> dead;

//erosion and dilation variables
float elemSide = 9.0;
float anchor = 5.0;
bool dilate = true;

sf::Image* frame;

void initOpenGL();
void loadAssets();
void handleInput();
void renderFrame();
void DrawQuad(GLuint programID);

int main(int argc, char** argv) {

    initOpenGL();
    loadAssets();
	handleInput();
	renderFrame();
    while (window.IsOpened()) {       
		window.Display();
    }
		
    return 0;
}

void initOpenGL() {
#ifdef FRAMEWORK_USE_GLEW
    GLint error = glewInit();
    if (GLEW_OK != error) {
        std::cerr << glewGetErrorString(error) << std::endl;
        exit(-1);
    }
    if (!GLEW_VERSION_2_0) {
        std::cerr << "This program requires OpenGL 2.0" << std::endl;
        exit(-1);
    }
#endif

    GL_CHECK(glClearColor(.15, .15, .15, .15));
	
}

void loadAssets() {
    hsi.reset(new Shader("shaders/hsi_threshold"));
	if (!hsi->loaded()) {
		std::cerr << "Shader failed to load" << std::endl;
		std::cerr << hsi->errors() << std::endl;
		exit(-1);
	}
	
	erosion.reset(new Shader("shaders/erosion"));
	if (!erosion->loaded()) {
		std::cerr << "Shader failed to load" << std::endl;
		std::cerr << erosion->errors() << std::endl;
		exit(-1);
	}
	
	dilation.reset(new Shader("shaders/dilation"));
	if (!dilation->loaded()) {
		std::cerr << "Shader failed to load" << std::endl;
		std::cerr << dilation->errors() << std::endl;
		exit(-1);
	}
	
	dead.reset(new Shader("shaders/dead"));
	if (!dead->loaded()) {
		std::cerr << "Shader failed to load" << std::endl;
		std::cerr << dead->errors() << std::endl;
		exit(-1);
	}
	
	frame = new sf::Image();
	frame->LoadFromFile("/Users/johnjessen/Desktop/CS210/vlcsnap-2011-04-13-17h11m18s163.png");
}

int blobUnion(int labels [], int l1, int l2)
{
	if (labels[l1] > labels[l2]) labels[l1] = labels[l2];
	labels[l2] = labels[l1];
	return labels[l1];
}


int VerifyFree (Blob* boundaries[]){
	int r = 1;
	for(int i=1; i<BASE_SIZE; i++)
		if (boundaries[i]!=NULL)
			r = 0;
	return r;
	
}

void FreeAllRegions (Blob* boundaries[], int nBlob)
{
	for (int i = 1; i <= nBlob; i++){
		{
			Blob* blob = boundaries[i];
			if (blob==NULL)
				continue;
			BlobPoint* next = blob->points;
			while(next!=NULL)
			{
				BlobPoint* old = next;
				next = old->nextPoint;
				free(old);
			}
			free(boundaries[i]);
			boundaries[i] = NULL;
		}
	}
}

bool hasColor(sf::Color color)
{
	return (color.r > 0 || color.g > 0);
}

void LabelRegions(sf::Image *src, sf::Image* dst, Blob* boundaries [], int* nBlob)
{
	int labels[BASE_SIZE];
	for(int i = 0; i < BASE_SIZE; i++)
		labels[i] = BASE_SIZE+1;
	
	int count = 1;
	int nred = 0;
	
	for (int i = 1; i < src->GetHeight(); i++) {
		for (int j = 1; j < src->GetWidth(); j++) {
			sf::Color r = src->GetPixel(j, i);
			if (hasColor(r)) {
				nred++;
				sf::Color left = dst->GetPixel(j-1, i);
				sf::Color up = dst->GetPixel(j, i-1);
				dst->SetPixel(j, i, left);
				if (up.r != 0) {
					if (dst->GetPixel(j,i).r == 0) {
						dst->SetPixel(j, i, up);
					} else {
						sf::Color color;
						color.r = blobUnion(labels, left.r, up.r);
						dst->SetPixel(j, i, color);
					}
				} else {
					if (dst->GetPixel(j,i).r == 0) {
						labels[count] = count;
						sf::Color color;
						color.r = count;
						dst->SetPixel(j,i, color);
						count++;
					}
				}
			}
		}
	}
	
	int remap [count];
	memset(remap,0,sizeof(remap));
	
	for(int i=1; i<count; i++){
		remap[labels[i]]=1;
	}
	
	*nBlob = 0;   
	int newcount = 1;
	for(int i=1; i<count; i++){
		if(remap[i]){
			remap[i] = newcount;
			(*nBlob) = newcount;
			newcount++;
		}
	}
	
	for(int i=1; i<count; i++){
		labels[i] = remap[labels[i]];
	}
	
	
	for (int i=1; i<count; i++){
		if (boundaries[labels[i]] == NULL){
			boundaries[labels[i]] = (Blob *)malloc(sizeof(Blob));
			boundaries[labels[i]]->numPoints = 0;
			boundaries[labels[i]]->points = NULL;
		}
	}

	for (int i = 1; i < dst->GetHeight()-1; i++) {
		for (int j = 1; j < dst->GetWidth()-1; j++) {
			sf::Color r = src->GetPixel(j, i);
			sf::Color left = dst->GetPixel(j-1, i);
			sf::Color right = dst->GetPixel(j+1, i);
			sf::Color up = dst->GetPixel(j, i-1);
			sf::Color down = dst->GetPixel(j, i+1);
			if(hasColor(r) && dst->GetPixel(j,i).r > 0){
				int label = labels[dst->GetPixel(j,i).r];
				// increment number of points in boundary
				boundaries[label]->numPoints++;
				
				if (!left.r||!right.r||!up.r||!down.r){
					BlobPoint* newpt = (BlobPoint*) malloc(sizeof(BlobPoint));
					
					// give destination correct label
					sf::Color color;
					color.r = label;
					dst->SetPixel(j,i,color);
					newpt->x = j;
					newpt->y = i;
					newpt->nextPoint = boundaries[label]->points;
					
					// add point to correct blob
					boundaries[label]->points = newpt;
				}
			}
		}
	} 
}

void handleInput() {

}

void loadShaderVariables(GLuint programID)
{
	if (!dilate) {
		elemSide += 2.0;
		anchor += 1.0;
	}
	GLuint loc = glGetUniformLocation(programID, "pixelSize");
	if (loc >= 0) glUniform2f(loc, 1.0/frame->GetWidth(), 1.0/frame->GetHeight());
	
	loc = glGetUniformLocation(programID, "elementWidth");
	if (loc >= 0) glUniform1f(loc, elemSide);
	
	loc = glGetUniformLocation(programID, "elementHeight");
	if (loc >= 0) glUniform1f(loc, elemSide);
	
	loc = glGetUniformLocation(programID, "anchorWidth");
	if (loc >= 0) glUniform1f(loc, anchor);
	
	loc = glGetUniformLocation(programID, "anchorHeight");
	if (loc >= 0) glUniform1f(loc, anchor);

}

void DrawQuad(GLuint programID)
{		
	GL_CHECK(glMatrixMode(GL_PROJECTION));
	GL_CHECK(glLoadIdentity());
	GL_CHECK(gluOrtho2D(-1, 1, -1, 1));
	glViewport(0, 0, window.GetWidth(), window.GetHeight());
	
	GL_CHECK(glMatrixMode(GL_MODELVIEW));
	GL_CHECK(glLoadIdentity());
	GL_CHECK(glEnable(GL_TEXTURE_2D));
	
	loadShaderVariables(programID);
	
	frame->Bind();
	
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex2f(-1, -1);
	
	glTexCoord2f(1, 1);
	glVertex2f(1, -1);
	
	glTexCoord2f(1, 0);
	glVertex2f(1, 1);
	
	glTexCoord2f(0, 0);
	glVertex2f(-1, 1);
	glEnd();
}

void drawRectangle(sf::Image *frame, BlobPoint lowerLeft, BlobPoint upperRight, sf::Color color, bool fillBlack)
{
	if (fillBlack) {
		for (int i = lowerLeft.x; i <= upperRight.x; i++) {
			for (int j = lowerLeft.y; j <= upperRight.y; j++) {
				frame->SetPixel(i, j, sf::Color(0,0,0));
			}
		}
	} else {
		for (int i = lowerLeft.x; i <= upperRight.x; i++) {
			frame->SetPixel(i, upperRight.y, color);
			frame->SetPixel(i, lowerLeft.y, color);
		}
	
		for (int i = lowerLeft.y+1; i < upperRight.y; i++) {
			frame->SetPixel(lowerLeft.x, i, color);
			frame->SetPixel(upperRight.x, i, color);
		}
	}
}

bool circleTest(Blob *blob)
{
	BlobPoint *next = blob->points;
	float averageX = 0;
	float averageY = 0;
	float numPoints = 0;
	while(next != NULL) {
		averageX += next->x;
		averageY += next->y;
		numPoints++;
		next = next->nextPoint;
	}
	averageX /= numPoints;
	averageY /= numPoints;
	
	next = blob->points;
	float rMax = -99999;
	float rMin = 99999;
	while(next != NULL) {
		float r = pow(next->x - averageX, 2) + pow(next->y - averageY, 2);
		if (r > rMax) rMax = r;
		if (r < rMin) rMin = r;
		next = next->nextPoint;
	}
	printf("%f\n", rMax - rMin);
	return rMax - rMin < 7;
}

void renderFrame() {
	//perform HSI converison
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	
	GLuint programID = hsi->programID();
	
	GL_CHECK(glUseProgram(programID));

	DrawQuad(programID);
	GL_CHECK(glUseProgram(0));
	
	
	*frame = window.Capture();
	
	//perform dilation
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	
	programID = dilation->programID();
	
	GL_CHECK(glUseProgram(programID));
	
	DrawQuad(programID);
	GL_CHECK(glUseProgram(0));
	
	*frame = window.Capture();
	dilate = false;
	
	//perform erosion
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	
	programID = erosion->programID();
	
	GL_CHECK(glUseProgram(programID));
	
	DrawQuad(programID);
	GL_CHECK(glUseProgram(0));
	 
	*frame = window.Capture();
	
	Blob* boundaries[BASE_SIZE];
	int nBlob = 0;
	
	memset(boundaries,0,sizeof(boundaries));
	
	sf::Image *labels = new sf::Image(frame->GetWidth(), frame->GetHeight());
	
	LabelRegions(frame, labels, boundaries, &nBlob);
	
	//printf("%d\n", nBlob);
	
	// draw rectangles
	for (int i=1; i<= nBlob; i++){
		// find the points
		BlobPoint ll, ur;
		ll.x = 99999;
		ll.y = 99999;
		ur.x = 0;
		ur.y = 0;
		Blob* blob = boundaries[i];
		BlobPoint* next = blob->points;
		printf("%d\n", blob->numPoints);
		while(next != NULL)
		{
			if(next->x < ll.x) ll.x = next->x;
			if(next->y < ll.y) ll.y = next->y;
			if(next->x > ur.x) ur.x = next->x;
			if(next->y > ur.y) ur.y = next->y;
			next = next->nextPoint;
			
		}
		
		ll.x -= 2;
		ll.y -= 2;
		ur.x += 2;
		ur.y += 2;
		bool fillBlack = false;
		if (!circleTest(blob)) {
			fillBlack = true;
		}
		drawRectangle(frame, ll, ur, sf::Color(0,0,255), fillBlack);
	}
		
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	
	programID = dead->programID();
	
	GL_CHECK(glUseProgram(programID));
	
	DrawQuad(programID);
	GL_CHECK(glUseProgram(0));
	
	FreeAllRegions(boundaries, nBlob);
}
