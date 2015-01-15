
#include "ofMain.h"
#include "ofApp.h"

#include "global.h"

const int borderTop = 50;
const int borderSide = 25;
const int row = 15;
const int column = 20;

//========================================================================
int main( ){

	ofSetupOpenGL(640*1.5,480*1.5, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
