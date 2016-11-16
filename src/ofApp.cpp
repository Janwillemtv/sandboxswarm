//#DESCRIPTION:///////////////////////////////////////////////////////////////
//
//  This code code runs a simulation of a oceanic world.
//  Islands can be created by physical interaction with the sand.
//  Flocking and island fauna is included.
//
//#DEPENDENCIES://////////////////////////////////////////////////////////////
//
//  Microsoft Kinect
//  Table full of Sand
//  Beamer
//
//#LEGAL NOTE://///////////////////////////////////////////////////////////////
//
//  Some Kinect routines are based on the OPENFRAMEWORKS Ofxkinect examples.
//
//#CREDITS:////////////////////////////////////////////////////////////////////
//
//  Janwillem Te Voortwis
//  Raoul Fasel
//
//////////////////////////////////////////////////////////////////////////////




#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){ //setup Open Framworks
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetLogLevel("ofThread", OF_LOG_WARNING);
    ofSetVerticalSync(true);//verical sync to decrease screen tearing
    map.set();
    ofMesh * temp = map.getMesh();
    
    int num = 50;
    //init all objects
    fish = new swarm(1,num,temp);
    people = new swarm(2,4,temp);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){//update all the objects
    map.update();
    fish->update();
    people->update();
}

//--------------------------------------------------------------
void ofApp::draw(){//draw all objects
    ofBackgroundGradient(ofColor(100,100,160), ofColor(40,40,100));
    map.draw();
    people->drawShadow();
    fish->drawShadow();
    fish->draw();
    people->draw();
    ofSetColor(255,0,0);
    ofDrawCircle(mouse.x, mouse.y, 15);//draw mouse blob that pushes all
   
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){//keypresses for debug
    switch(key){
        case '>':
        case '.':
            map.farThreshold +=1;
            if(map.farThreshold>=255) map.farThreshold = 255;
            break;
            
        case '<':
        case ',':
            map.farThreshold -= 1;
            if(map.farThreshold<=0) map.farThreshold = 0;
            break;
            
        case '+':
        case '=':
            map.nearThreshold +=1;
            if(map.nearThreshold>=255) map.nearThreshold = 255;
            break;
            
        case '-':
            map.nearThreshold -= 1;
            if(map.nearThreshold<=0) map.nearThreshold = 0;
            break;
        
        case 'v':
            map.drawVector = !map.drawVector;// drawe vector map to show vector directions
            break;
        
        case 'c':
            map.calibrate = !map.calibrate;//turn on camera for better calibration
            break;
           
        case 't':
            map.thresh = !map.thresh;
            break;
    
    }
}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    map.reposition();// apply grid to resolution
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    fish->mouseUpdate(x, y);
    mouse.x = x;
    mouse.y = y;
}


void ofApp::exit() {
    map.close();
}
