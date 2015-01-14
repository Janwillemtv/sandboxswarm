#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    map.set(15,20);

    
    int num = 50;
   
    fish.set(1,num,map.vectorGrid(),map.contours());
    people.set(2,10,map.vectorGrid(),map.contours());
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    map.update();
    fish.update();
    people.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));
    map.draw();
    fish.draw();
    people.draw();
    ofSetColor(255,0,0);
    ofCircle(mouse.x, mouse.y, 15);
   
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case '>':
        case '.':
            map.farAlter(1);
            break;
            
        case '<':
        case ',':
            map.farAlter(-1);
            break;
            
        case '+':
        case '=':
            map.nearAlter(1);
            break;
            
        case '-':
            map.nearAlter(-1);
            break;
        
        case 'v':
            map.drawVector = !map.drawVector;
            break;
        
        case 'c':
            map.calibrate = !map.calibrate;
            break;
           
        case 't':
            map.thresh = !map.thresh;
            break;
    
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    fish.mouseUpdate(x, y);
    mouse.x = x;
    mouse.y = y;
}


void ofApp::exit() {
    map.close();
}