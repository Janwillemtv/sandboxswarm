
#include "ofMain.h"
#include "ofApp.h"

#include "global.h"

const int borderTop = 50;
const int borderSide = 25;
const int row = 35;
const int column = 40;

//========================================================================
int main( ){

	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
