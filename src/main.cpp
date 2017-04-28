#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	

	ofGLFWWindowSettings settings;
	ofDisableArbTex();
	settings.setGLVersion(3, 2); //we define the OpenGL version we want to use
	settings.width = 1280;
	settings.height = 720;
	ofCreateWindow(settings);
	// this kicks off the running of my app
	ofRunApp(new ofApp());

}
